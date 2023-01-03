#include "dump_authorization_file.h"
#include "test_XauGetAuthByAddr.h"
#include "test_XauGetBestAuthByAddr.h"

#include "libc/getenv.h"
#include "logger/logger.h"
#include "x11_constants/x11_constants.h"

int main()
{
  dump_authorization_file();

  if (!::libc::getenv(::x11::constants::environment::DISPLAY)) {
    IPRINTF("environment variable '%s' is undefined", ::x11::constants::environment::DISPLAY);
  } else {
    test_XauGetAuthByAddr();
    test_XauGetBestAuthByAddr();
  }

  return 0;
}
