#pragma once

#include "logger/debug_level.h"
#include "logger/FUNCTION_NAME.h"
#include "logger/log_level.h"

#include <stddef.h>	// size_t

#ifdef __cplusplus
extern "C" {
#endif

void _log_hex_dump(logger_log_level_t logger_log_level, const char * file, unsigned line, const char * function, const void * p, size_t size);

#define xHEX(logger_log_level, p, size) \
	_log_hex_dump(logger_log_level, __FILE__, __LINE__, LOGGER_FUNCTION_NAME, p, size)

#define DHEXx(level, p, size) \
    do { \
        if (debug_level > (level - LOG_LEVEL_DEBUG)) { \
            xHEX(level, p, size); \
        } \
    } while(0)

#define DHEX(p, size) DHEXx(LOG_LEVEL_DEBUG, p, size)

#define DHEX0(p, size) DHEXx(LOG_LEVEL_DEBUG0, p, size)
#define DHEX1(p, size) DHEXx(LOG_LEVEL_DEBUG1, p, size)
#define DHEX2(p, size) DHEXx(LOG_LEVEL_DEBUG2, p, size)
#define DHEX3(p, size) DHEXx(LOG_LEVEL_DEBUG3, p, size)
#define DHEX4(p, size) DHEXx(LOG_LEVEL_DEBUG4, p, size)
#define DHEX5(p, size) DHEXx(LOG_LEVEL_DEBUG5, p, size)
#define DHEX6(p, size) DHEXx(LOG_LEVEL_DEBUG6, p, size)
#define DHEX7(p, size) DHEXx(LOG_LEVEL_DEBUG7, p, size)
#define DHEX8(p, size) DHEXx(LOG_LEVEL_DEBUG8, p, size)
#define DHEX9(p, size) DHEXx(LOG_LEVEL_DEBUG9, p, size)

#ifdef __cplusplus
}
#endif
