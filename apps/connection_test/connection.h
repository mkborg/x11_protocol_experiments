#pragma once

#include "connection_config.h"

//#include "libc/handle.h"
//#include "libc/template/socket.h"
#include "libc/base/socket.h"

/*
    This is 'connection' from 'client application' to 'x11 server'.

    It is 'generic stream connection' supporting both 'tcp/ip [socket]'
    and 'unix socket' connection types.

    mk: Looks like most of the time it will be 'unix stream socket'.
*/

#include <string>

namespace x11 {
namespace client2server {

class Connection
{
private:
  connection::Config connection_config_;
  //::libc::Fd fd_;
  //::libc::Unix::StreamSocket fd_;
  ::libc::base::Socket fd_;

protected:

public:
  Connection();
  Connection(const std::string& display);
};

} // namespace client2server
} // namespace x11
