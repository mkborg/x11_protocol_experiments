#pragma once

#include "libc/result.h"

#include <cstdlib>

namespace libc {

typedef Result<const char*,0> GetEnvResult;

inline GetEnvResult getenv(const char* name)
{
  return GetEnvResult(::getenv(name));
}

namespace cxx {

const char* getenv(const char* name);

} // namespace cxx

} // namespace libc
