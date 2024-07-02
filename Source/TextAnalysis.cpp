#include "Common.hpp"

static Dict<char, uint> getCharacterUseStats(const std::string &toAnalyze)
{
    Dict<char, uint> statsDict;

    for (const char c : toAnalyze)
        statsDict[c] += 1;

    return statsDict;
}

static Dict<char, uint> getMostUsedChars(const std::string &toAnalyze, const uint maxIter)
{
    using iter = Dict<char, uint>::iterator;

    Dict<char, uint> statsDict = getCharacterUseStats(toAnalyze);
    Dict<char, uint> mostUsedDict = {};

    for (uint i = 0; i < maxIter; i++)
    {
        iter max = statsDict.begin();

        for (iter it = statsDict.begin(); it != statsDict.end(); ++it)
            if (it->second > max->second)
                max = it;

        // In case there aren't enough characters,
        // this could be a segfault.
        if (max == statsDict.end())
            break;

        mostUsedDict[max->first] = max->second;
        statsDict.erase(max);
    }

    return mostUsedDict;
}

Dict<char, uint> getEncodingTable(const std::string &toAnalyze)
{
    Dict<char, uint> mostUsedDict = getMostUsedChars(toAnalyze, 15);
    uint firstChar = 0x1;

    for (auto it = mostUsedDict.begin(); it != mostUsedDict.end(); ++it)
        mostUsedDict[it->first] = firstChar++;

    return mostUsedDict;
}