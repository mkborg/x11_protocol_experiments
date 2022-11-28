#pragma once

/// @brief    'SYSTEM_ERROR_PRINTF()' convenience wrapper

#include "cxx/printf.h"

#include <system_error>

/*
    std::system_error e;
    e.what() => "${message}: $(strerror(${error_number}))"
*/
#define SYSTEM_ERROR(error_number, message) \
    std::system_error(             \
        std::error_code(           \
            (error_number),        \
            std::system_category() \
        ),                         \
        message                    \
    )

#define SYSTEM_ERROR_PRINTF(error_number, format, args...) \
    SYSTEM_ERROR(error_number, ::cxx::printf(format, ##args))
