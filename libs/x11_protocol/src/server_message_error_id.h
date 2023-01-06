#pragma once

namespace x11 {
namespace protocol {
namespace server {
namespace message {
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

} // namespace error
} // namespace message
} // namespace server
} // namespace protocol
} // namespace x11
