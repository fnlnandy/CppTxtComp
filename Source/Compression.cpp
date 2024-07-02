#include <iostream>

#include "BinContainer.hpp"
#include "TextAnalysis.hpp"

static void writeEncodingTableHeader(const Dict<char, uint> &srcEncodingTable, BinContainer &dest)
{
    for (auto it = srcEncodingTable.begin(); it != srcEncodingTable.end(); ++it)
        dest.push8Bits(static_cast<uint8_t>(it->first)); // We write the key, not the value.

    if (srcEncodingTable.size() < 15)
        dest.push8Bits(0);
}

BinContainer compressFileContent(const std::string &decodedText)
{
    Dict<char, uint> encodingTable = getEncodingTable(decodedText);
    BinContainer compressed = {};
    bool isEncodedMode = false;

    writeEncodingTableHeader(encodingTable, compressed);

    for (const char c : decodedText)
    {
        bool isInEncodingTable = false;

        for (auto it = encodingTable.begin(); it != encodingTable.end(); ++it)
        {
            if (c == it->first)
            {
                if (!isEncodedMode)
                {
                    compressed.push8Bits(0);
                    isEncodedMode = true;
                }

                compressed.push4Bits(it->second);
                isInEncodingTable = true;
                break;
            }
        }

        if (isInEncodingTable)
            continue;

        if (isEncodedMode)
        {
            compressed.push8Bits(0);
            isEncodedMode = false;
        }

        compressed.push8Bits(c);
    }

    return compressed;
}