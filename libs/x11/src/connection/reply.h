#pragma once

#include <stdint.h>     // [u]int(8|16|32|64)_t

namespace x11 {
namespace connection {
namespace reply {

enum class Id
{
  Failed	= 0,
  Success	= 1,
  Authenticate	= 2,
};
char const * toString(Id id);

struct Header
{
  uint8_t id; // 0 failed, 1 success, 2 authenticate
  uint8_t reason_size;
  uint16_t protocol_major_version;
  uint16_t protocol_minor_version;
  uint16_t data_size;
  //uint32_t data[]; // data[data_size]
};

} // namespace reply
} // namespace connection
} // namespace x11
