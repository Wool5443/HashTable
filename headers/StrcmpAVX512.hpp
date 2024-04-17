#pragma once

#include "Utils.hpp"

/**
 * @brief Strcmp using AVX512. Only works for English words since they are not that long.
 * Addresses must be 64 byte alligned.
 * 
 * @param s1
 * @param s2
 * @return int - comparison result
 */
int StrcmpAVX512(const char* s1, const char* s2);
