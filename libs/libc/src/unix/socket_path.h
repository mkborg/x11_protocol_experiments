#pragma once

#include <string>

namespace libc {
namespace unix {
namespace socket {
namespace path {

/*
    'remove()' and 'prepare()' are to be used with 'server' sockets.

    All directories in 'socketPath' must be created before 'bind()' call. Final
    element in 'socketPath' must be absent before 'bind()' call. 'socketPath' is
    not needed after 'server' shutdown.
*/
void remove(const char* socketPath);
void remove(const std::string& socketPath);

void prepare(const char* socketPath);
void prepare(const std::string& socketPath);

} // namespace path
} // namespace socket
} // namespace unix
} // namespace libc
