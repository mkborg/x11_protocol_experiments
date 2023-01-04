/// @brief    libc 'stat()' wrapped with 'libc::Result'

#include "libc/file/stat.h"

#include "exceptions/system_error.h"

namespace libc {
namespace file {
namespace cxx {

struct stat stat(int fd)
{
  struct stat stat;
  const auto r = ::libc::file::raw::stat(fd, &stat);
  if (!r)
  {
    throw SYSTEM_ERROR(r.raw().error(), "stat");
  }
  return stat;
}

struct stat lstat(const char* path)
{
  struct stat stat;
  const auto r = ::libc::file::raw::lstat(path, &stat);
  if (!r)
  {
    throw SYSTEM_ERROR_PRINTF(r.raw().error(), "%s('%s')", "lstat", path);
  }
  return stat;
}

struct stat stat(const char* path)
{
  struct stat stat;
  const auto r = ::libc::file::raw::stat(path, &stat);
  if (!r)
  {
    throw SYSTEM_ERROR_PRINTF(r.raw().error(), "%s('%s')", "stat", path);
  }
  return stat;
}

} // namespace cxx
} // namespace file
} // namespace libc
