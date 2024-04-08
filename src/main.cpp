#include <stdio.h>
#include "HashTable.hpp"
#include "PrettyDumpList.hpp"
#include "DumpHashTable.hpp"
#include "FileLoader.hpp"

int main()
{
    const char* logFolder = "/home/twenty/Programming/HashTable/log/LinkedList";
    const char* hashLog   = "/home/twenty/Programming/HashTable/log/hash.txt";

    const char* wordsPath = "/home/twenty/Programming/HashTable/Words.txt";

    RETURN_ERROR(StartHtmlLogging(logFolder));

    HashTable table = {};

    RETURN_ERROR(table.Init(101, CalculateHash, logFolder));

    LoadResult loadRes = LoadFileToTable(&table, wordsPath);
    RETURN_ERROR(loadRes.error);

    // DumpHashTable(&table, table.Verify(), hashLog);

    const char* word = "Man";

    HashTableElementResult wordRes = table.Get(word, 4);
    printf("%s: %zu\n", wordRes.value->key, wordRes.value->count);

    EndHtmlLogging();

    free(loadRes.buffer);
    RETURN_ERROR(table.Destructor());

    return 0;
}
