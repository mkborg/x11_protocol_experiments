#include "libc/io/write.h"

/// @brief libc 'write()' wrapped with 'libc::Result'

#include "exceptions/system_error.h"

namespace libc {
namespace io {
namespace cxx {

size_t write(int fd, const void* data, size_t size)
{
retry:
  const auto r = ::libc::io::raw::write(fd, data, size);
  if (!r)
  {
    const auto errorNumber = r.raw().error();
    if (EINTR == errorNumber) { goto retry; }
    throw SYSTEM_ERROR(errorNumber, "write");
  }
  return r.raw().result();
}

void write_exact(int fd, const void* data, size_t size)
{
  const auto r = ::libc::io::raw::write_exact(fd, data, size);
  if (!r)
  {
    const auto errorNumber = r.raw().error();
    throw SYSTEM_ERROR(errorNumber, "write");
  }
  // Note: in case of success 'r.raw().result() == size'
}

} // namespace cxx
} // namespace io
} // namespace libc
