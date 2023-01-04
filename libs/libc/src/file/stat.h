#pragma once

/// @brief    libc 'stat()' wrapped with 'libc::Result'

#include "libc/result.h"

#include <string>

#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace libc {
namespace file {

namespace raw {

using StatResult = Result<int>;

inline StatResult stat(int fd, struct stat *statbuf)
{
  return StatResult(::fstat(fd, statbuf));
}

inline StatResult lstat(const char* path, struct stat *statbuf)
{
  return StatResult(::lstat(path, statbuf));
}

inline StatResult lstat(const std::string& path, struct stat *statbuf)
{
  return ::libc::file::raw::lstat(path.c_str(), statbuf);
}

inline StatResult stat(const char* path, struct stat *statbuf)
{
  return StatResult(::stat(path, statbuf));
}

inline StatResult stat(const std::string& path, struct stat *statbuf)
{
  return ::libc::file::raw::stat(path.c_str(), statbuf);
}

} // namespace raw

namespace cxx {

struct stat lstat(const char* path);
struct stat stat(int fd);
struct stat stat(const char* path);

} // namespace cxx

} // namespace file
} // namespace libc
