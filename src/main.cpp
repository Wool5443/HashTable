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
        "../Containers/ContainersZero.txt",
        "../Containers/ContainersFirstChar.txt",
        "../Containers/ContainersLength.txt",
        "../Containers/ContainersSum.txt",
        "../Containers/ContainersSumLength.txt",
        "../Containers/ContainersUtils.txt",
    };

    const char* pythonResult = "../ResultsPython.txt";

    PRINT_ERROR("Zero\t\t",         TestZeroHash     (wordsPath, logFolder, resultFiles[0], containerDataFiles[0], 211));
    PRINT_ERROR("First Char\t\t",   TestFirstChar    (wordsPath, logFolder, resultFiles[1], containerDataFiles[1], 211));
    PRINT_ERROR("Length\t\t",       TestLengthHash   (wordsPath, logFolder, resultFiles[2], containerDataFiles[2], 211));
    PRINT_ERROR("Sum\t\t",          TestSumHash      (wordsPath, logFolder, resultFiles[3], containerDataFiles[3], 211));
    PRINT_ERROR("Sum / Length\t\t", TestSumLengthHash(wordsPath, logFolder, resultFiles[4], containerDataFiles[4], 211));
    PRINT_ERROR("Utils\t\t",        Test             (wordsPath, logFolder, resultFiles[5], containerDataFiles[5], 211, CalculateHash));

    return 0;
}
