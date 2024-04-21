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
    CRC32const char* logFolder      = "../log/LinkedList";
    const char* wordsPath      = "../Words.txt";

    const char* containersPath = "../Containers/ContainersCRC32.csv";
    const char* resultPath     = "../Results/ResultsCRC32.txt";

    size_t containersCount = 5113;

    PRINT_ERROR("CRC32\t\t", Test(wordsPath, logFolder, resultPath, containersPath, containersCount, CRC32));

    return 0;
}
