#include <libc/file/stream/fopen.h>

#include <exceptions/system_error.h>

namespace libc {
namespace file {
namespace stream {
namespace cxx {

FILE * open(const char *path, const char *mode)
{
  const auto r = ::libc::file::stream::raw::open(path, mode);
  if (!r)
  {
    throw SYSTEM_ERROR_PRINTF(r.raw().error(), "%s(%s,%s)", "::libc::file::stream::open", path, mode);
  }
  return r.raw().result();
}

} // namespace cxx
} // namespace stream
} // namespace file
} // namespace libc
