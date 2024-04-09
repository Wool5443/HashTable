#include <string.h>
#include "Hash.hpp"

uint64_t ZeroHash(const void* data, size_t size, uint64_t seed)
{
    return 0;
}

uint64_t FirstCharHash(const void* data, size_t size, uint64_t seed)
{
    return *(char*)data;
}

uint64_t LengthHash(const void* data, size_t size, uint64_t seed)
{
    return size;
}

uint64_t SumLengthHash(const void* data, size_t size, uint64_t seed)
{
    return SumHash(data, size, seed) / size;
}

uint64_t SumHash(const void* data, size_t size, uint64_t seed)
{
    uint64_t hash = 0;
    
    for (size_t i = 0; i < size; i++)
        hash += ((uint8_t*)data)[i];

    return hash;
}
