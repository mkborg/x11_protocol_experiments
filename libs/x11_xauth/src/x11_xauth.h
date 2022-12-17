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
void disposeAuth(Xauth *auth)
{
  ::XauDisposeAuth(auth);
}

inline
Xauth *readAuth(FILE *auth_file)
{
  return ::XauReadAuth(auth_file);
}

inline
Xauth *getAuthByAddr(
    unsigned short family,
    unsigned short address_length,
    char *address,
    unsigned short number_length,
    char *number,
    unsigned short name_length,
    const char* name)
{
  return ::XauGetAuthByAddr(
      family, address_length, address, number_length, number, name_length, name);
}

inline
Xauth *GetBestAuthByAddr(
    unsigned short family,
    unsigned short address_length,
    char *address,
    unsigned short number_length,
    char *number,
    int types_length,
    char **types,
    int *type_lengths)
{
  return ::XauGetBestAuthByAddr(
      family, address_length, address, number_length, number,
      types_length, types, type_lengths); 
}

} // namespace xauth
} // namespace x11
