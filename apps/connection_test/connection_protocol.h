#pragma once

#include "cxx_template/optional.h"
#include "cxx_template/optional_enum.h"

namespace x11 {
namespace client2server {
namespace raw {

using Protocol_storage_type = unsigned short;
enum class Protocol : Protocol_storage_type {
  tcp,   // TCP over IPv4 or IPv6
  inet,  // TCP over IPv4 only
  inet6, // TCP over IPv6 only
  unix,  // UNIX Domain Sockets (same host only)
  local, // Platform preferred local connection method

  COUNT
};
static const unsigned constexpr Protocol_COUNT = unsigned(Protocol::COUNT);

inline
bool isOK(Protocol protocol)
{
  return unsigned(protocol) < Protocol_COUNT;
}

inline
bool isNG(Protocol protocol)
{
  return !isOK(protocol);
}

Protocol toProtocol(const char* s);
const char* toString(Protocol protocol);

} // namespace raw

namespace cxx {

raw::Protocol toProtocol(const char* s);

class Protocol
{
private:
  raw::Protocol rawProtocol_;

public:
  Protocol(raw::Protocol rawProtocol = raw::Protocol::COUNT)
    : rawProtocol_(rawProtocol)
  {
  }

  Protocol(const char* s)
    : Protocol(toProtocol(s))
  {
  }

  const char* toString() const
  {
    return raw::toString(rawProtocol_);
  }

  operator raw::Protocol() const
  {
    return static_cast<raw::Protocol>(rawProtocol_);
  }

  operator raw::Protocol_storage_type() const
  {
    return static_cast<raw::Protocol_storage_type>(rawProtocol_);
  }
};

using OptionalProtocol = ::Template::Optional<Protocol>;

OptionalProtocol toOptionalProtocol(const char* s);

} // namespace cxx

using OptionalProtocol = ::Template::OptionalEnum<raw::Protocol,raw::Protocol::COUNT>;

inline
OptionalProtocol toOptionalProtocol(const char* s)
{
  return OptionalProtocol(raw::toProtocol(s));
}

} // namespace client2server
} // namespace x11
