#include <stdio.h>
#include "HashTable.hpp"
#include "PrettyDumpList.hpp"
#include "DumpHashTable.hpp"
#include "FileLoader.hpp"
#include "Hash.hpp"
#include "Testing.hpp"

#define PRINT_ERROR(hash, error)                                    \
do                                                                  \
{                                                                   \
    ErrorCode _error = error;                                       \
    printf("%s: %s[%d]\n", hash, ERROR_CODE_NAMES[_error], _error); \
} while (0)

static const char* RESULT_FILES[] =
{
    "../Results/ResultsZero.txt",
    "../Results/ResultsFirstChar.txt",
    "../Results/ResultsLength.txt",
    "../Results/ResultsSumLength.txt",
    "../Results/ResultsSum.txt",
    "../Results/ResultsMurMur.txt",
    "../Results/ResultsCRC32.txt",
};
static const char* CONTAINER_DATA_FILES[] =
{
    "../Containers/ContainersZero.csv",
    "../Containers/ContainersFirstChar.csv",
    "../Containers/ContainersLength.csv",
    "../Containers/ContainersSumLength.csv",
    "../Containers/ContainersSum.csv",
    "../Containers/ContainersMurMur.csv",
    "../Containers/ContainersCRC32.csv",
};
static const char* TIMING_RESULT_FILES[] =
{
    "../Timings/TimingsZero.csv",
    "../Timings/TimingsFirstChar.csv",
    "../Timings/TimingsLength.csv",
    "../Timings/TimingsSumLength.csv",
    "../Timings/TimingsSum.csv",
    "../Timings/TimingsMurMur.csv",
    "../Timings/TimingsCRC32.csv",
};
static const char* HASH_NAMES[] =
{
    "Zero",
    "Length",
    "FirtChar",
    "SumLength",
    "Sum",
    "MurMur",
    "CRC32", 
};
static const hashFunction_t HASH_FUNCTIONS[] =
{
    ZeroHash,
    LengthHash,
    FirstCharHash,
    SumLengthHash,
    SumHash,
    CalculateHash,
    CRC32,
};

enum Contexts
{
    ZERO_HASH_NUMBER,
    LENGTH_HASH_NUMBER,
    FIRST_CHAR_HASH_NUMBER,
    SUM_LENGTH_HASH_NUMBER,
    SUM_HASH_NUMBER,
    MUR_MUR_HASH_NUMBER,
    CRC32_HASH_NUMBER,
};

static const char*  WORDS_PATH       = "../Words.txt";
static const char*  LOG_FOLDER       = "../log/LinkedList";
static const size_t CONTAINERS_COUNT = 5113;
static const size_t HASH_COUNT       = ArrayLength(HASH_FUNCTIONS);

int main()
{
    static const size_t HASH_FUNCTIONS_LENGTH       = HASH_COUNT;
    static const size_t HASH_NAMES_LENGTH           = ArrayLength(HASH_NAMES);
    static const size_t RESULT_FILES_LENGTH         = ArrayLength(RESULT_FILES);
    static const size_t CONTAINER_DATA_FILES_LENGTH = ArrayLength(CONTAINER_DATA_FILES);
    static const size_t TIME_RESULT_FILES_LENGTH    = ArrayLength(TIMING_RESULT_FILES);

    static_assert(HASH_FUNCTIONS_LENGTH == HASH_NAMES_LENGTH &&
                  RESULT_FILES_LENGTH   == CONTAINER_DATA_FILES_LENGTH &&
                  RESULT_FILES_LENGTH   == TIME_RESULT_FILES_LENGTH &&
                  HASH_FUNCTIONS_LENGTH == RESULT_FILES_LENGTH);

    static TestContext contexts[HASH_COUNT] = {};
    for (size_t i = 0; i < HASH_COUNT; i++)
    {
        contexts[i].wordsPath          = WORDS_PATH;
        contexts[i].resultPath         = RESULT_FILES[i];
        contexts[i].containersDataPath = CONTAINER_DATA_FILES[i];
        contexts[i].timingPath         = TIMING_RESULT_FILES[i];
        contexts[i].containersCount    = CONTAINERS_COUNT;
        contexts[i].hashName           = HASH_NAMES[i];
        contexts[i].hashFunction       = HASH_FUNCTIONS[i];
    }

    int startHash = ZERO_HASH_NUMBER;

    for (int i = startHash; i < HASH_COUNT; i++)
    {
        Test(&contexts[i]);
    }

    return 0;
}
