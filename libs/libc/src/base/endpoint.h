#pragma once

#include "cxx/raw/data.h"

#include <string>

#include <sys/socket.h> // struct sockaddr, socklen_t

namespace libc {
namespace base {

class EndPoint
  : public ::cxx::raw::Data
{
public:
  explicit EndPoint(size_t size)
    : ::cxx::raw::Data(size, 0)
  {
  }
  EndPoint(const void* data, size_t size)
    : ::cxx::raw::Data(data, size)
  {
  }
  inline EndPoint(const sockaddr* addr, socklen_t addrlen)
    : EndPoint(static_cast<const void*>(addr), addrlen)
  {
  }

  explicit inline operator const sockaddr*() const { return static_cast<const sockaddr*>(data()); }
  explicit inline operator sockaddr*() { return static_cast<sockaddr*>(data()); }
};

} // namespace base
} // namespace libc
