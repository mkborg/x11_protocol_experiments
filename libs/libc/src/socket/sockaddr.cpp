#include "libc/socket/sockaddr.h"

#include "cxx/printf.h"

#include <arpa/inet.h>		// htonl(), htons(), ntohl(), ntohs()

namespace libc {
namespace socket {

/*

    The <sys/socket.h> header shall define the sockaddr structure, which
    shall include at least the following members:

      sa_family_t  sa_family  Address family.
      char         sa_data[]  Socket address (variable-length data).


    man 3 inet_ntop
    man 3 inet_pton

    #include <arpa/inet.h>
    const char *inet_ntop(int af, const void *restrict src, char *restrict dst, socklen_t size);
    int inet_pton(int af, const char *restrict src, void *restrict dst);

*/
std::string toString(const struct sockaddr* sa, socklen_t socklen)
{
  if (!sa) {
    return "?";
  }

  if (socklen < sizeof(sa_family_t)) {
    return "?";
  }

  switch (sa->sa_family)
  {
    case AF_INET:
    {
      if (socklen < sizeof(struct sockaddr_in)) {
        return "?";
      }
      const auto a = reinterpret_cast<const struct sockaddr_in*>(sa);
      const auto ip = static_cast<unsigned>(ntohl(a->sin_addr.s_addr));
      return cxx::printf("%u.%u.%u.%u:%u",
#if 0
          static_cast<const unsigned char*>(&a->sin_addr.s_addr)[0],
          static_cast<const unsigned char*>(&a->sin_addr.s_addr)[1],
          static_cast<const unsigned char*>(&a->sin_addr.s_addr)[2],
          static_cast<const unsigned char*>(&a->sin_addr.s_addr)[3],
#else
          (ip >> (8 * 3)) & 0xFF,
          (ip >> (8 * 2)) & 0xFF,
          (ip >> (8 * 1)) & 0xFF,
          (ip >> (8 * 0)) & 0xFF,
#endif
          ntohs(a->sin_port)
      );
    }
    case AF_INET6:
    {
      if (socklen < sizeof(struct sockaddr_in6)) {
        return "?";
      }
      const auto a = reinterpret_cast<const struct sockaddr_in6*>(sa);
      const auto ip = reinterpret_cast<const unsigned char*>(&a->sin6_addr.s6_addr);
      return cxx::printf("[%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X]:%u",
          ip[0], ip[1], ip[ 2], ip[ 3], ip[ 4], ip[ 5], ip[ 6], ip[ 7],
          ip[8], ip[9], ip[10], ip[11], ip[12], ip[13], ip[14], ip[15],
          ntohs(a->sin6_port)
      );
    }

    default:
      return "?";
  }
}

} // namespace socket
} // namespace libc
