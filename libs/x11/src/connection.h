#pragma once

#include "libc/base/socket.h"
#include "x11/connection/info.h"

#include <string>

/*
    This is 'connection' from 'client application' to 'x11 server'.

    It is 'generic stream connection' supporting both 'tcp/ip [socket]'
    and 'unix socket' connection types.

    mk: Looks like most of the time it will be 'unix stream socket'.
*/

namespace x11 {

class Connection
  : public ::libc::base::Socket
  , public ::x11::connection::Info
{
public:
  explicit Connection();
  explicit Connection(const std::string& display);

/*
  Connection(int fd)
    : ::libc::base::Socket(fd)
    , info_(::x11:connection::Info(
  {
  }
*/
#if 1
  explicit Connection(::libc::base::Socket&& socket);
#else
  explicit Connection(::libc::base::Socket&& socket)
    : ::libc::base::Socket( std::move(socket) )
    , ::x11:connection::Info(static_cast<const ::libc::base::Socket*>(this))
  {
  }
#endif
};

} // namespace x11
