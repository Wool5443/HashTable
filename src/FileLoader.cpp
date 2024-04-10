#include "FileLoader.hpp"

static const size_t ALLIGNMENT = 8;

LoadedResult LoadFileToTable(HashTable* hashTable, const char* filePath)
{
    MyAssertSoftResult(hashTable, {}, ERROR_NULLPTR);
    MyAssertSoftResult(filePath,  {}, ERROR_NULLPTR);

    FILE* inputFile = fopen(filePath, "rb");
    if (!inputFile) return { {}, ERROR_BAD_FILE };

    size_t fileSize = GetFileSize(filePath);

    String unallignedString = {};
    ErrorCode error = unallignedString.Create(fileSize + 1);
    if (error)
    {
        fclose(inputFile);
        return { {}, error };
    }

    if (fread(unallignedString.buf, 1, fileSize, inputFile) != fileSize)
    {
        fclose(inputFile);
        unallignedString.Destructor();
        return { {}, ERROR_BAD_FILE };
    }
    fclose(inputFile);
    unallignedString.length = fileSize;

    SplitStringResult splitRes = unallignedString.Split("\n");
    if (splitRes.error)
    {
        unallignedString.Destructor();
        return { {}, splitRes.error };
    }
    SplitString split = splitRes.value;

    String allignedString = {};
    allignedString.Create(fileSize);

    for (size_t i = 0; i < split.wordsCount; i++)
    {
        String* word = &split.words[i];

        allignedString.Append(word);

        size_t zeroesCount = ALLIGNMENT - word->length % ALLIGNMENT;
        allignedString.length += zeroesCount;
    }

    unallignedString.Destructor();

    char* currentWord = allignedString.buf;

    for (size_t i = 0; i < split.wordsCount; i++)
    {
        error = hashTable->Add({ currentWord, split.words[i].length });
        if (error)
        {
            allignedString.Destructor();
            split.Destructor();
            return { {}, error };
        }

        while (!(*currentWord)) currentWord++;
        split.words[i].buf = currentWord;

        size_t length = split.words[i].length;
        currentWord += ALLIGNMENT * (length / ALLIGNMENT + ((length % ALLIGNMENT) ? 1 : 0));
    }

    return { {allignedString, split}, EVERYTHING_FINE };
}
