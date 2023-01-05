#pragma once

#include "libc/base/socket.h"

#include <sys/socket.h>		// AF_*, SOCK_*

namespace libc {

namespace Template {

template<int addressFamily, int socketType, int protocol>
class Socket
  : public ::libc::base::Socket
{
public:
  ~Socket() = default;
  Socket()
    : ::libc::base::Socket(addressFamily, socketType, protocol)
  {
  }

  Socket(const Socket&) = delete;

  Socket(Socket&& other)
    : ::libc::base::Socket(std::move(other))
  {
  }

  Socket& operator =(const Socket&) = delete;

  Socket& operator =(Socket&& other)
  {
    ::libc::base::Socket(std::move(other));
    return *this;
  }
};

} // namespace Template

namespace IPv4 {

using DatagramSocket = Template::Socket<AF_INET, SOCK_DGRAM , 0>;
using StreamSocket   = Template::Socket<AF_INET, SOCK_STREAM, 0>;

} // namespace IPv4

namespace IPv6 {

using DatagramSocket = Template::Socket<AF_INET6, SOCK_DGRAM , 0>;
using StreamSocket   = Template::Socket<AF_INET6, SOCK_STREAM, 0>;

} // namespace IPv6

namespace Unix {

using DatagramSocket  = Template::Socket<AF_UNIX, SOCK_DGRAM    , 0>;
using SeqPacketSocket = Template::Socket<AF_UNIX, SOCK_SEQPACKET, 0>;
using StreamSocket    = Template::Socket<AF_UNIX, SOCK_STREAM   , 0>;

} // namespace Unix

} // namespace libc
