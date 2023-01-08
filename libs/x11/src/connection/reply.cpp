#include "x11/connection/reply.h"

#include "utils/PREPROCESSOR.h"

namespace x11 {
namespace connection {
namespace reply {

static char const * const names[] =
{
  "Failed"		, // 0
  "Success"		, // 1
  "Authenticate"	, // 2
};
char const * toString(Id id)
{
  return
      (unsigned(id) < ARRAY_SIZE(names))
          ? names[unsigned(id)]
          : "?";
}

} // namespace reply
} // namespace connection
} // namespace x11
