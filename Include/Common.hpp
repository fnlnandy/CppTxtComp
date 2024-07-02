#ifndef GUARD_COMMON_HPP_INCLUDED
#define GUARD_COMMON_HPP_INCLUDED

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cstring>

#include "BinContainer.hpp"

/**
 * @brief To display error messages.
 */
#define ERROR(passToCERR)                               \
    {                                                   \
        std::cerr << "[ERROR]: " << passToCERR << '\n'; \
        std::exit(1);                                   \
    }

/**
 * @brief To display information messages.
 */
#define INFO(passToCOUT)                               \
    {                                                  \
        std::cout << "[INFO]: " << passToCOUT << '\n'; \
    }

template <typename Key, typename Value>
using Dict = std::unordered_map<Key, Value>;

/**
 * @file Source/Encrypt.cpp
 *
 * @param prevState
 *
 * @brief Transitions the state
 * of encryption of a string to
 * another.
 *
 * @note This works both ways, i.e.
 * calling this function twice on the
 * same string will return the same string.
 *
 * @return The transitioned string.
 * @returns std::string
 */
std::string transitionEncryption(const std::string &prevState);
/**
 * @file Source/Encrypt.cpp
 *
 * @param filePath
 *
 * @brief Parses the content in a file
 *
 * @return The parsed file content.
 * @returns std::string
 */
std::string parseFileContent(const std::string &filePath);

/**
 * @file Source/Compression.cpp.
 *
 * @param decodedText
 *
 * @brief Compresses an std::string
 * into a BinContainer.
 *
 * @return The compressed data in a container.
 * @returns BinContainer
 */
BinContainer compressFileContent(const std::string &decodedText);

/**
 * @file Source/Decompression.cpp.
 *
 * @param encodedData
 *
 * @brief Decompresses a BinContainer
 * into an std::string.
 *
 * @return The decompressed text.
 * @returns std::string
 */
std::string decompressBinaryToText(BinContainer &encodedData);

/**
 * @file Source/TextAnalysis.cpp.
 *
 * @param toAnalyze
 *
 * @brief Gets the adequate encoding table
 * for a given text.
 *
 * @return The encoding table.
 * @returns Dict<char, uint>
 */
Dict<char, uint> getEncodingTable(const std::string &toAnalyze);

#endif // GUARD_COMMON_HPP_INCLUDED