#pragma once

/// @brief    libc 'unlink()' wrapped with 'libc::Result'

#include "libc/result.h"

#include <string>

#include <unistd.h>	// unlink()

namespace libc {
namespace file {

using UnlinkResult = ::libc::Result<int>;

inline UnlinkResult unlink(const char* path)
{
  return UnlinkResult(::unlink(path));
}

inline UnlinkResult unlink(const std::string& path)
{
  return unlink(path.c_str());
}

} // namespace file
} // namespace libc
