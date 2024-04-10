#include "Testing.hpp"
#include "FileLoader.hpp"
#include "Hash.hpp"

ErrorCode Test(const char* wordsPath, const char* logFolder, const char* resultPath,
               size_t containersCount, hashFunction_t hashFunc)
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
        HashTableElementResult wordRes = table.Get(load.split.words[i].buf, load.split.words[i].length);
        RETURN_ERROR(wordRes.error);
        fprintf(resultFile, "%s: %zu\n", wordRes.value->key, wordRes.value->count);
    }

    load.buffer.Destructor();
    load.split. Destructor();
    RETURN_ERROR(table.Destructor());

    return EVERYTHING_FINE;
}

ErrorCode TestZeroHash(const char* wordsPath, const char* logFolder, const char* resultPath,
                       size_t containersCount)
{
    return Test(wordsPath, logFolder, resultPath, containersCount, ZeroHash);
}

ErrorCode TestFirstChar(const char* wordsPath, const char* logFolder, const char* resultPath,
                        size_t containersCount)
{
    return Test(wordsPath, logFolder, resultPath, containersCount, FirstCharHash);
}

ErrorCode TestLengthHash(const char* wordsPath, const char* logFolder, const char* resultPath,
                         size_t containersCount)
{
    return Test(wordsPath, logFolder, resultPath, containersCount, LengthHash);
}

ErrorCode TestSumLengthHash(const char* wordsPath, const char* logFolder, const char* resultPath,
                            size_t containersCount)
{
    return Test(wordsPath, logFolder, resultPath, containersCount, SumLengthHash);
}

ErrorCode TestSumHash(const char* wordsPath, const char* logFolder, const char* resultPath,
                      size_t containersCount)
{
    return Test(wordsPath, logFolder, resultPath, containersCount, SumHash);
}
