#pragma once

namespace x11 {
namespace client2server {
namespace protocol {

enum class Id {
  tcp,   // TCP over IPv4 or IPv6
  inet,  // TCP over IPv4 only
  inet6, // TCP over IPv6 only
  unix,  // UNIX Domain Sockets (same host only)
  local, // Platform preferred local connection method

  COUNT
};
static const unsigned constexpr Id_COUNT = unsigned(Id::COUNT);

Id toId(const char* s);
const char* toString(Id id);

} // namespace protocol
} // namespace client2server
} // namespace x11
