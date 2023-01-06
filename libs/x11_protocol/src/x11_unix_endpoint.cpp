#include "x11_unix_endpoint.h"

#include "cxx/printf.h"

namespace x11 {
namespace unix {

namespace endpoint {

std::string path(unsigned short display)
{
  return cxx::printf("/tmp/.X11-unix/X%u", display);
}

} // namespace endpoint

/*
class EndPoint
{
};
*/

} // namespace unix
} // namespace x11
