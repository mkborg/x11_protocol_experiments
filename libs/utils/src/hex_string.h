#pragma once

/// @brief    Helper to convert binary data into hexadecimal text string

#include <string>
#include <stddef.h>

std::string toHexString(const void* data, size_t size);
