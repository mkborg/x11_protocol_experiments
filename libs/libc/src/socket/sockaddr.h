#pragma once

#include <string>

#include <sys/socket.h>

namespace libc {
namespace socket {

/*

    The <sys/socket.h> header shall define the sockaddr structure, which
    shall include at least the following members:

      sa_family_t  sa_family  Address family.
      char         sa_data[]  Socket address (variable-length data).

*/
std::string toString(const struct sockaddr* sa, socklen_t socklen);

/*

    The <sys/socket.h> header shall define the sockaddr_storage structure, which shall be:

    * Large enough to accommodate all supported protocol-specific address structures

    * Aligned at an appropriate boundary so that pointers to it can be
      cast as pointers to protocol-specific address structures and used
      to access the fields of those structures without alignment problems

    The sockaddr_storage structure shall include at least the following members:

      sa_family_t   ss_family

*/
inline
std::string toString(const struct sockaddr_storage* sas)
{
  return toString(reinterpret_cast<const struct sockaddr*>(sas), sizeof(struct sockaddr_storage));
}

} // namespace socket
} // namespace libc
