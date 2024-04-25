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

#ifdef FINAL_TESTING
#define ON_FINAL_TEST(...) __VA_ARGS__
#else
#define ON_FINAL_TEST(...) (void)0
#endif

ErrorCode _printContainerSizes(HashTable* hashTable, const char* outTextPath);

ErrorCode Test(TestContext* context)
{
    MyAssertSoft(context, ERROR_NULLPTR);

    ON_EMIT(
            FILE* resultFile = fopen(context->resultPath, "wb");
            if (!resultFile) return ERROR_BAD_FILE;
           );

    ON_FINAL_TEST(
    FILE* timingFile = fopen(context->timingPath, "ab");
    if (!timingFile) return ERROR_BAD_FILE;
    fprintf(timingFile, "\"Load\"\t\"Hash operations\"\t\"All\"\n");
    for (int i = 0; i < FINAL_TESTING; i++) {
    );

    HashTable table = {};
    RETURN_ERROR(table.Init(context->containersCount, context->hashFunction, context->logFolder));

    Timer timer = {};

    timer.Start();
    LoadedResult loadRes  = LoadFileToTable(&table, context->wordsPath);
    uint64_t loadDuration = timer.Stop();
    RETURN_ERROR(loadRes.error);

    Loaded load = loadRes.value;

    timer.Start();
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
    uint64_t hashOperationDuration = timer.Stop();

    ON_EMIT(puts("EMMITED!!!"));
    ON_EMIT(fclose(resultFile));
    ON_EMIT(RETURN_ERROR(_printContainerSizes(&table, context->containersDataPath)));

    #ifdef FINAL_TESTING
    fprintf(timingFile, "%lu\t%lu\t%lu\n", loadDuration, hashOperationDuration, loadDuration + hashOperationDuration);
    fflush(timingFile);
    #else
    FILE* timingFile = fopen(context->timingPath, "wb");
    if (!timingFile) return ERROR_BAD_FILE;
    fprintf(timingFile, "\"%s - load\"\t%llu\n", context->hashName, loadDuration);
    fprintf(timingFile, "\"%s - operations\"\t%llu\n", context->hashName, hashOperationDuration);
    fprintf(timingFile, "\"%s\"\t%llu\n", context->hashName, loadDuration + hashOperationDuration);
    fclose(timingFile);
    #endif

    load.buffer.Destructor();
    load.split. Destructor();
    RETURN_ERROR(table.Destructor());

    ON_FINAL_TEST(});

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
