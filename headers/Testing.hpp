#pragma once

#include "HashTable.hpp"

struct TestContext
{
    const char*    wordsPath;
    const char*    logFolder;
    const char*    resultPath;
    const char*    containersDataPath;
    const char*    timingPath;
    size_t         containersCount;
    const char*    hashName;
    hashFunction_t hashFunction;
};

// ErrorCode Test(const char* wordsPath, const char* logFolder, const char* resultPath,
            //    const char* conatinersDataPath, size_t containersCount, hashFunction_t hashFunc);

ErrorCode Test(TestContext* context);
