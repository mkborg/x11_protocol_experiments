#pragma once

#include "cxx/raw/data.h"

#include <vector>

#include <stdint.h>     // [u]int(8|16|32|64)_t

namespace x11 {
namespace connection {

namespace impl {

// mk: Looks like base part of 'info' has size of 32 bytes
struct Info
{
  uint32_t release_number;
  uint32_t resource_id_base;
  uint32_t resource_id_mask;
  uint32_t motion_buffer_size;
  uint16_t vendor_size;
  uint16_t request_maximum_size;
  uint8_t screens_count;
  uint8_t formats_count;
  uint8_t image_byte_order; // 0 LSBFirst, 1 MSBFirst
  uint8_t bitmap_format_bit_order; // 0 LeastSignificant, 1 MostSignificant
  uint8_t bitmap_format_scanline_unit;
  uint8_t bitmap_format_scanline_pad;
  uint8_t min_keycode;
  uint8_t max_keycode;
  uint32_t unused_28;
  // uint8_t vendor[vendor_size]
  // uint8_t vendor_pad[(4 - vendor_size % 4) % 4]
  // Format format[number_of_formats_in_pixmap_formats]
};

struct Format
{
  uint8_t depth;
  uint8_t bits_per_pixel;
  uint8_t scanline_pad;
  uint8_t unused_3[5];
};
//using Formats = std::vector<Format>;

struct Screen
{
  uint32_t root_window;
  uint32_t default_colormap;
  uint32_t white_pixel;
  uint32_t black_pixel;
  uint32_t current_input_masks;
  uint16_t width_in_pixels;
  uint16_t height_in_pixels;
  uint16_t width_in_millimeters;
  uint16_t height_in_millimeters;
  uint16_t min_installed_maps;
  uint16_t max_installed_maps;
  uint32_t root_visual;
  uint8_t backing_stores;
  uint8_t save_unders;
  uint8_t root_depth;
  uint8_t depths_count;
  // Depth depths[depths_count]
};
//using Screens = std::vector<Screen>;

struct Depth
{
  uint8_t depth;
  uint8_t unused_1;
  uint16_t visuals_count;
  uint32_t unused_4;
  // VisualType visuals[visuals_count]
};

// VISUALID 32-bit value (top three bits guaranteed to be zero)
struct VisualType
{
  uint32_t visual_id;
  uint8_t visual_class;
  uint8_t bits_per_rgb_value;
  uint16_t colormap_entries;
  uint32_t red_mask;
  uint32_t green_mask;
  uint32_t blue_mask;
  uint32_t unused_20;
};

struct ResourceId
{
  uint32_t base;
  uint32_t mask;
};

} // namespace impl

struct Format
{
  uint8_t depth;
  uint8_t bits_per_pixel;
  uint8_t scanline_pad;
};
using Formats = std::vector<Format>;
void dump(const Formats formats);

struct VisualType
{
  uint32_t visual_id;
  uint8_t visual_class;
  uint8_t bits_per_rgb_value;
  uint16_t colormap_entries;
  uint32_t red_mask;
  uint32_t green_mask;
  uint32_t blue_mask;
};
using VisualTypes = std::vector<VisualType>;
void dump(const VisualTypes visualTypes);

struct Depth
{
  uint8_t depth;
  uint16_t visuals_count;
  VisualTypes visualTypes;
};
using Depths = std::vector<Depth>;
void dump(const Depths depths);

struct Screen
{
  uint32_t root_window;
  uint32_t default_colormap;
  uint32_t white_pixel;
  uint32_t black_pixel;
  uint32_t current_input_masks;
  uint16_t width_in_pixels;
  uint16_t height_in_pixels;
  uint16_t width_in_millimeters;
  uint16_t height_in_millimeters;
  uint16_t min_installed_maps;
  uint16_t max_installed_maps;
  uint32_t root_visual;
  uint8_t backing_stores;
  uint8_t save_unders;
  uint8_t root_depth;
  uint8_t depths_count;
  Depths depths; // depths[depths_count]
};
using Screens = std::vector<Screen>;
void dump(const Screens& screens);

class Info
{
private:
  std::string vendor_;
  Formats formats_;
  Screens screens_;

public:
  Info(
      const std::string& vendor,
      const Formats& formats,
      const Screens& screens
  )
    : vendor_(vendor)
    , formats_(formats)
    , screens_(screens)
  {
  }

  inline const std::string& vendor() const { return vendor_; }

  //Info(const ::libc::base::Socket& socket);
  Info(const ::cxx::raw::Data& data);
  Info(Info&& other)
    : Info(other.vendor_, other.formats_, other.screens_)
  {
  }
};

} // namespace connection
} // namespace x11
