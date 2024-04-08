// #include <stdlib.h>
#include <string.h>
#include "HashTable.hpp"
#include "PrettyDumpList.hpp"

static const uint64_t seed = 0xabcfedfabfeacdfd;

#define GET_CNT_NUM this->hashFunc(key, keySize, seed) % this->containersCount

HashTableElementResult _get(HashTable* hashTable, hashTableKey_t key, size_t keySize, LinkedList* container);

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

ErrorCode HashTable::Destructor()
{
    RETURN_ERROR(this->Verify());

    for (size_t i = 0; i < this->containersCount; i++)
        RETURN_ERROR(this->containers[i].Destructor());

    this->containersCount = SIZET_POISON;
    this->hashFunc        = nullptr;
    this->logFolder       = nullptr;

    return EVERYTHING_FINE;
}

ErrorCode HashTable::Verify()
{
    if (this->containersCount == 0) return ERROR_BAD_FIELDS;
    if (!this->containers)          return ERROR_NO_MEMORY;
    if (!this->hashFunc)            return ERROR_NULLPTR;

    return EVERYTHING_FINE;
}

ErrorCode HashTable::Add(hashTableKey_t key, size_t keySize)
{
    LinkedList* container = &this->containers[GET_CNT_NUM];
    
    HashTableElementResult elem = _get(this, key, keySize, container);

    if (elem.error == EVERYTHING_FINE)
    {
        elem.value->count++;
        return EVERYTHING_FINE;
    }

    return container->PushBack({ key, 1 });
}

ErrorCode HashTable::Remove(hashTableKey_t key, size_t keySize)
{
    LinkedList* container = &this->containers[GET_CNT_NUM];

    HashTableElementResult elem = _get(this, key, keySize, container);

    RETURN_ERROR(elem.error);

    size_t index = (elem.value - container->data) / sizeof(*container->data);

    return container->Pop(index).error;
}

bool HashTable::Contains(hashTableKey_t key, size_t keySize)
{
    return _get(this, key, keySize, &this->containers[GET_CNT_NUM]).error == EVERYTHING_FINE;
}

HashTableElementResult HashTable::Get(hashTableKey_t key, size_t keySize)
{
    return _get(this, key, keySize, &this->containers[GET_CNT_NUM]);
}

HashTableElementResult _get(HashTable* hashTable, hashTableKey_t key, size_t keySize, LinkedList* container)
{
    if (container->length == 1)
        return { nullptr, ERROR_NOT_FOUND };

    for (size_t i = 1; i < container->length; i++)
        if (container->prev[i] != SIZET_POISON)
            if (container->data[i].key && strncmp(container->data[i].key, key, keySize) == 0)
                return { &container->data[i], EVERYTHING_FINE }; 

    return { nullptr, ERROR_NOT_FOUND };
}
