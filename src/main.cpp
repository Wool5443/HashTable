#include <stdio.h>
#include "HashTable.hpp"
#include "PrettyDumpList.hpp"
#include "DumpHashTable.hpp"
#include "FileLoader.hpp"
#include "Hash.hpp"

int main()
{
    const char* logFolder = "/home/twenty/Programming/HashTable/log/LinkedList";
    const char* hashLog   = "/home/twenty/Programming/HashTable/log/hash.txt";

    const char* wordsPath = "/home/twenty/Programming/HashTable/Words.txt";

    RETURN_ERROR(StartHtmlLogging(logFolder));

    HashTable table = {};

    RETURN_ERROR(table.Init(101, CalculateHash, logFolder));

    LoadedResult loadRes = LoadFileToTable(&table, wordsPath);
    RETURN_ERROR(loadRes.error);

    // DumpHashTable(&table, table.Verify(), hashLog);
    EndHtmlLogging();

    Loaded load = loadRes.value;

    for (size_t i = 0; i < load.split.wordsCount; i++)
    {
        HashTableElementResult wordRes = table.Get(load.split.words[i].buf, load.split.words[i].length);
        printf("%s: %zu\n", wordRes.value->key, wordRes.value->count);
    }

    load.buffer.Destructor();
    load.split.Destructor();
    RETURN_ERROR(table.Destructor());

    return 0;
}
