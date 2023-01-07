#include "x11/protocol/error.h"

#include "utils/PREPROCESSOR.h"

namespace x11 {
namespace protocol {
namespace error {

static char const * const names[] =
{
  "?"			,
  "Request"		, // 1
  "Value"		, // 2
  "Window"		, // 3
  "Pixmap"		, // 4
  "Atom"		, // 5
  "Cursor"		, // 6
  "Font"		, // 7
  "Match"		, // 8
  "Drawable"		, // 9
  "Access"		, // 10
  "Alloc"		, // 11
  "Colormap"		, // 12
  "GContext"		, // 13
  "IDChoice"		, // 14
  "Name"		, // 15
  "Length"		, // 16
  "Implementation"	, // 17
};
char const * toString(Id id)
{
  return
      (unsigned(id) < ARRAY_SIZE(names))
          ? names[unsigned(id)]
          : "?";
}

} // namespace error
} // namespace protocol
} // namespace x11
