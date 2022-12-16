#pragma once

#include "libc/result.h"

#include <stdio.h>

namespace libc {
namespace file {
namespace stream {
namespace raw {

using CloseResult = ::libc::Result<int>;
inline
int close(FILE *stream)
{
  return CloseResult(::fclose(stream));
}

} // namespace raw
} // namespace stream
} // namespace file
} // namespace libc
