#include "dump_authorization_data.h"

#include "hex_string.h"
#include "logger/logger.h"
#include "x11/xauth.h"

/*
    #include <X11/Xauth.h>

    typedef struct xauth {
         unsigned short family;
         unsigned short address_length;
         char           *address;
         unsigned short number_length;
         char           *number;
         unsigned short name_length;
         char           *name;		// for example: MIT-MAGIC-COOKIE-1'
         unsigned short data_length;
         char           *data;
    } Xauth;

    mk: Looks like 'address', 'number' and 'name' are not terminated with 'zero' ('\0').
    mk: Looks like 'address' may be 'binary'
    mk: Looks like 'address' is 'textual' host's name or 'binary' representation of host's address.
    mk: Looks like 'number' is 'display number'.
    mk: Looks like 'data' is 'binary'.
*/
void dump_authorization_data(const Xauth * xauth)
{
  const auto data = toHexString(xauth->data, xauth->data_length);
  IPRINTF("family=%u address_length=%u address='%.*s' number_length=%u number='%.*s' name_length=%u name='%.*s' data_length=%u data='%s'",
      xauth->family,
      xauth->address_length, xauth->address_length, xauth->address,
      xauth->number_length, xauth->number_length, xauth->number,
      xauth->name_length, xauth->name_length, xauth->name,
      xauth->data_length, data.c_str());
}
