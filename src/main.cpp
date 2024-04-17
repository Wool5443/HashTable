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
    const char* logFolder = "../log/LinkedList";
    const char* wordsPath = "../Words.txt";

    size_t      hashCount     = 6;
    const char* resultFiles[] = 
    {
        "../Results/ResultsZero.txt",
        "../Results/ResultsFirstChar.txt",
        "../Results/ResultsLength.txt",
        "../Results/ResultsSum.txt",
        "../Results/ResultsSumLength.txt",
        "../Results/ResultsUtils.txt",
    };

    const char* containerDataFiles[] = 
    {
        "../Containers/ContainersZero.csv",
        "../Containers/ContainersFirstChar.csv",
        "../Containers/ContainersLength.csv",
        "../Containers/ContainersSum.csv",
        "../Containers/ContainersSumLength.csv",
        "../Containers/ContainersUtils.csv",
    };

    size_t containersCount = 5113;

    PRINT_ERROR("Zero\t\t",         TestZeroHash     (wordsPath, logFolder, resultFiles[0], containerDataFiles[0], containersCount));
    PRINT_ERROR("First Char\t\t",   TestFirstChar    (wordsPath, logFolder, resultFiles[1], containerDataFiles[1], containersCount));
    PRINT_ERROR("Length\t\t",       TestLengthHash   (wordsPath, logFolder, resultFiles[2], containerDataFiles[2], containersCount));
    PRINT_ERROR("Sum\t\t",          TestSumHash      (wordsPath, logFolder, resultFiles[3], containerDataFiles[3], containersCount));
    PRINT_ERROR("Sum / Length\t\t", TestSumLengthHash(wordsPath, logFolder, resultFiles[4], containerDataFiles[4], containersCount));
    PRINT_ERROR("MurMur\t\t",       TestMurMur       (wordsPath, logFolder, resultFiles[4], containerDataFiles[4], containersCount));

    return 0;
}
