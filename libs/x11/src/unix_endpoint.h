#pragma once

#include "libc/unix/endpoint.h"

#include <string>

namespace x11 {
namespace unix {

namespace endpoint {

std::string path(unsigned short display);

} // namespace endpoint

class EndPoint
  : public ::libc::unix::EndPoint
{
public:
  EndPoint(unsigned short display)
    : ::libc::unix::EndPoint(endpoint::path(display))
  {
  }
};

} // namespace unix
} // namespace x11
