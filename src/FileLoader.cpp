#include <string.h>
#include "FileLoader.hpp"

LoadResult LoadFileToTable(HashTable* hashTable, const char* filePath)
{
    MyAssertSoftResult(hashTable, nullptr, ERROR_NULLPTR);
    MyAssertSoftResult(filePath,  nullptr, ERROR_NULLPTR);

    FILE* file = fopen(filePath, "rb");
    if (!file) return { nullptr, ERROR_BAD_FILE };

    size_t fileSize = GetFileSize(filePath);

    char* buffer = (char*)calloc(fileSize + 1, 1);
    if (!buffer) return { nullptr, ERROR_NO_MEMORY };

    fread(buffer, 1, fileSize, file);
    fclose(file);

    char* currentToken = strtok(buffer, "\n");

    while (currentToken)
    {
        size_t length = 0;
        size_t read   = 0;
        if (sscanf(currentToken, "%zu%n", &length, &read) != 1) return { nullptr, ERROR_BAD_FILE };
        length++;

        ErrorCode error = hashTable->Add(currentToken + read, length);
        if (error)
        {
            free(buffer);
            return { nullptr, error };
        }

        currentToken = strtok(nullptr, "\n");
    }

    return { buffer, EVERYTHING_FINE };
}
