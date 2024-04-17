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
    const char* logFolder      = "../log/LinkedList";
    const char* wordsPath      = "../Words.txt";

    const char* containersPath = "../Containers/ContainersUtils.csv";
    const char* resultPath     = "../Results/ResultsUtils.txt";

    size_t containersCount = 5113;

    PRINT_ERROR("MurMur\t\t", Test(wordsPath, logFolder, resultPath, containersPath, containersCount, CalculateHash));

    return 0;
}
