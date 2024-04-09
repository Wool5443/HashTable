#pragma once

#include "HashTable.hpp"
#include "String.hpp"

struct Loaded
{
    String      buffer;
    SplitString split;
};

struct LoadedResult
{
    Loaded      value;
    ErrorCode   error;
};

LoadedResult LoadFileToTable(HashTable* hashTable, const char* filePath);
