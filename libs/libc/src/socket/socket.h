#pragma once

#include "libc/result.h"

#include <sys/socket.h>

namespace libc {
namespace socket {

namespace raw {

using SocketResult = ::libc::Result<int>;

inline SocketResult socket(int domain, int type, int protocol)
{
  return SocketResult(::socket(domain, type, protocol));
}

} // namespace raw

namespace cxx {

int socket(int domain, int type, int protocol);

} // namespace cxx

} // namespace socket
} // namespace libc
