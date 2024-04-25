#include <immintrin.h>
#include "StrcmpAVX.hpp"

bool StrcmpAVX(const char* s1, const char* s2)
{
    MyAssertSoft(s1, ERROR_NULLPTR);
    MyAssertSoft(s2, ERROR_NULLPTR);

    __m256i s1Vector = _mm256_loadu_epi8(s1);
    __m256i s2Vector = _mm256_loadu_epi8(s2);

    __m256i difference = _mm256_xor_epi64(s1Vector, s2Vector);

    __mmask32 res = _mm256_test_epi8_mask(difference, difference);

    return res == 0;
}
