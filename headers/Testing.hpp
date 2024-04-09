#pragma once

#include "HashTable.hpp"
ErrorCode Test(const char* wordsPath, const char* logFolder, const char* resultPath,
               size_t containersCount, hashFunction_t hashFunc);
