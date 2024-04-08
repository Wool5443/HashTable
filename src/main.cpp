#include <stdio.h>
#include "HashTable.hpp"
#include "PrettyDumpList.hpp"
#include "DumpHashTable.hpp"

int main()
{
    const char* logFolder = "/home/twenty/Programming/HashTable/log/LinkedList";
    const char* hashLog   = "/home/twenty/Programming/HashTable/log/hash.txt";

    RETURN_ERROR(StartHtmlLogging(logFolder));

    HashTable table = {};
    table.Init(2, CalculateHash, logFolder);
    DumpHashTableText(&table, table.Verify(), hashLog);

    table.Add("Hello", 5);
    table.Add("world", 5);
    table.Add("world", 5);
    table.Add("friends", 7);
    table.Add("friends", 7);
    table.Add("friends", 7);

    DumpHashTable(&table, table.Verify(), hashLog);

    HashTableElementResult helloRes   = table.Get("Hello", 5);
    MyAssertSoft(!helloRes.error, helloRes.error);

    HashTableElementResult worldRes   = table.Get("world", 5);
    MyAssertSoft(!worldRes.error, worldRes.error);

    HashTableElementResult friendsRes = table.Get("friends", 7);
    MyAssertSoft(!friendsRes.error, friendsRes.error);

    printf("%s: %llu\n", helloRes.value->key, helloRes.value->count);
    printf("%s: %llu\n", worldRes.value->key, worldRes.value->count);
    printf("%s: %llu\n", friendsRes.value->key, friendsRes.value->count);

    EndHtmlLogging();
    return 0;
}
