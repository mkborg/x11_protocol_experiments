#pragma once

/// @brief    libc 'mkdir()' wrapped with 'libc::Result'

#include "libc/result.h"

#include <string>

#include <sys/stat.h>
#include <sys/types.h>

#if !defined DEFAULT_MKDIR_MODE
#define DEFAULT_MKDIR_MODE (S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)
#endif

namespace libc {
namespace raw {

using MkdirResult = ::libc::Result<int>;

inline MkdirResult mkdir(const char* path, mode_t mode)
{
  return MkdirResult(::mkdir(path, mode));
}

inline MkdirResult mkdir(const std::string& path, mode_t mode)
{
  return mkdir(path.c_str(), mode);
}

MkdirResult mkdirs(const char* path, mode_t mode);

inline MkdirResult mkdirs(const std::string& path, mode_t mode)
{
  return mkdirs(path.c_str(), mode);
}

MkdirResult parent_mkdirs(const char* path, mode_t mode);

inline MkdirResult parent_mkdirs(const std::string& path, mode_t mode)
{
  return parent_mkdirs(path.c_str(), mode);
}

} // namespace raw

namespace cxx {

void mkdirs(const char* path, mode_t mode);

inline void mkdirs(const std::string& path, mode_t mode)
{
  mkdirs(path.c_str(), mode);
}

void parent_mkdirs(const char* path, mode_t mode);

inline void parent_mkdirs(const std::string& path, mode_t mode)
{
  parent_mkdirs(path.c_str(), mode);
}

} // namespace cxx
} // namespace libc
