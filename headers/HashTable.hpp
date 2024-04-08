#pragma once

#include "LinkedList.hpp"
#include "HashTableSettings.hpp"

typedef uint64_t (*hashFunction_t)(const void* data, size_t length, uint64_t seed);

struct HashTable
{
    LinkedList*    containers;
    size_t         containersCount;
    hashFunction_t hashFunc;

    const char*    logFolder;

    ErrorCode              Init(size_t containersCount, hashFunction_t hashFunc, const char* logFolder);
    ErrorCode              Destructor();

    ErrorCode              Verify();

    ErrorCode              Add(hashTableKey_t key, size_t keySize);

    ErrorCode              Remove(hashTableKey_t key, size_t keySize);

    bool                   Contains(hashTableKey_t key, size_t keySize);

    HashTableElementResult Get(hashTableKey_t key, size_t keySize);
};

