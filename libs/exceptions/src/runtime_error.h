#pragma once

/// @brief 'RUNTIME_ERROR_PRINTF()' convenience wrapper

#include "cxx/printf.h"

#include <stdexcept> // std::runtime_error

#define RUNTIME_ERROR(message) \
    std::runtime_error(message)

#define RUNTIME_ERROR_PRINTF(format, args...) \
    std::runtime_error(::cxx::printf(format, ##args))
