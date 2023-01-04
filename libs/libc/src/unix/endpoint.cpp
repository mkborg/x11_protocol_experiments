#include "libc/unix/endpoint.h"

#include "logger/debug.h"
#include "libc/file/unlink.h"
#include "libc/mkdirs.h"
#include "utils/assert.h"

#include <string.h>             // strncpy(), strerror()
#include <sys/socket.h>         // AF_*, SOCK_*

#define sizeof_field(TYPE, MEMBER) sizeof((((TYPE *)0)->MEMBER))

/*
    [linux-5.10.76/include/uapi/linux/un.h]

    #define UNIX_PATH_MAX   108
    struct sockaddr_un {
        __kernel_sa_family_t sun_family; // AF_UNIX
        char sun_path[UNIX_PATH_MAX];   // pathname
    };

    Note: Linux kernel does not require 'sockaddr_un.sun_path' to be zero
    terminated. It means that Linux kernel may return 'sockaddr_un' with
    'sun_path' completely filled by non-zero bytes without teminating zero.
*/

namespace libc {
namespace unix {

std::string EndPoint::socketPath() const
{
  const auto p = static_cast<const struct sockaddr_un*>(data());
  return std::string(p->sun_path, sizeof(p->sun_path));
}

// Note: 'socketPath' length must be less than 'sun_path' capacity to
// accomodate terminating '\0'
EndPoint::EndPoint(const char* socketPath)
{
  DPRINTF9("socketPath='%s'", socketPath);
  size_t len = strlen(socketPath);
  DPRINTF9("len=%zu sizeof(sockaddr_un.sun_path)=%zu", len, sizeof_field(sockaddr_un, sun_path));
  ASSERT(len <= sizeof_field(sockaddr_un, sun_path));
  struct sockaddr_un& a = *static_cast<struct sockaddr_un*>(data());
  a.sun_family = AF_UNIX;
  // Note: 'stringop-truncation' warning is produced here by errror
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstringop-truncation"
  ::strncpy(a.sun_path, socketPath, sizeof(a.sun_path));
#pragma GCC diagnostic pop
  DPRINTF9("");
}

} // namespace unix
} // namespace libc
