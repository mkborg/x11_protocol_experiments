#pragma once

#include <stdint.h>     // [u]int(8|16|32|64)_t

namespace x11 {
namespace connection {

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

struct Screen
{
  uint32_t root_window;
  uint32_t default_colormap;
  uint32_t white_pixel;
  uint32_t black_pixel;
};

struct Depth
{
};

// VISUALID 32-bit value (top three bits guaranteed to be zero)
struct VisualType
{
};

} // namespace connection
} // namespace x11
