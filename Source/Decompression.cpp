#include "Common.hpp"

/**
 * @param encodedData
 *
 * @brief Tries to deduce an encoding
 * table from the given binary data.
 *
 * @warning This changes encodedData.
 *
 * @return The deduced encoding table.
 * @returns Dict<char, uint>
 */
static Dict<char, uint> deduceEncodingTableFromContent(BinContainer &encodedData)
{
    Dict<char, uint> encodingTable = {};

    // We start with 1, since globally 0 is
    // used as borth a separator and a header terminator,
    // we also don't include 16 since we can only encode
    // 15 characters (16 - 1).
    for (uint i = 1; i < 16; ++i)
    {
        uint8_t buffer = encodedData.pop8Bits();

        if (buffer == 0)
            break;

        encodingTable[static_cast<char>(buffer)] = i;
    }

    return encodingTable;
}

std::string decompressBinaryToText(BinContainer &encodedData)
{
    std::string decodedText = {};
    Dict<char, uint> encodingTable = deduceEncodingTableFromContent(encodedData);
    bool isEncodedMode = false;
    uint8_t prevChar = 1; // Not 0, since that would be a separator.

    while (!encodedData.isEmpty())
    {
        if (!isEncodedMode)
        {
            uint8_t buffer = encodedData.pop8Bits();

            // Separator encountered, switching the mode.
            if (buffer == 0)
            {
                isEncodedMode = true;
                continue;
            }

            decodedText += static_cast<char>(buffer);
        }
        else
        {
            uint8_t currChar = encodedData.pop4Bits();
            uint8_t nextChar = encodedData.peek4Bits();

            // Separator encountered, switching the mode.
            if (currChar == 0 && prevChar == 0)
            {
                isEncodedMode = false;
                prevChar = -1;
                continue;
            }
            // Also separator encountered.
            else if (currChar == 0 && nextChar == 0)
            {
                // Peek did NOT take the 4 bits, so we have to.
                nextChar = encodedData.pop4Bits();
                isEncodedMode = false;
                prevChar = -1;
                continue;
            }

            for (auto it = encodingTable.begin(); it != encodingTable.end(); ++it)
            {
                if (it->second != currChar)
                    continue;

                decodedText += it->first;
                break;
            }

            prevChar = currChar;
        }
    }

    return decodedText;
}