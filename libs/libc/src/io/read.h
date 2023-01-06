#pragma once

/// @brief libc 'read()' wrapped with 'libc::Result'

#include "libc/result.h"

#include <unistd.h>

namespace libc {
namespace io {

namespace raw {

using ReadResult = Result<size_t>;

/*
    [man 2 read]:

    According to POSIX.1, if 'size' is greater than SSIZE_MAX, the result
    is implementation-defined.

    On Linux, read() (and similar system calls) will transfer at most
    0x7ffff000 (2,147,479,552) bytes, returning the number of bytes
    actually transferred. (This is true on both 32-bit and 64-bit
    systems.)
*/
inline ReadResult read(int fd, void* data, size_t size)
{
  return ReadResult(::read(fd, data, size));
}

// There is no 'read_exact' in 'libc'. This 'read_exact' is convenience
// wrapper for 'read'.
inline ReadResult read_exact(int fd, void* data, size_t size)
{
  size_t done_size = 0;
  while (size)
  {
retry:
    const auto r = read(fd, data, size);
    if (!r)
    {
      const auto errorNumber = r.raw().error();
      if (EINTR == errorNumber) { goto retry; }
      return r;
    }
    const auto done = r.raw().result();
    // Note: successful read returning zero size means 'EOF'
    if (!done) { return ReadResult::Failure(ENODATA); }
    done_size += done;
    data = reinterpret_cast<uint8_t*>(data) + done;
    size -= done;
  }
  return ReadResult::Success(done_size);
}

} // namespace raw

namespace cxx {

size_t read(int fd, void* data, size_t size);
void read_exact(int fd, void* data, size_t size);

} // namespace cxx

} // namespace io
} // namespace libc
