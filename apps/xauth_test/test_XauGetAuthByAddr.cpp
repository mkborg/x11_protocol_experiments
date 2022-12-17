#include "test_XauGetAuthByAddr.h"

#include "dump_authorization_data.h"

#include <logger/logger.h>
#include <utils/PREPROCESSOR.h>
#include <x11_constants/x11_constants.h>
#include <x11_xauth/x11_xauth.h>

void test_XauGetAuthByAddr()
{
  unsigned short family = FamilyLocal; // 256
  unsigned short address_length = CONSTSTRLEN("i7");
  const char * address = "i7";
  unsigned short number_length = CONSTSTRLEN("0");
  const char * number = "0";
  unsigned short name_length = CONSTSTRLEN(::x11::constants::AUTH_PROTO_MIT_MAGIC_COOKIE);
  const char* name = ::x11::constants::AUTH_PROTO_MIT_MAGIC_COOKIE;

  const auto auth = ::x11::xauth::getByAddr(family, address_length, address, number_length, number, name_length, name);
  if (!auth) {
    EPRINTF("%s() failure", "::x11::auth::getByAddr");
  } else {
    IPRINTF("%s() success", "::x11::auth::getByAddr");
    dump_authorization_data(auth);
  }
}
