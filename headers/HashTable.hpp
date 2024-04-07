#pragma once

#include "LinkedList.hpp"
#include "HashTableSettings.hpp"

typedef uint64_t (*hashFunction_t)(const void* data, size_t length, uint64_t seed);

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

    ErrorCode              Init(size_t containersCount, hashFunction_t hashFunc);

    ErrorCode              Verify();

    void                   DumpText();

    ErrorCode              Add(hashTableKey_t key);

    ErrorCode              Remove(hashTableKey_t key);

    bool                   Contains(hashTableKey_t key);

    HashTableElementResult Get(hashTableKey_t key);
};
