#pragma once

#include <string>

namespace x11 {
namespace client2server {
namespace connection {

class Config
{
private:
  std::string protocol_;
  std::string host_;
  unsigned short display_;
  unsigned short screen_;

  Config makeConfig(const std::string& display);

protected:

public:
  Config(const std::string& protocol, const std::string& host, unsigned short display, unsigned short screen)
    : protocol_(protocol), host_(host), display_(display), screen_(screen)
  {
  }
  Config(const Config& other) = default;
  Config(const std::string& display)
    : Config(makeConfig(display))
  {
  }
};

} // namespace connection
} // namespace client2server
} // namespace x11
