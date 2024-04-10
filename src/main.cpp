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
    printf("%s: %s[%d]\n", hash, ERROR_CODE_NAMES[error], error);   \
} while (0)

int main()
{
    const char* logFolder = "../log/LinkedList";
    const char* wordsPath = "../Words.txt";

    // PRINT_ERROR("Zero", TestZeroHash(wordsPath, logFolder, "../ResultsZero.txt", 211));
    // PRINT_ERROR("First Char", TestFirstChar(wordsPath, logFolder, "../ResultsFirstChar.txt", 211));
    // PRINT_ERROR("Length", TestLengthHash(wordsPath, logFolder, "../ResultsLength.txt", 211));
    // PRINT_ERROR("Sum", TestSumHash(wordsPath, logFolder, "../ResultsSum.txt", 211));
    // PRINT_ERROR("Sum / Length", TestSumLengthHash(wordsPath, logFolder, "../ResultsSumLength.txt", 211));
    PRINT_ERROR("Utils", Test(wordsPath, logFolder, "../ResultsUtils.txt", 211, CalculateHash));

    return 0;
}
