#pragma once

#include "LinkedList.hpp"
#include "HashTableSettings.hpp"

typedef uint64_t (*hashFunction_t)(const void* data, size_t length, uint64_t seed);

/** @struct HashTableElement
 * @brief Struct for hash table elements
 * 
 * @var HashTableElement::key - key in hash table
 */
struct HashTableElement
{
    hashTableKey_t key;
    size_t         count;
};

struct HashTableElementResult
{
    HashTableElement value;
    ErrorCode        error;
};

struct HashTable
{
    LinkedList*    containers;
    size_t         containersCount;
    hashFunction_t hashFunc;

    const char*    logFolder;

    ErrorCode              Init(size_t containersCount, hashFunction_t hashFunc, const char* logFolder);

    ErrorCode              Verify();

    ErrorCode              Add(hashTableKey_t key);

    ErrorCode              Remove(hashTableKey_t key);

    bool                   Contains(hashTableKey_t key);

    HashTableElementResult Get(hashTableKey_t key);
};

#define DumpHashTable(hashTable, error, outTextPath)                        \
do                                                                          \
{                                                                           \
    SourceCodePosition _caller = { __FILE__, __LINE__, __func__ };          \
    return _dumpHashTable(hashTable, error, outTextPath, &_caller);         \
} while (0)
ErrorCode _dumpHashTable(HashTable* hashTable, ErrorCode error, const char* outTextPath, 
                         SourceCodePosition* caller);
