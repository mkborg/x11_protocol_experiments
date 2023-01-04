#include "libc/unix/socket_path.h"

#include "logger/debug.h"
#include "libc/file/unlink.h"
#include "libc/mkdirs.h"

namespace libc {
namespace unix {
namespace socket {
namespace path {

void remove(const char* socketPath)
{
  DPRINTF9("socketPath='%s'", socketPath);
  (void) libc::file::unlink(socketPath);
}

void remove(const std::string& socketPath)
{
  remove(socketPath.c_str());
}

void prepare(const char* socketPath)
{
  remove(socketPath);
  DPRINTF9("socketPath='%s'", socketPath);
  // FIXME: What shll be used here: 'libc::cxx::parent_mkdirs' or 'libc::raw::parent_mkdirs()'?
  (void) libc::cxx::parent_mkdirs(socketPath, DEFAULT_MKDIR_MODE);
}

void prepare(const std::string& socketPath)
{
  prepare(socketPath.c_str());
}

} // namespace path
} // namespace socket
} // namespace unix
} // namespace libc
