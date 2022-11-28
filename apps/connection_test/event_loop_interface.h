#include <cstdint>	// [u]int(8|16|32|64)_t

namespace event_loop {

// For performance reasons we can try to use 'void *' pointer, but 64-bit number will be safer
using handle = uint64_t;

} // namespace event_loop
