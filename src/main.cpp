#include <stdio.h>
#include "HashTable.hpp"

int main()
{
    const char* logFolder = "/home/twenty/Programming/HashTable/log/LinkedList";
    const char* hashLog   = "/home/twenty/Programming/HashTable/log/hash.txt";

    HashTable table = {};
    table.Init(2, CalculateHash, logFolder);
    DumpHashTable(&table, table.Verify(), hashLog);

    table.Add("Hello");
    table.Add("world");
    table.Add("world");
    table.Add("freinds");
    table.Add("freinds");
    table.Add("freinds");

    HashTableElementResult helloRes   = table.Get("Hello");
    MyAssertSoft(!helloRes.error, helloRes.error);

    HashTableElementResult worldRes   = table.Get("world");
    MyAssertSoft(!worldRes.error, worldRes.error);

    HashTableElementResult friendsRes = table.Get("friends");
    MyAssertSoft(!friendsRes.error, friendsRes.error);

    printf("%s: %llu\n", helloRes.value.key, helloRes.value.count);

    return 0;
}
