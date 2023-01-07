#pragma once

#include "libc/base/socket.h"
//#include "libc/socket/fd.h"

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
{
public:
  Connection();

  Connection(int fd)
    : ::libc::base::Socket(fd)
  {
  }

  Connection(const std::string& display);
};

} // namespace x11
