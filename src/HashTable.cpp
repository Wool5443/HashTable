// #include <stdlib.h>
#include "HashTable.hpp"

ErrorCode HashTable::Init(size_t containersCount, hashFunction_t hashFunc)
{
    if (containersCount == 0) return ERROR_BAD_NUMBER;
    if (!hashFunc)            return ERROR_NULLPTR;

    LinkedList* containers = (LinkedList*)calloc(containersCount, sizeof(*containers));
    if (!containers) return ERROR_NO_MEMORY;

    this->containersCount = containersCount;
    this->containers      = containers;
    this->hashFunc        = hashFunc;

    return EVERYTHING_FINE;
}

ErrorCode HashTable::Verify()
{
    if (this->containersCount == 0) return ERROR_BAD_FIELDS;
    if (!this->containers)          return ERROR_NO_MEMORY;
    if (!this->hashFunc)            return ERROR_NULLPTR;

    return EVERYTHING_FINE;
}
