#include "libc/socket/socket.h"

#include "logger/debug.h"
#include "exceptions/system_error.h"

namespace libc {
namespace socket {
namespace cxx {

int socket(int domain, int type, int protocol)
{
  DPRINTF9("domain=0x%X type=0x%X protocol=0x%X", domain, type, protocol);
  const auto r = ::libc::socket::raw::socket(domain, type, protocol);
  if (!r)
  {
    throw SYSTEM_ERROR(r.raw().error(), "socket");
  }
  return r.raw().result();
}

} // namespace cxx
} // namespace socket
} // namespace libc
