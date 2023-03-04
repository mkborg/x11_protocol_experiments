#include "escape_control_bytes.h"

#include "cxx/printf.h"

std::string escape_control_bytes(const std::string s)
{
  std::string r;
  const auto size = s.size();
  for (unsigned i = 0; i < size; ++i) {
    const auto b = static_cast<unsigned char>(s[i]);
    if (b >= '\x20') {
      r += b;
    } else {
      r += '\\';
      switch (b) {
        case '\x07': r += 'a'; break; // alert/beep/bell
        case '\x08': r += 'b'; break; // backspace
        case '\x09': r += 't'; break; // horizontal tab
        case '\x0A': r += 'n'; break; // newline (line feed)
        case '\x0B': r += 'v'; break; // vertical tab
        case '\x0C': r += 'f'; break; // formfeed page break
        case '\x0D': r += 'r'; break; // carriage return
        case '\x1B': r += 'e'; break; // escape
        default: // 0..7, x0E..x1A, x1C00x1F
          r += ::cxx::printf("%02X", b); break;
      }
    }
  }
  return r;
}
