#pragma once

#include <stdint.h>     // [u]int(8|16|32|64)_t

namespace x11 {
namespace connection {
namespace reply {

struct Header
{
  uint8_t status; // 0 failed, 1 success, 2 authenticate
  uint8_t reason_size;
  uint16_t protocol_major_version;
  uint16_t protocol_minor_version;
  uint16_t data_size;
  //uint32_t data[]; // data[data_size]
};

} // namespace reply
} // namespace connection
} // namespace x11
