#include "logger/hex_dump.h"

#include "logger/log_line.h"

#include <stdio.h>	// snprintf()

//#define FILL_WITH_CONST_CHAR

#define HEX_DUMP_WIDTH 16
//#define HEX_DUMP_WIDTH 32

#define FILL_BUFFER(buffer, filler) \
    do { \
	memset((buffer), (filler), sizeof(buffer) - 1); \
	(buffer)[sizeof(buffer) - 1] = 0; \
    } while (0)


void _log_hex_dump(logger_log_level_t logger_log_level, const char * file, unsigned line,
    const char * function, const void * p, size_t size)
{
#if 0
  // "XX XX XX XX  XX XX XX XX  XX XX XX XX  XX XX XX XX"
  // "XX XX XX XX  XX XX XX XX  XX XX XX XX  XX XX XX XX  XX XX XX XX  XX XX XX XX  XX XX XX XX  XX XX XX XX"
  char hex_buf[HEX_DUMP_WIDTH*2 + HEX_DUMP_WIDTH-1 + (HEX_DUMP_WIDTH-1)/4 + 1];
#else
  // "XXXXXXXX XXXXXXXX XXXXXXXX XXXXXXXX"
  // "XXXXXXXX XXXXXXXX XXXXXXXX XXXXXXXX XXXXXXXX XXXXXXXX XXXXXXXX XXXXXXXX"
  char hex_buf[HEX_DUMP_WIDTH*2 + (HEX_DUMP_WIDTH-1)/4 + 1];
#endif
  // ".... .... .... ...."
  // ".... .... .... .... .... .... .... ...."
  char sym_buf[HEX_DUMP_WIDTH + (HEX_DUMP_WIDTH-1)/4 + 1];

  while(size) {

    unsigned hex_off = 0;
    unsigned sym_off = 0;
    unsigned off;

#if defined FILL_WITH_CONST_CHAR
    FILL_BUFFER(hex_buf, '#');
    FILL_BUFFER(sym_buf, '#');
#endif // defined FILL_WITH_CONST_CHAR

    for(off=0; off<HEX_DUMP_WIDTH && off<size; ++off) {
    //for(off=0; off<HEX_DUMP_WIDTH; ++off) {
      //char * d1 = (0!=off) ? " " : "";
      const char * d4 = (0!=off/4 && 0==off%4) ? " " : "";
      unsigned char b = ((unsigned char *)p)[off];
      //unsigned char b = (off<size) ? ((unsigned char *)p)[off] : 0;

      // "XX XX XX XX  XX XX XX XX  XX XX XX XX  XX XX XX XX  XX XX XX XX  XX XX XX XX  XX XX XX XX  XX XX XX XX"
#if 0
      hex_off += snprintf(hex_buf+hex_off, sizeof(hex_buf)-hex_off, "%s%s%02X", d1, d4, b);
#else
      hex_off += snprintf(hex_buf+hex_off, sizeof(hex_buf)-hex_off, "%s%02X", d4, b);
#endif
      if (hex_off >= sizeof(hex_buf)-1) { hex_off = sizeof(hex_buf)-1; }

      if (b >= 0x80) { b &= ~0x80; }
      if (b < ' ' || b == 0x7F) { b = '.'; }

      // ".... .... .... .... .... .... .... ...."
      sym_off+=snprintf(sym_buf+sym_off, sizeof(sym_buf)-sym_off, "%s%c", d4, b);
      if (sym_off >= sizeof(sym_buf)-1) { sym_off = sizeof(sym_buf)-1; }
    }

    for(; off<HEX_DUMP_WIDTH; ++off) {
      const char * d4 = (0!=off/4 && 0==off%4) ? " " : "";

      hex_off += snprintf(hex_buf+hex_off, sizeof(hex_buf)-hex_off, "%s..", d4);
      if (hex_off >= sizeof(hex_buf)-1) { hex_off = sizeof(hex_buf)-1; }

      sym_off += snprintf(sym_buf+sym_off, sizeof(sym_buf)-sym_off, "%s.", d4);
      if (sym_off >= sizeof(sym_buf)-1) { sym_off = sizeof(sym_buf)-1; }
    }

    logger_log_line(logger_log_level, function, line, file, "%08lX: %s %s", (unsigned long)p, hex_buf, sym_buf);

    if (off > size) { off = size; }
    size -= off;
    p = ((char *)p) + off;
  }
}
