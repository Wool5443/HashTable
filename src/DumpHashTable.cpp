#include "DumpHashTable.hpp"
#include "PrettyDumpList.hpp"

#define PRINT_LOG_INDENT(indentSize, ...)   \
do                                          \
{                                           \
    WriteSpaces(outTextFile, indentSize);   \
    fprintf(outTextFile, __VA_ARGS__);      \
} while (0)
ErrorCode _dumpHashTableText(HashTable* hashTable, ErrorCode error, const char* outTextPath,
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
        PRINT_LOG_INDENT(8, "List[%p] condition - %s[%d]\n", listPtr, ERROR_CODE_NAMES[listErr], listErr);
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

ErrorCode _dumpHashTable(HashTable* hashTable, ErrorCode error, const char* outTextPath, 
                         SourceCodePosition* caller)
{
    RETURN_ERROR(_dumpHashTableText(hashTable, error, outTextPath, caller));

    for (size_t i = 0; i < hashTable->containersCount; i++)
    {
        LinkedList* listPtr = &hashTable->containers[i];
        DumpList(listPtr, listPtr->Verify());
    }

    return EVERYTHING_FINE;
}