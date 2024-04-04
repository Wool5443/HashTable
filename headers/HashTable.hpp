#pragma once

#include "LinkedList.hpp"
#include "HashTableSettings.hpp"

typedef uint64_t (*hashFunction_t)(const void* data);

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
    LinkedList* containers;
    hashFunction_t hashF;

    ErrorCode              Init();

    ErrorCode              Add(hashTableKey_t key);

    ErrorCode              Remove(hashTableKey_t key);

    bool                   Contains(hashTableKey_t key);

    HashTableElementResult Get(hashTableKey_t key);
};
