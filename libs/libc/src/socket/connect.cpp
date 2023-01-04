#include "libc/socket/connect.h"

#include "exceptions/system_error.h"

namespace libc {
namespace socket {
namespace cxx {

int connect(int fd, const struct sockaddr *addr, socklen_t addrlen)
{
  const auto r = ::libc::socket::raw::connect(fd, addr, addrlen);
  if (!r)
  {
    throw SYSTEM_ERROR(r.error(), "connect");
  }
  return r.result();
}

} // namespace cxx
} // namespace socket
} // namespace libc
