#pragma once

#include "libc/result.h"

#include <stdio.h>

namespace libc {
namespace file {
namespace stream {

namespace raw {

using OpenResult = ::libc::Result<FILE *, 0>;
inline
OpenResult open(const char *pathname, const char *mode)
{
  return OpenResult(::fopen(pathname, mode));
}

} // namespace raw

namespace cxx {

FILE * open(const char *pathname, const char *mode);

} // namespace cxx

} // namespace stream
} // namespace file
} // namespace libc
