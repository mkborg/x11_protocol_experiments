#pragma once

/// @brief libc 'write()' wrapped with 'libc::Result'

#include "libc/result.h"

#include <unistd.h>

namespace libc {
namespace io {

namespace raw {

using WriteResult = Result<size_t>;

inline WriteResult write(int fd, const void* data, size_t size)
{
  return WriteResult(::write(fd, data, size));
}

// There is no 'write_exact' in 'libc'. This 'write_exact' is
// convenience wrapper for 'write'.
inline WriteResult write_exact(int fd, const void* data, size_t size)
{
  size_t done_size = 0;
  while (size)
  {
retry:
    const auto r = write(fd, data, size);
    if (!r)
    {
      const auto errorNumber = r.raw().error();
      if (EINTR == errorNumber) { goto retry; }
      return r;
    }
    const auto done = r.raw().result();
    // Note: successful zero size partial write shall be impossible
    if (!done) { return WriteResult::Failure(ENOSPC); }
    done_size += done;
    data = reinterpret_cast<const uint8_t*>(data) + done;
    size -= done;
  }
  return WriteResult::Success(done_size);
}

} // namespace raw

namespace cxx {

size_t write(int fd, const void* data, size_t size);
void write_exact(int fd, const void* data, size_t size);

} // namespace cxx

} // namespace io
} // namespace libc
