#pragma once

#include "HashTable.hpp"

#define DumpHashTableText(hashTable, error, outTextPath)                    \
do                                                                          \
{                                                                           \
    SourceCodePosition _caller = { __FILE__, __LINE__, __func__ };          \
    _dumpHashTableText(hashTable, error, outTextPath, &_caller);            \
} while (0)
ErrorCode _dumpHashTableText(HashTable* hashTable, ErrorCode error, const char* outTextPath, 
                             SourceCodePosition* caller);


#define DumpHashTable(hashTable, error, outTextPath)                        \
do                                                                          \
{                                                                           \
    SourceCodePosition _caller = { __FILE__, __LINE__, __func__ };          \
    _dumpHashTable(hashTable, error, outTextPath, &_caller);                \
} while (0)
ErrorCode _dumpHashTable(HashTable* hashTable, ErrorCode error, const char* outTextPath, 
                         SourceCodePosition* caller);
