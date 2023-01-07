#pragma once

#include <string>

namespace x11 {
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

  inline const std::string& protocol() const { return protocol_; }
  inline const std::string& host() const { return host_; }
  inline unsigned short display() const { return display_; }
  inline unsigned short screen() const { return screen_; }
};

} // namespace connection
} // namespace x11
