/// @brief    Helper to convert binary data into hexadecimal text string

#include "hex_string.h"

#include <iomanip>              // std::setfill, std::hex, std::setw
#include <sstream>

std::string toHexString(const void* data, size_t size)
{
  std::ostringstream oss;
  oss << std::hex
      << std::uppercase
      << std::setfill('0');
  for (unsigned i=0; i<size; ++i)
  {
    unsigned b = static_cast<const unsigned char*>(data)[i];
    oss << std::setw(2)
        << b;
  }
  return oss.str();
}
