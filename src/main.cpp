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

int main()
{
    int hashCount = 7;

    const char* resultDataFiles[] =
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
    
    const char* logFolder      = "../log/LinkedList";
    const char* wordsPath      = "../Words.txt";

    size_t containersCount = 5113;

    for (int i = 0; i < hashCount; i++)
    {
        PRINT_ERROR(hashNames[i], Test(wordsPath, logFolder, resultDataFiles[i],
                                       containerDataFiles[i], containersCount, hashFunctions[i]));
    }

    return 0;
}
