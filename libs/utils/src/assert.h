#pragma once

/// @brief    Alternative 'assert' implementation

#include "exceptions/runtime_error.h"

#define ASSERT_TO_STRING(x) #x

#define ASSERT(expr) \
    do { \
      if (!(expr)) { \
        throw RUNTIME_ERROR_PRINTF("ASSERT(%s) failure", ASSERT_TO_STRING(expr)); \
      } \
    } while (0)

#define ASSERT_PRINTF(expr, format, args...) \
    do { \
      if (!(expr)) { \
        throw RUNTIME_ERROR_PRINTF(format, ##args); \
      } \
    } while (0)
