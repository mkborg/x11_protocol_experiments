#include <libc/getenv.h>

#include <exceptions/runtime_error.h>

namespace libc {
namespace cxx {

const char* getenv(const char* name)
{
  const auto libc_getenv_result = libc::getenv(name);
  if (!libc_getenv_result) {
    throw RUNTIME_ERROR_PRINTF("'%s' environment variable is undefined", name);
  }
  libc_getenv_result.raw().result();
}

} // namespace cxx
} // namespace libc
