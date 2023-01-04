/// @brief    libc 'mkdir()' wrapped with 'libc::Result'

#include "libc/mkdirs.h"

#include "exceptions/system_error.h"
#include "libc/file/stat.h"

#include <limits.h>             // PATH_MAX
#include <string.h>             // memcpy(), strrchr)

namespace libc {
namespace raw {
namespace impl {

// creates last subdirectory if it is missing in path
static MkdirResult mkdir(const char* path, mode_t mode)
{
  // Note: Both 'stat()' and 'mkdir()' fail if path is empty
  if (!*path)
  {
    return MkdirResult::Success(0);
  }
  struct stat stat;
  const auto statResult = libc::file::raw::stat(path, &stat);
  if (!statResult)
  {
    const auto stat_errorNumber = statResult.raw().error();
    if (ENOENT != stat_errorNumber)
    {
      return MkdirResult::Failure(stat_errorNumber);
    }
    /*
        Note: There is risk of 'race' between two processes simultaneously
        reaching this point between 'stat' above and 'mkdir' below. In such case
        one of processes will fail in 'mkdir' below with 'EEXIST'.
    */
    // 'path' is missing
    const auto mkdirResult = libc::raw::mkdir(path, mode);
    if (!mkdirResult)
    {
      const auto mkdir_errorNumber = mkdirResult.raw().error();
      if (EEXIST == mkdir_errorNumber)
      {
        return MkdirResult::Success(0);
      }
    }
    return mkdirResult;
  }
  else
  {
    // 'path' already exists
    if (!S_ISDIR(stat.st_mode))
    {
      return MkdirResult::Failure(ENOTDIR);
    }
  }
  return MkdirResult::Success(0);
}

} // namespace impl

// creates all directories missing in path
// returns zero on success or 'errno' on failure
MkdirResult mkdirs(const char* path, mode_t mode)
{
  // create intermediate subdirectories
  char dir[PATH_MAX];
  unsigned i = 0;
  char c;
  do
  {
    c = path[i];
    if ('/' == c)
    {
      dir[i] = '\0';
      // create intermediate subdirectory
      const auto r = impl::mkdir(dir, mode);
      if (!r) { return r; }
    }
    dir[i++] = c;
  } while (c);

  // create last subdirectory
  return impl::mkdir(path, mode);
}

MkdirResult parent_mkdirs(const char* path, mode_t mode)
{
  char dir[PATH_MAX];
  const char* p = strrchr(path, '/');
  if (!p)
  {
    // path without '/' separator
    return MkdirResult::Failure(EINVAL);
  }
  const size_t len = p - path;
  if (len >= PATH_MAX)
  {
    // path exceeds PATH_MAX
    return MkdirResult::Failure(ENAMETOOLONG);
  }
  memcpy(dir, path, len);
  dir[len] = '\0';
  return mkdirs(dir, mode);
}

} // namespace raw

namespace cxx {

void mkdirs(const char* path, mode_t mode)
{
  const auto r = ::libc::raw::mkdirs(path, mode);
  if (!r)
  {
    throw SYSTEM_ERROR_PRINTF(r.raw().error(), "%s('%s')", "mkdirs", path);
  }
}

void parent_mkdirs(const char* path, mode_t mode)
{
  const auto r = ::libc::raw::parent_mkdirs(path, mode);
  if (!r)
  {
    throw SYSTEM_ERROR_PRINTF(r.raw().error(), "%s('%s')", "parent_mkdirs", path);
  }
}

} // namespace cxx
} // namespace libc
