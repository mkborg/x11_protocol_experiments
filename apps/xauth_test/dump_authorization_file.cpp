#include "dump_authorization_file.h"

#include "dump_authorization_data.h"

//#include "hex_string.h"
#include "libc/file/stream/handle.h"
//#include "logger/logger.h"
#include "x11_xauth/x11_xauth.h"

/*

    #include <X11/Xauth.h>

    typedef struct xauth {
         unsigned short family;
         unsigned short address_length;
         char           *address;
         unsigned short number_length;
         char           *number;
         unsigned short name_length;
         char           *name;
         unsigned short data_length;
         char           *data;
    } Xauth;

    mk: Looks like 'address', 'number' and 'name' are not terminated with 'zero' ('\0').
    mk: Looks like 'address' is 'host name'.
    mk: Looks like 'number' is 'display number'.
    mk: Looks like 'data' is 'binary'.
*/
void dump_authorization_file()
{
  const auto x11_xauth_fileName = ::x11::xauth::fileName();
  const auto fileStream = ::libc::file::Stream(::libc::file::stream::cxx::open(x11_xauth_fileName, "rb"));
  const auto fileStreamHandle = fileStream.get();
  for (;;) {
    const auto xauth = ::x11::xauth::read(fileStreamHandle);
    if (!xauth) { break; }
    dump_authorization_data(xauth);
    ::x11::xauth::dispose(xauth);
  }
}
