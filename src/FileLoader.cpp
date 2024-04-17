#include <string.h>
#include "FileLoader.hpp"

static const size_t ALLIGNMENT = 64;

LoadedResult LoadFileToTable(HashTable* hashTable, const char* filePath)
{
    MyAssertSoftResult(hashTable, {}, ERROR_NULLPTR);
    MyAssertSoftResult(filePath,  {}, ERROR_NULLPTR);

    FILE* inputFile = fopen(filePath, "rb");
    if (!inputFile) return { {}, ERROR_BAD_FILE };

    size_t fileSize = GetFileSize(filePath);

    String unalignedString = {};
    ErrorCode error = unalignedString.Create(fileSize + 1);
    if (error)
    {
        fclose(inputFile);
        return { {}, error };
    }

    if (fread(unalignedString.buf, 1, fileSize, inputFile) != fileSize)
    {
        fclose(inputFile);
        unalignedString.Destructor();
        return { {}, ERROR_BAD_FILE };
    }
    fclose(inputFile);
    unalignedString.length = fileSize;

    SplitStringResult splitRes = unalignedString.Split("\n");
    if (splitRes.error)
    {
        unalignedString.Destructor();
        return { {}, splitRes.error };
    }
    SplitString split = splitRes.value;

    String alignedString = {};
    alignedString.capacity  = fileSize + ALLIGNMENT - (fileSize % ALLIGNMENT);
    alignedString.buf       = (char*)aligned_alloc(ALLIGNMENT, alignedString.capacity);
    alignedString.allocated = true;

    for (size_t i = 0; i < split.wordsCount; i++)
    {
        String* word = &split.words[i];

        alignedString.Append(word);

        size_t zeroesCount = ALLIGNMENT - word->length % ALLIGNMENT;
        alignedString.length += zeroesCount;
    }

    unalignedString.Destructor();

    char* currentWord = alignedString.buf;
    size_t k = 0;
    for (size_t i = 0; i < split.wordsCount; i++)
    {
        error = hashTable->Add({ currentWord, split.words[i].length });

        if (error)
        {
            alignedString.Destructor();
            split.Destructor();
            return { {}, error };
        }

        while (!(*currentWord)) currentWord++;
        split.words[i].buf = currentWord;

        size_t length = split.words[i].length;
        currentWord += length + (ALLIGNMENT - length % ALLIGNMENT);
    }

    return { {alignedString, split}, EVERYTHING_FINE };
}
