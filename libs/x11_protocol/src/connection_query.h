#pragma once

#include <stdint.h>     // [u]int(8|16|32|64)_t

namespace connection {
namespace query {

struct Header
{
  uint8_t byte_order; // 0x42 'B' MASB first or 0x6C 'l' LSB first
  uint8_t unused_1;
  uint16_t protocol_major_version;
  uint16_t protocol_minor_version;
  uint16_t authorization_protocol_name_size;
  uint16_t authorization_protocol_data_size;
  uint16_t unused_10;
  //uint32_t authorization_protocol_name[]; // authorization_protocol_name[(authorization_protocol_name_size+3)/4]
  //uint32_t authorization_protocol_data[]; // authorization_protocol_data[(authorization_protocol_data_size+3)/4]
};

} // namespace query
} // namespace connection
