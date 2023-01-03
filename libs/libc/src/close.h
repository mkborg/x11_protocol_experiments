#pragma once

/// @brief libc 'close()' wrapped with 'libc::Result'

#include "libc/result.h"

#include <unistd.h>             // close()

namespace libc {
namespace raw {

using CloseResult = ::libc::Result<int>;

/*
    [man 2 close]:

    close() should not be retried after an error

    Linux kernel always releases the file descriptor early in the close
    operation, freeing it for reuse; the steps that may return an error,
    such as flushing data to the filesystem or device, occur only later
    in the close operation.
*/
inline CloseResult close(int fd)
{
  return CloseResult(::close(fd));
}

} // namespace raw
} // namespace libc
