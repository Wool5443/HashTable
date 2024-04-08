// #include <stdlib.h>
#include "HashTable.hpp"
#include "PrettyDumpList.hpp"

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

#define PRINT_LOG_INDENT(indentSize, ...)   \
do                                          \
{                                           \
    WriteSpaces(outTextFile, indentSize);   \
    fprintf(outTextFile, __VA_ARGS__);      \
} while (0)
ErrorCode _dumpHashTable(HashTable* hashTable, ErrorCode error, const char* outTextPath,
                         SourceCodePosition* caller)
{
    MyAssertSoft(hashTable,   ERROR_NULLPTR);
    MyAssertSoft(outTextPath, ERROR_BAD_FILE);
    MyAssertSoft(caller,      ERROR_NULLPTR);

    FILE* outTextFile = fopen(outTextPath, "w");
    if (!outTextFile) return ERROR_BAD_FILE;

    PRINT_LOG_INDENT(0, "HashTable[%p] called from %s(%zu) %s()\n", hashTable,
                                                                    caller->fileName,
                                                                    caller->line,
                                                                    caller->name);
    PRINT_LOG_INDENT(0, "HashTable condition - %s[%d]\n", ERROR_CODE_NAMES[error], error);

    PRINT_LOG_INDENT(0, "{\n");
    PRINT_LOG_INDENT(4, "hash functions  = %p\n",  hashTable->hashFunc);
    PRINT_LOG_INDENT(4, "containersCount = %zu\n", hashTable->containersCount);
    PRINT_LOG_INDENT(4, "containers[%p]:\n",       hashTable->containers);

    PRINT_LOG_INDENT(4, "{\n");

    for (size_t i = 0; i < hashTable->containersCount; i++)
    {
        LinkedList* listPtr = &hashTable->containers[i];
        ErrorCode   listErr = listPtr->Verify();
        PRINT_LOG_INDENT(8, "List[%p] condition - %s[%d]\n", ERROR_CODE_NAMES[listErr], listErr);
        PRINT_LOG_INDENT(8, "{\n");
        PRINT_LOG_INDENT(12, "data[%p]\n",       listPtr->data);
        PRINT_LOG_INDENT(12, "prev[%p]\n",       listPtr->prev);
        PRINT_LOG_INDENT(12, "next[%p]\n",       listPtr->next);
        PRINT_LOG_INDENT(12, "length = %zu\n",   listPtr->length);
        PRINT_LOG_INDENT(12, "capacity = %zu\n", listPtr->capacity);
        PRINT_LOG_INDENT(12, "freeHead = %zu\n", listPtr->freeHead);
        PRINT_LOG_INDENT(8, "}\n");
    }

    PRINT_LOG_INDENT(4, "}\n");
    PRINT_LOG_INDENT(0, "}\n");

    fclose(outTextFile);

    return EVERYTHING_FINE;
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
