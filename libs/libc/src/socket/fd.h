#pragma once

#include "libc/io/fd.h"
#include "libc/socket/socket.h"

namespace libc {
namespace socket {

class Fd
  : public ::libc::io::Fd
{
public:
  explicit Fd()
    : ::libc::io::Fd()
  {
  }

  explicit Fd(int fd)
    : ::libc::io::Fd(fd)
  {
  }

  Fd(int domain, int type, int protocol)
    : Fd(::libc::socket::cxx::socket(domain, type, protocol))
  {
  }

  Fd(const Fd&) = delete;

  Fd(Fd&& other)
    : ::libc::io::Fd(std::move(other))
  {
  }
};

} // namespace socket
} // namespace libc
