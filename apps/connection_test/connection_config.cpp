#include "connection_config.h"

#include "exceptions/runtime_error.h"
#include "logger/debug.h"

#include <string>

namespace x11 {
namespace client2server {
namespace connection {

// [[protocol/]hostname:]displaynumber[.screennumber]
Config Config::makeConfig(const std::string& displayConfigString)
{
  std::string protocol;
  std::string host;
  unsigned short display = 0;

  const auto displayConfigString_size = displayConfigString.size();
  bool slash_seen = false;
  bool colon_seen = false;
  bool dot_seen = false;
  unsigned s = 0;
  unsigned i = 0;
  for (; i < displayConfigString_size; ++i) {
    switch (displayConfigString[i]) {
      case '/':
      {
        if (slash_seen || colon_seen || dot_seen) {
          throw RUNTIME_ERROR("invalid format");
        }
        slash_seen = true;
        protocol = displayConfigString.substr(s, i - s);
        s = i + 1;
        break;
      }
      case ':':
      {
        if (colon_seen || dot_seen) {
          throw RUNTIME_ERROR("invalid format");
        }
        colon_seen = true;
        host = displayConfigString.substr(s, i - s);
        s = i + 1;
        break;
      }
      case '.':
      {
        if (dot_seen) {
          throw RUNTIME_ERROR("invalid format");
        }
        dot_seen = true;
        const auto display_n = std::stoull(displayConfigString.substr(s, i - s));
        display = display_n;
        s = i + 1;
        break;
      }
      default:
      {
        break;
      }
    }
  }
  const auto screen = (unsigned short) std::stoull(displayConfigString.substr(s, i - s));
  DPRINTF("protocol='%s' host='%s' display=%u screen=%u", protocol.c_str(), host.c_str(), display, screen);
  return Config(protocol, host, display, screen);
}

} // namespace connection
} // namespace client2server
} // namespace x11
