#pragma once

#include <stdint.h>     // [u]int(8|16|32|64)_t

/*

    Every reply contains a 32-bit length field expressed in units of four
    bytes.

    Every reply consists of 32 bytes followed by zero or more additional
    bytes of data, as specified in the length field. Unused bytes within
    a reply are not guaranteed to be zero.

    Every reply also contains the least significant 16 bits of the
    sequence number of the corresponding request.

*/
namespace x11 {
namespace protocol {
namespace reply {

struct Header
{
  uint8_t status;       // 0 means 'error', 1 'success reply', 2..34 events
  uint8_t unused_1;
  uint16_t size;
  uint8_t unused_4[28];
  // uint32_t data[size];
};

} // namespace reply
} // namespace protocol
} // namespace x11
