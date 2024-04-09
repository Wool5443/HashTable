#pragma once

#include "Utils.hpp"

uint64_t ZeroHash(const void* data, size_t size, uint64_t seed);

uint64_t FirstCharHash(const void* data, size_t size, uint64_t seed);

uint64_t LengthHash(const void* data, size_t size, uint64_t seed);

uint64_t SumLengthHash(const void* data, size_t size, uint64_t seed);

uint64_t SumHash(const void* data, size_t size, uint64_t seed);
