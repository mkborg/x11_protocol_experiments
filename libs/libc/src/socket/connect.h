#pragma once

#include "libc/result.h"

#include <sys/socket.h>

namespace libc {
namespace socket {

namespace raw {

using ConnectResult = ::libc::Result<int>;

inline ConnectResult connect(int fd, const struct sockaddr *addr, socklen_t addrlen)
{
  return ConnectResult(::connect(fd, addr, addrlen));
}

} // namespace raw

namespace cxx {

int connect(int fd, const struct sockaddr *addr, socklen_t addrlen);

} // namespace cxx

} // namespace socket
} // namespace libc
