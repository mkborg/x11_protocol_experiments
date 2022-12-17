#include "test_XauGetBestAuthByAddr.h"

#include "dump_authorization_data.h"

#include <logger/logger.h>
#include <utils/PREPROCESSOR.h>
#include <x11_constants/x11_constants.h>
#include <x11_xauth/x11_xauth.h>

static char const * const auth_names[] =
{
  ::x11::constants::AUTH_PROTO_MIT_MAGIC_COOKIE,
  ::x11::constants::AUTH_PROTO_XDM_AUTHORIZATION,
};
static const int auth_names_lens[] =
{
  CONSTSTRLEN(::x11::constants::AUTH_PROTO_MIT_MAGIC_COOKIE),
  CONSTSTRLEN(::x11::constants::AUTH_PROTO_XDM_AUTHORIZATION),
};
static_assert(ARRAY_SIZE(auth_names) == ARRAY_SIZE(auth_names_lens),
    "'auth_names_lens' doesn't match 'auth_names'");

void test_XauGetBestAuthByAddr()
{
  unsigned short family = FamilyLocal; // 256
  unsigned short address_length = CONSTSTRLEN("i7");
  const char * address = "i7";
  unsigned short number_length = CONSTSTRLEN("0");
  const char * number = "0";

  const auto auth = ::x11::xauth::getBestByAddr(
      family,
      address_length, address,
      number_length, number, 
      ARRAY_SIZE(auth_names), auth_names, auth_names_lens);
  if (!auth) {
    EPRINTF("%s() failure", "::x11::auth::getBestByAddr");
  } else {
    IPRINTF("%s() success", "::x11::auth::getBestByAddr");
    dump_authorization_data(auth);
  }
}
