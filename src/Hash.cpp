#include "Hash.hpp"

uint64_t LengthHash(const void* data, size_t size, uint64_t seed)
{
    uint64_t hash = 0;
    
    for (size_t i = 0; i < size; i++)
        hash += ((uint8_t*)data)[i];

    return hash;
}
