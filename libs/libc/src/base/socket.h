#pragma once

#include "libc/socket/fd.h"

#include <sys/socket.h>		// struct sockaddr, socklen_t

namespace libc {
namespace base {

class EndPoint;

class Socket
  : public ::libc::socket::Fd
{
public:
  ~Socket() = default;

  inline explicit Socket()
    : ::libc::socket::Fd()
  {
  }

  inline explicit Socket(int fd)
    : ::libc::socket::Fd(fd)
  {
  }

  inline Socket(int domain, int type, int protocol)
    : ::libc::socket::Fd(domain, type, protocol)
  {
  }

  Socket(const Socket&) = delete;
  inline Socket(Socket&& other)
    : ::libc::socket::Fd(std::move(other))
  {
  }

  Socket& operator =(const Socket&) = delete;
  inline Socket& operator =(Socket&& other)
  {
    ::libc::socket::Fd::operator =(std::move(other));
    return *this;
  }

  int accept();
  void bind(const struct sockaddr *addr, socklen_t socklen);
  void bind(const EndPoint& endPoint);
  void connect(const struct sockaddr *addr, socklen_t socklen);
  void connect(const EndPoint& endPoint);
  void listen(int backlog);
};

} // namespace base
} // namespace libc
