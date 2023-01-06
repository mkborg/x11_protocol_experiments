/// @brief libc 'read()' wrapped with 'libc::Result'

#include "libc/io/read.h"

#include "exceptions/system_error.h"

namespace libc {
namespace io {
namespace cxx {

size_t read(int fd, void* data, size_t size)
{
retry:
  const auto r = ::libc::io::raw::read(fd, data, size);
  if (!r)
  {
    const auto errorNumber = r.raw().error();
    if (EINTR == errorNumber) { goto retry; }
    throw SYSTEM_ERROR(errorNumber, "read");
  }
  return r.raw().result();
}

void read_exact(int fd, void* data, size_t size)
{
  const auto r = ::libc::io::raw::read_exact(fd, data, size);
  if (!r)
  {
    const auto errorNumber = r.raw().error();
    throw SYSTEM_ERROR(errorNumber, "read");
  }
  // Note: in case of success 'r.raw().result() == size'
}

} // namespace cxx

} // namespace io
} // namespace libc
