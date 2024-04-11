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

    const char* pythonResult = "../ResultsPython.txt";

    PRINT_ERROR("Zero", TestZeroHash(wordsPath, logFolder, resultFiles[0], 211));
    PRINT_ERROR("First Char", TestFirstChar(wordsPath, logFolder, resultFiles[1], 211));
    PRINT_ERROR("Length", TestLengthHash(wordsPath, logFolder, resultFiles[2], 211));
    PRINT_ERROR("Sum", TestSumHash(wordsPath, logFolder, resultFiles[3], 211));
    PRINT_ERROR("Sum / Length", TestSumLengthHash(wordsPath, logFolder, resultFiles[4], 211));
    PRINT_ERROR("Utils", Test(wordsPath, logFolder, resultFiles[5], 211, CalculateHash));

    char command[128] = "";
    for (size_t i = 0; i < hashCount; i++)
    {
        printf("%s:\n\n", resultFiles[i]);
        fflush(stdout);
        sprintf(command, "diff %s %s", pythonResult, resultFiles[i]);
        system(command);
    }

    return 0;
}
