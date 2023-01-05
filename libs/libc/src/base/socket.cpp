#include "libc/base/socket.h"

#include "libc/base/endpoint.h"

#include "exceptions/system_error.h"

namespace libc {
namespace base {

int Socket::accept()
{
  auto r(libc::socket::Fd::accept());
  if (!r)
  {
    int errorNumber(r.raw().error());
    throw SYSTEM_ERROR(errorNumber, "accept");
  }
  return r.raw().result();
}

void Socket::bind(const EndPoint& endPoint)
{
  bind(static_cast<const sockaddr*>(endPoint), endPoint.size());
}

void Socket::bind(const struct sockaddr *addr, socklen_t socklen)
{
  auto r(libc::socket::Fd::bind(addr, socklen));
  if (!r)
  {
    int errorNumber(r.raw().error());
    throw SYSTEM_ERROR(errorNumber, "bind");
  }
}

void Socket::connect(const EndPoint& endPoint)
{
  connect(static_cast<const sockaddr*>(endPoint), endPoint.size());
}

void Socket::connect(const struct sockaddr *addr, socklen_t socklen)
{
  auto r(libc::socket::Fd::connect(addr, socklen));
  if (!r)
  {
    int errorNumber(r.raw().error());
    throw SYSTEM_ERROR(errorNumber, "connect");
  }
}

void Socket::listen(int backlog)
{
  auto r(libc::socket::Fd::listen(backlog));
  if (!r)
  {
    int errorNumber(r.raw().error());
    throw SYSTEM_ERROR(errorNumber, "listen");
  }
}

} // namespace base
} // namespace libc
