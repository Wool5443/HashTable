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
        "../ResultsZero.txt",
        "../ResultsFirstChar.txt",
        "../ResultsLength.txt",
        "../ResultsSum.txt",
        "../ResultsSumLength.txt",
        "../ResultsUtils.txt",
    };

    const char* containerDataFiles[] = 
    {
        "../ContainersZero.txt",
        "../ContainersFirstChar.txt",
        "../ContainersLength.txt",
        "../ContainersSum.txt",
        "../ContainersSumLength.txt",
        "../ContainersUtils.txt",
    };

    const char* pythonResult = "../ResultsPython.txt";

    PRINT_ERROR("Zero\t\t",         TestZeroHash     (wordsPath, logFolder, resultFiles[0], containerDataFiles[0], 211));
    PRINT_ERROR("First Char\t\t",   TestFirstChar    (wordsPath, logFolder, resultFiles[1], containerDataFiles[1], 211));
    PRINT_ERROR("Length\t\t",       TestLengthHash   (wordsPath, logFolder, resultFiles[2], containerDataFiles[2], 211));
    PRINT_ERROR("Sum\t\t",          TestSumHash      (wordsPath, logFolder, resultFiles[3], containerDataFiles[3], 211));
    PRINT_ERROR("Sum / Length\t\t", TestSumLengthHash(wordsPath, logFolder, resultFiles[4], containerDataFiles[4], 211));
    PRINT_ERROR("Utils\t\t",        Test             (wordsPath, logFolder, resultFiles[5], containerDataFiles[5], 211, CalculateHash));

    // char command[128] = "";
    // for (size_t i = 0; i < hashCount; i++)
    // {
    //     printf ("%s:\n\n", resultFiles[i]);
    //     fflush (stdout);
    //     sprintf(command, "diff %s %s", pythonResult, resultFiles[i]);
    //     system (command);
    // }

    return 0;
}
