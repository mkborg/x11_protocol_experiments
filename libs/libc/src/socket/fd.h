#pragma once

#include "libc/io/fd.h"
#include "libc/socket/socket.h"

namespace libc {
namespace socket {

class Fd
  : public ::libc::io::Fd
{
public:
  ~Fd() = default;

  explicit Fd()
    : ::libc::io::Fd()
  {
  }

  explicit Fd(int fd)
    : ::libc::io::Fd(fd)
  {
  }

  // Note: May 'throw' exception
  Fd(int domain, int type, int protocol)
    : Fd(::libc::socket::cxx::socket(domain, type, protocol))
  {
  }

  Fd(const Fd&) = delete;
  Fd(Fd&& other)
    : ::libc::io::Fd(std::move(other))
  {
  }

  Fd& operator =(const Fd&) = delete;
  Fd& operator =(Fd&& other)
  {
    ::libc::io::Fd::operator =(std::move(other));
    return *this;
  }
};

} // namespace socket
} // namespace libc
