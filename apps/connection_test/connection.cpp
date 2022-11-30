#include "connection.h"

#include <libc/getenv.h>

#include "logger/debug.h"

namespace x11 {
namespace client2server {

Connection::Connection()
  : Connection(libc::cxx::getenv("DISPLAY"))
{
}

Connection::Connection(const std::string& display)
{
  DPRINTF("display='%s'", display.c_str());
}

} // namespace client2server
} // namespace x11
