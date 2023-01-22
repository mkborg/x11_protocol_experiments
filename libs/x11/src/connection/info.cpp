#include "x11/connection/info.h"

#include "cxx/raw/view.h"
#include "exceptions/runtime_error.h"
#include "logger/debug.h"
//#include "logger/hex_dump.h"

namespace x11 {
namespace connection {

using ByteView = ::cxx::raw::base::View<const uint8_t, const void>;

static const ::x11::connection::impl::Info * parseInfo(ByteView& image)
{
  const auto image_size = image.size();
  const auto infoImage_size = sizeof(::x11::connection::impl::Info);
  DPRINTF("image_size=%zu infoImage_size=%zu", image_size, infoImage_size);
  if (image_size < infoImage_size) {
    throw RUNTIME_ERROR_PRINTF("'connection::reply' is too short ('%s' underflow)", "info");
  }
  const auto infoImage = static_cast<const ::x11::connection::impl::Info*>(image.data());
  image.remove_prefix(infoImage_size);
  DPRINTF("release_number=%u resource_id_base=0x%X/%u resource_id_mask=0x%X/%u",
      infoImage->release_number,
      infoImage->resource_id_base, infoImage->resource_id_base,
      infoImage->resource_id_mask, infoImage->resource_id_mask);
  DPRINTF("motion_buffer_size=%u vendor_size=%u request_maximum_size=%u screens_count=%u formats_count=%u",
      infoImage->motion_buffer_size,
      infoImage->vendor_size,
      infoImage->request_maximum_size,
      infoImage->screens_count,
      infoImage->formats_count);
  DPRINTF("image_byte_order=%u bitmap_format_bit_order=%u",
      infoImage->image_byte_order, infoImage->bitmap_format_bit_order);
  DPRINTF("bitmap_format_scanline_unit=%u bitmap_format_scanline_pad=%u",
      infoImage->bitmap_format_scanline_unit, infoImage->bitmap_format_scanline_pad);
  DPRINTF("min_keycode=%u max_keycode=%u",
      infoImage->min_keycode, infoImage->max_keycode);
  return infoImage;
}

static const std::string parseVendor(ByteView& image, const ::x11::connection::impl::Info * info)
{
  const auto image_size = image.size();
  const auto vendor_image_size = info->vendor_size;
  const auto vendor_allocated_size = (vendor_image_size + 3U) & ~3U;
  DPRINTF("image_size=%zu vendor_image_size=%u vendor_allocated_size=%u",
      image_size, vendor_image_size, vendor_allocated_size);
  if (image_size < vendor_allocated_size) {
    throw RUNTIME_ERROR_PRINTF("'connection::reply' is too short ('%s' underflow)", "vendor");
  }
  const auto vendor_image = static_cast<const char*>(image.data());
  const auto vendor = std::string(vendor_image, vendor_image_size);
  image.remove_prefix(vendor_allocated_size);
  DPRINTF("vendor='%s'", vendor.c_str());
  return vendor;
}

static const Formats parseFormats(ByteView& image, const ::x11::connection::impl::Info * info)
{
  const auto image_size = image.size();
  const auto formats_count = info->formats_count;
  const auto formats_image_size = sizeof(::x11::connection::impl::Format) * formats_count;
  DPRINTF("image_size=%zu formats_image_size=%zu formats_count=%u",
      image_size, formats_image_size, formats_count);
  if (image_size < formats_image_size) {
    throw RUNTIME_ERROR_PRINTF("'connection::reply' is too short ('%s' underflow)", "formats");
  }
  const auto formatsImage = static_cast<const ::x11::connection::impl::Format*>(image.data());
  Formats formats;
  for (unsigned i = 0; i < formats_count; ++i) {
    formats.push_back(
      Format{
        formatsImage[i].depth,
        formatsImage[i].bits_per_pixel,
        formatsImage[i].scanline_pad
      } 
    );
  }
  image.remove_prefix(formats_image_size);
  dump(formats);
  return formats;
}

static const VisualTypes parseVisuals(ByteView& image, const ::x11::connection::impl::Depth * depth)
{
  const auto image_size = image.size();
  const auto visualTypes_count = depth->visuals_count;
  const auto visualTypes_image_size = sizeof(::x11::connection::impl::VisualType) * visualTypes_count;
  DPRINTF("image_size=%zu visualTypes_image_size=%zu visualTypes_count=%u",
      image_size, visualTypes_image_size, visualTypes_count);
  if (image_size < visualTypes_image_size) {
    throw RUNTIME_ERROR_PRINTF("'connection::reply' is too short ('%s' underflow)", "visual types");
  }
  const auto visualTypesImage = static_cast<const ::x11::connection::impl::VisualType*>(image.data());
  VisualTypes visualTypes;
  for (unsigned i = 0; i < visualTypes_count; ++i) {
    //DPRINTF("[%u] visual_id=%u visual_class=%u", i, visualTypesImage[i].visual_id, visualTypesImage[i].visual_class);
    visualTypes.push_back(
        VisualType{
            visualTypesImage[i].visual_id,
            visualTypesImage[i].visual_class,
            visualTypesImage[i].bits_per_rgb_value,
            visualTypesImage[i].colormap_entries,
            visualTypesImage[i].red_mask,
            visualTypesImage[i].green_mask,
            visualTypesImage[i].blue_mask
        }
    );
  }
  image.remove_prefix(visualTypes_image_size);
  return visualTypes;
}

static const Depth parseDepth(ByteView& image, const ::x11::connection::impl::Screen * /*screenImage*/)
{
  const auto image_size = image.size();
  const auto depth_image_size = sizeof(::x11::connection::impl::Depth);
  DPRINTF("image_size=%zu depth_image_size=%zu", image_size, depth_image_size);
  if (image_size < depth_image_size) {
    throw RUNTIME_ERROR_PRINTF("'connection::reply' is too short ('%s' underflow)", "depth");
  }
  const auto depthImage = static_cast<const ::x11::connection::impl::Depth*>(image.data());
  DPRINTF("depth=%u visuals_count=%u", depthImage->depth, depthImage->visuals_count);
  image.remove_prefix(depth_image_size);
  const auto visualTypes = parseVisuals(image, depthImage);
  const auto depth = Depth{
      depthImage->depth,
      depthImage->visuals_count,
      visualTypes
  };
  return depth;
}

static const Depths parseDepths(ByteView& image, const ::x11::connection::impl::Screen * screenImage)
{
  const auto depths_count = screenImage->depths_count;
  Depths depths;
  for (unsigned i = 0; i < depths_count; ++i) {
    depths.push_back(parseDepth(image, screenImage));
  }
  return depths;
}

static const Screen parseScreen(ByteView& image, const ::x11::connection::impl::Info * /*info*/)
{
  const auto image_size = image.size();
  const auto screen_image_size = sizeof(::x11::connection::impl::Screen);
  DPRINTF("image_size=%zu screen_image_size=%zu", image_size, screen_image_size);
  if (image_size < screen_image_size) {
    throw RUNTIME_ERROR_PRINTF("'connection::reply' is too short ('%s' underflow)", "screen");
  }
  const auto screenImage = static_cast<const ::x11::connection::impl::Screen*>(image.data());
  image.remove_prefix(screen_image_size);
  const auto depths = parseDepths(image, screenImage);
  const auto screen = Screen{
      screenImage->root_window,
      screenImage->default_colormap,
      screenImage->white_pixel,
      screenImage->black_pixel,
      screenImage->current_input_masks,
      screenImage->width_in_pixels,
      screenImage->height_in_pixels,
      screenImage->width_in_millimeters,
      screenImage->height_in_millimeters,
      screenImage->min_installed_maps,
      screenImage->max_installed_maps,
      screenImage->root_visual,
      screenImage->backing_stores,
      screenImage->save_unders,
      screenImage->root_depth,
      screenImage->depths_count,
      depths
  };
  return screen;
}

static const Screens parseScreens(ByteView& image, const ::x11::connection::impl::Info * info)
{
  const auto screens_count = info->screens_count;
  Screens screens;
  for (unsigned i = 0; i < screens_count; ++i) {
    screens.push_back(parseScreen(image, info));
  }
  dump(screens);
  return screens;
}

static Info parseInfo(const ::cxx::raw::Data& infoData)
{
  auto imageView = ByteView(infoData.data(), infoData.size());

  const auto info = parseInfo(imageView);
  const auto resourceId = ResourceId{
      info->resource_id_base,
      info->resource_id_mask
  };
  const auto vendor = parseVendor(imageView, info);
  const auto formats = parseFormats(imageView, info);
  const auto screens = parseScreens(imageView, info);

  const auto image_size = imageView.size();
  if (image_size) {
    WPRINTF("Unused image_size=%zu", image_size);
    //DHEX(imageView.data(), image_size);
  } else {
    DPRINTF("There is no unused data left in info image");
  }

  return Info(resourceId, vendor, formats, screens);
}

void dump(const Screens& screens)
{
  const auto screens_size = screens.size();
  for (unsigned i = 0; i < screens_size; ++i) {
    DPRINTF("screen[%u] root_window=%u default_colormap=%u white_pixel=0x%X/%u black_pixel=0x%X/%u", i,
        screens[i].root_window,
        screens[i].default_colormap,
        screens[i].white_pixel, screens[i].white_pixel,
        screens[i].black_pixel, screens[i].black_pixel);
  }
}

void dump(const Formats formats)
{
  const auto formats_size = formats.size();
  for (unsigned i = 0; i < formats_size; ++i) {
    DPRINTF("format[%u] depth=%u bits_per_pixel=%u scanline_pad=%u", i,
        formats[i].depth, formats[i].bits_per_pixel, formats[i].scanline_pad);
  }
}

Info::Info(const ::cxx::raw::Data& infoImage)
  : Info(parseInfo(infoImage))
{
}

} // namespace connection
} // namespace x11
