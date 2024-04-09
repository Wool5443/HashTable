#include "FileLoader.hpp"

LoadedResult LoadFileToTable(HashTable* hashTable, const char* filePath)
{
    MyAssertSoftResult(hashTable, {}, ERROR_NULLPTR);
    MyAssertSoftResult(filePath,  {}, ERROR_NULLPTR);

    FILE* inputFile = fopen(filePath, "rb");
    if (!inputFile) return { {}, ERROR_BAD_FILE };

    size_t fileSize = GetFileSize(filePath);

    String string = {};
    ErrorCode error = string.Create(fileSize + 1);
    if (error)
    {
        fclose(inputFile);
        return { {}, error };
    }

    if (fread(string.buf, 1, fileSize, inputFile) != fileSize)
    {
        fclose(inputFile);
        string.Destructor();
        return { {}, ERROR_BAD_FILE };
    }
    fclose(inputFile);
    string.length = fileSize;

    SplitStringResult splitRes = string.Split("\n");
    if (splitRes.error)
    {
        string.Destructor();
        return { {}, splitRes.error };
    }

    SplitString split = splitRes.value;

    for (size_t i = 0; i < split.wordsCount; i++)
    {
        const String word   = split.words[i];
        error = hashTable->Add(word.buf, word.length);
        if (error)
        {
            split.Destructor();
            string.Destructor();
            return { {}, error };
        }
    }

    return { {string, split}, EVERYTHING_FINE };
}
