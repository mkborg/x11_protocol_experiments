#pragma once

#include "libc/template/endpoint.h"
#include "libc/unix/socket_path.h"

#include <string>

#include <sys/un.h>             // struct sockaddr_un

namespace libc {
namespace unix {

class EndPoint
  : public Template::EndPoint<sockaddr_un>
{
public:
  std::string socketPath() const;

  explicit EndPoint(const char* socketPath);
  explicit EndPoint(const std::string& socketPath)
    : EndPoint(socketPath.c_str())
  {
  }

  void removeSocketPath() const
  {
    socket::path::remove(socketPath());
  }

  void prepareSocketPath() const
  {
    socket::path::prepare(socketPath());
  }
};

} // namespace unix
} // namespace libc
