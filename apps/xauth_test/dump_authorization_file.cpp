#include "dump_authorization_file.h"

#include <libc/file/stream/handle.h>
#include <logger/logger.h>

#include "cxx_Xau/Xau.h"
#include <hex_string.h>

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

    mk: Looks like 'address' is 'host name'.
    mk: Looks like 'number' is 'display number'.
    mk: Looks like 'data' is 'binary'.
*/
void dump_authorization_file()
{
  const auto xau_fileName = ::cxx::Xau::fileName();
  const auto fileStream = ::libc::file::Stream(::libc::file::stream::cxx::open(xau_fileName, "r"));
  const auto fileStreamHandle = fileStream.get();
  for (;;) {
    const auto xauth = ::cxx::Xau::readAuth(fileStreamHandle);
    if (!xauth) { break; }
    const auto data = toHexString(xauth->data, xauth->data_length);
    IPRINTF("family=%u address_length=%u address='%s' number_length=%u number='%s' name_length=%u name='%s' data_length=%u data='%s'",
        xauth->family, xauth->address_length, xauth->address, xauth->number_length, xauth->number, xauth->name_length,
        //xauth->name, xauth->data_length, xauth->data);
        xauth->name, xauth->data_length, data.c_str());
  }
}
