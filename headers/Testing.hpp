#pragma once

#include "HashTable.hpp"
ErrorCode Test(const char* wordsPath, const char* logFolder, const char* resultPath,
               const char* conatinersDataPath, size_t containersCount, hashFunction_t hashFunc);

ErrorCode TestZeroHash(const char* wordsPath, const char* logFolder, const char* resultPath,
                       const char* containersDataPath, size_t containersCount);

ErrorCode TestFirstChar(const char* wordsPath, const char* logFolder, const char* resultPath,
                        const char* containersDataPath, size_t containersCount);

ErrorCode TestLengthHash(const char* wordsPath, const char* logFolder, const char* resultPath,
                         const char* containersDataPath, size_t containersCount);

ErrorCode TestSumLengthHash(const char* wordsPath, const char* logFolder, const char* resultPath,
                            const char* containersDataPath, size_t containersCount);

ErrorCode TestSumHash(const char* wordsPath, const char* logFolder, const char* resultPath,
                      const char* containersDataPath, size_t containersCount);
