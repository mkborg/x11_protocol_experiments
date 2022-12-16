#pragma once

#include <libc/file/stream/fclose.h>
#include <libc/file/stream/fopen.h>

#include "cxx_template/deleter.h"
#include "cxx_template/handle.h"

#include "libc/result.h"

#include <stdio.h>

#if 0
FILE *fopen(const char *restrict pathname, const char *restrict mode);
FILE *fmemopen(void *buf, size_t size, const char *mode);
FILE *open_memstream(char **ptr, size_t *sizeloc);

int fseek(FILE *stream, long offset, int whence);
size_t fread(void *restrict ptr, size_t size, size_t nmemb, FILE *restrict stream);
size_t fwrite(const void *restrict ptr, size_t size, size_t nmemb, FILE *restrict stream);
int fflush(FILE *stream);

int fclose(FILE *stream);
#endif

namespace libc {
namespace file {
namespace stream {

inline
void x_fclose(FILE* h) { ::fclose(h); }
#if 0
using fileStreamDeleter = ::Template::Deleter<FILE, ::fclose>;
using Handle = ::Template::Handle<FILE*, nullptr, fileStreamDeleter>;
#else
//using Handle = ::Template::Handle<FILE*, nullptr, ::fclose>;
using Handle = ::Template::Handle<FILE*, nullptr, x_fclose>;
#endif

} // namespace stream

class Stream
  : private stream::Handle
{
public:
  Stream(FILE * handle)
    : stream::Handle(handle)
  {
  }

  Stream(const char* path, const char *mode)
    //: stream::Handle(stream::cxx::open(path, mode))
    : Stream(stream::cxx::open(path, mode))
  {
  }

  inline
  FILE* get() const
  {
    return stream::Handle::get();
  }

#if 0
  inline
  struct dirent* read()
  {
    return stream::read(stream::Handle::get()).result();
  }
#endif
};

} // namespace file
} // namespace libc
