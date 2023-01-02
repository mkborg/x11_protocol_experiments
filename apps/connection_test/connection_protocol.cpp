#include "connection_protocol.h"

#include <exceptions/runtime_error.h>
//#include <logger/debug.h>
#include <utils/PREPROCESSOR.h>

#include <cstring>	// strcmp()

namespace x11 {
namespace client2server {
namespace raw {

static char const * const protocol_names[] =
{
  "tcp",   // TCP over IPv4 or IPv6
  "inet",  // TCP over IPv4 only
  "inet6", // TCP over IPv6 only
  "unix",  // UNIX Domain Sockets (same host only)
  "local", // Platform preferred local connection method
};
static_assert(ARRAY_SIZE(protocol_names) == Protocol_COUNT,
    "'protocol_names' doesn't match 'Protocol_COUNT'");

char const * toString(Protocol protocol)
{
  if (unsigned(protocol) < unsigned(Protocol::COUNT)) {
    return protocol_names[unsigned(protocol)];
  } else {
    return "?";
  }
}

Protocol toProtocol(char const * s)
{
  //DPRINTF("s='%s'", s);
  unsigned i = 0;
  for (; i < ARRAY_SIZE(protocol_names); ++i)
  {
    if (!strcmp(s, protocol_names[i]))
    {
      //DPRINTF("s='%s' protocol_names[%u]='%s'", s, i, protocol_names[i]);
      break;
    }
  }
  return static_cast<Protocol>(i);
}

} // namespace raw

namespace cxx {

raw::Protocol toProtocol(const char* s)
{
  const auto rawProtocol = raw::toProtocol(s);
  if (isNG(rawProtocol)) {
    throw RUNTIME_ERROR("invalid 'protocol'");
  }
  return rawProtocol;
}

OptionalProtocol toOptionalProtocol(const char* s)
{
  const auto rawProtocol = raw::toProtocol(s);
  return isOK(rawProtocol)
      ? OptionalProtocol(Protocol(rawProtocol))
      : OptionalProtocol();
}

} // namespace cxx
} // namespace client2server
} // namespace x11
