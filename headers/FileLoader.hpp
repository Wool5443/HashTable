#pragma once

#include "HashTable.hpp"

struct LoadResult
{
    char* buffer;
    ErrorCode error;
};

LoadResult LoadFileToTable(HashTable* hashTable, const char* filePath);
