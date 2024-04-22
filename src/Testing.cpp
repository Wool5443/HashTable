#include "Testing.hpp"
#include "FileLoader.hpp"
#include "Hash.hpp"
#include "PrettyDumpList.hpp"

#ifdef NEMIT_DATA
#define ON_EMIT(...) (void)0
#else
#define ON_EMIT(...) __VA_ARGS__
#endif

#define PRINT_ERROR(hash, error)                                    \
do                                                                  \
{                                                                   \
    ErrorCode _error = error;                                       \
    printf("%s: %s[%d]\n", hash, ERROR_CODE_NAMES[error], error);   \
} while (0)

ErrorCode _printContainerSizes(HashTable* hashTable, const char* outTextPath);

ErrorCode Test(const char* wordsPath, const char* logFolder, const char* resultPath,
               const char* containersDataPath, size_t containersCount, hashFunction_t hashFunc)
{
    MyAssertSoft(wordsPath,  ERROR_NULLPTR);
    MyAssertSoft(logFolder,  ERROR_NULLPTR);
    MyAssertSoft(resultPath, ERROR_NULLPTR);

    FILE* resultFile = fopen(resultPath, "wb");
    if (!resultFile) return ERROR_BAD_FILE;

    HashTable table = {};

    RETURN_ERROR(table.Init(containersCount, hashFunc, logFolder));

    LoadedResult loadRes = LoadFileToTable(&table, wordsPath);
    RETURN_ERROR(loadRes.error);

    Loaded load = loadRes.value;

    for (size_t i = 0; i < load.split.wordsCount; i++)
    {
        HashTableElementResult wordRes = table.Get(load.split.words[i]);
        if (wordRes.error)
        {
            printf("Utils, i = %zu word = %s\n", i, load.split.words[i].buf);
            RETURN_ERROR(wordRes.error);
        }
        ON_EMIT(fprintf(resultFile, "%s: %zu\n", wordRes.value->key.buf, wordRes.value->count));
    }
    ON_EMIT(RETURN_ERROR(_printContainerSizes(&table, containersDataPath)));

    load.buffer.Destructor();
    load.split. Destructor();
    RETURN_ERROR(table.Destructor());

    return EVERYTHING_FINE;
}

ErrorCode _printContainerSizes(HashTable* hashTable, const char* outTextPath)
{
    MyAssertSoft(hashTable,   ERROR_NULLPTR);
    MyAssertSoft(outTextPath, ERROR_BAD_FILE);

    FILE* outTextFile = fopen(outTextPath, "wb");
    if (!outTextFile) return ERROR_BAD_FILE;

    size_t sumLength        = 0;
    size_t filledContainers = 0;

    for (size_t i = 0; i < hashTable->containersCount; i++)
    {
        size_t length = hashTable->containers[i].length;
        fprintf(outTextFile, "%zu\t%zu\n", i, length - 1);
        if (length > 1)
        {
            sumLength += length;
            filledContainers++;
        }
    }

    double loadFactor = (double)sumLength / (double)filledContainers;
    fprintf(outTextFile, "%lg\t%lg", loadFactor, loadFactor);

    return EVERYTHING_FINE;
}
