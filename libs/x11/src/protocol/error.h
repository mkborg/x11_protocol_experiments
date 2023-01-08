#pragma once

#include <stdint.h>     // [u]int(8|16|32|64)_t

/*

    Error reports are 32 bytes long.

    Every error includes an 8-bit error code. Error codes 128 through 255
    are reserved for extensions.

    Every error also includes the major and minor opcodes of the failed
    request and the least significant 16 bits of the sequence number of
    the request.

    For the following errors (see section 4), the failing resource ID is
    also returned: Colormap, Cursor, Drawable, Font, GContext, IDChoice,
    Pixmap and Window.

    For Atom errors, the failing atom is returned.

    For Value errors, the failing value is returned.

    Other core errors return no additional data.

    Unused bytes within an error are not guaranteed to be zero.

*/
namespace x11 {
namespace protocol {
namespace error {

enum class Id
{
  Request	= 1,
  Value		= 2,
  Window	= 3,
  Pixmap	= 4,
  Atom		= 5,
  Cursor	= 6,
  Font		= 7,
  Match		= 8,
  Drawable	= 9,
  Access	= 10,
  Alloc		= 11,
  Colormap	= 12,
  GContext	= 13,
  IDChoice	= 14,
  Name		= 15,
  Length	= 16,
  Implementation = 17,
};
char const * toString(Id id);

struct Header
{
  uint8_t status;	// 0 means 'error'
  uint8_t error_code;
  uint16_t sequence;
  uint32_t bad;		// 'bad value', 'bad resouce id', 'bad atom id'
  uint16_t minor_opcode;
  uint8_t major_opcode;
  uint8_t unused_11[21];
};

} // namespace error
} // namespace protocol
} // namespace x11
