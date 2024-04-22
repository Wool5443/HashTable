#include <stdio.h>
#include <intrin.h>
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

int main()
{
    int hashCount = 7;
    const char* resultFiles[] =
    {
        "../Results/ResultsZero.txt",
        "../Results/ResultsFirstChar.txt",
        "../Results/ResultsLength.txt",
        "../Results/ResultsSumLength.txt",
        "../Results/ResultsSum.txt",
        "../Results/ResultsMurMur.txt",
        "../Results/ResultsCRC32.txt",
    };
    const char* containerDataFiles[] =
    {
        "../Containers/ContainersZero.csv",
        "../Containers/ContainersFirstChar.csv",
        "../Containers/ContainersLength.csv",
        "../Containers/ContainersSumLength.csv",
        "../Containers/ContainersSum.csv",
        "../Containers/ContainersMurMur.csv",
        "../Containers/ContainersCRC32.csv",
    };
    const char* hashNames[] =
    {
        "Zero",
        "Length",
        "FirtChar",
        "SumLength",
        "Sum",
        "MurMur",
        "CRC32", 
    };
    const hashFunction_t hashFunctions[] =
    {
        ZeroHash,
        LengthHash,
        FirstCharHash,
        SumLengthHash,
        SumHash,
        CalculateHash,
        CRC32,
    };
    const char* wordsPath  = "../Words.txt";
    const char* logFolder  = "../log/LinkedList";
    size_t containersCount = 5113;

    #ifdef TEST_ALL
    for (int i = 0; i < hashCount; i++)
    {
        PRINT_ERROR(hashNames[i], Test(wordsPath, logFolder, resultFiles[i],
                                       containerDataFiles[i], containersCount, hashFunctions[i]));
    }
    #else

    uint64_t startTicks = __rdtsc();

    PRINT_ERROR("CRC32", Test(wordsPath, logFolder, resultFiles[6], containerDataFiles[6], containersCount,
                              CRC32));
    #endif

    return 0;
}
