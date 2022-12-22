#include "connection_protocol.h"

#include <utils/PREPROCESSOR.h>

#include <cstring>	// strcmp()

namespace x11 {
namespace client2server {
namespace protocol {

static char const * const names[] =
{
  "tcp",   // TCP over IPv4 or IPv6
  "inet",  // TCP over IPv4 only
  "inet6", // TCP over IPv6 only
  "unix",  // UNIX Domain Sockets (same host only)
  "local", // Platform preferred local connection method
};
static_assert(ARRAY_SIZE(names) == Id_COUNT,
    "'protocol::names' doesn't match 'protocol::Id'");

char const * toString(Id id)
{
  if (unsigned(id) < unsigned(Id::COUNT)) {
    return names[unsigned(id)];
  } else {
    return "?";
  }
}

Id toId(char const * s)
{
  unsigned i = 0;
  for (; i < ARRAY_SIZE(names); ++i)
  {
    if (!strcmp(s, names[i]))
    {
      break;
    }
  }
  return static_cast<Id>(i);
}

} // namespace protocol
} // namespace client2server
} // namespace x11
