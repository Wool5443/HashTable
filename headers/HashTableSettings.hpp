#pragma once

#include "Utils.hpp"

typedef const char* hashTableKey_t;

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
    HashTableElement* value;
    ErrorCode         error;
};
