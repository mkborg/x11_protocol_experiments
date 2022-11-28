#include "connection.h"

#include <libc/getenv.h>

namespace x11 {
namespace client2server {

Connection::Connection()
  : Connection(libc::cxx::getenv("DISPLAY"))
{
}

Connection::Connection(const std::string& display)
{
}

} // namespace client2server
} // namespace x11
