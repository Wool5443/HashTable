#pragma once

#include <immintrin.h>
#include "Utils.hpp"

/**
 * @brief strcmp written using avx2 instructions. Only works for words shorter than 32.
 * 
 * @param s1
 * @param s2
 * @return bool equality
 */
bool StrcmpAVX(const char* s1, const char* s2);
