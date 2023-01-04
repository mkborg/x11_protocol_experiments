#pragma once

#include "libc/result.h"

#include <sys/socket.h>

namespace libc {
namespace socket {

namespace raw {

using GetSockNameResult = ::libc::Result<int>;

inline GetSockNameResult getsockname(int fd, struct sockaddr* addr, socklen_t* addrlen)
{
  return GetSockNameResult(::getsockname(fd, addr, addrlen));
}

} // namespace raw

namespace cxx {

void getsockname(int fd, struct sockaddr* addr, socklen_t* addrlen);

} // namespace cxx

} // namespace socket
} // namespace libc
