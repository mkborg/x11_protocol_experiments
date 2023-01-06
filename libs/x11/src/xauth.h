#pragma once

#include <X11/Xauth.h>

namespace x11 {
namespace xauth {

inline
char *fileName(void)
{
  return ::XauFileName();
}

// Note: Initially 'XauDisposeAuth()' was returning 'int'.
// Currently it is returning 'void'.
inline
void dispose(Xauth *auth)
{
  ::XauDisposeAuth(auth);
}

inline
Xauth *read(FILE *auth_file)
{
  return ::XauReadAuth(auth_file);
}

inline
Xauth *getByAddr(
    unsigned short family,
    unsigned short address_length,
    const char *address,
    unsigned short number_length,
    const char *number,
    unsigned short name_length,
    const char* name)
{
  return ::XauGetAuthByAddr(
      family,
      address_length, address,
      number_length, number,
      name_length, name);
}

// '<X11/Xauth.h>' erroneously requires 'type_names' to be non-constant
inline
Xauth *getBestByAddr(
    unsigned short family,
    unsigned short address_length,
    const char *address,
    unsigned short number_length,
    const char *number,
    int types_length,
    char const * const * type_names,
    const int *type_lengths)
{
  return ::XauGetBestAuthByAddr(
      family,
      address_length, address,
      number_length, number,
      types_length, const_cast<char**>(type_names), type_lengths); 
}

} // namespace xauth
} // namespace x11
