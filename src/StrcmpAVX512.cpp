#include <immintrin.h>
#include "StrcmpAVX512.hpp"

bool StrcmpAVX512(const char* s1, const char* s2)
{
    MyAssertSoft(s1, ERROR_NULLPTR);
    MyAssertSoft(s2, ERROR_NULLPTR);

    __m512i s1_intr = _mm512_load_epi64(s1);
    __m512i s2_intr = _mm512_load_epi64(s2);

    __mmask64 cmp   = _mm512_cmp_epi8_mask(s1_intr, s2_intr, _MM_CMPINT_EQ);

    return cmp == (~(uint64_t)0);
}
