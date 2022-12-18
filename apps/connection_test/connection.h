#pragma once

#include "connection_config.h"

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

protected:

public:
  Connection();
  Connection(const std::string& display);
};

} // namespace client2server
} // namespace x11
