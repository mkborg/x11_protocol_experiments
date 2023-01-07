#pragma once

#include "libc/base/socket.h"
#include "x11/connection/config.h"

/*
    This is 'connection' from 'client application' to 'x11 server'.

    It is 'generic stream connection' supporting both 'tcp/ip [socket]'
    and 'unix socket' connection types.

    mk: Looks like most of the time it will be 'unix stream socket'.
*/

#include <string>

namespace x11 {

class Connection
{
private:
  ::x11::connection::Config connection_config_;
  ::libc::base::Socket fd_;

protected:

public:
  Connection();
  Connection(const std::string& display);
};

} // namespace x11
