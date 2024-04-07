// #include <stdlib.h>
#include "HashTable.hpp"

ErrorCode HashTable::Init(size_t containersCount, hashFunction_t hashFunc, const char* logFolder)
{
    if (containersCount == 0) return ERROR_BAD_NUMBER;
    if (!hashFunc)            return ERROR_NULLPTR;

    LinkedList* containers = (LinkedList*)calloc(containersCount, sizeof(*containers));
    if (!containers) return ERROR_NO_MEMORY;

    for (size_t i = 0; i < containersCount; i++)
        containers[i].Init(logFolder);

    this->containersCount = containersCount;
    this->containers      = containers;
    this->hashFunc        = hashFunc;
    this->logFolder       = logFolder;

    return EVERYTHING_FINE;
}

ErrorCode HashTable::Verify()
{
    if (this->containersCount == 0) return ERROR_BAD_FIELDS;
    if (!this->containers)          return ERROR_NO_MEMORY;
    if (!this->hashFunc)            return ERROR_NULLPTR;

    return EVERYTHING_FINE;
}

void HashTable::DumpText()
{

}

ErrorCode HashTable::Add(hashTableKey_t key)
{
    return EVERYTHING_FINE;
}

ErrorCode HashTable::Remove(hashTableKey_t key)
{
    return EVERYTHING_FINE;
}

bool HashTable::Contains(hashTableKey_t key)
{
    return EVERYTHING_FINE;
}

HashTableElementResult HashTable::Get(hashTableKey_t key)
{
    return { 0, EVERYTHING_FINE };
}
