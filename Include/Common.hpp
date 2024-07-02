#ifndef GUARD_COMMON_HPP_INCLUDED
#define GUARD_COMMON_HPP_INCLUDED

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cstring>

#include "BinContainer.hpp"

#define ERROR(passToCERR)                               \
    {                                                   \
        std::cerr << "[ERROR]: " << passToCERR << '\n'; \
        std::exit(1);                                   \
    }

#define INFO(passToCOUT)                               \
    {                                                  \
        std::cout << "[INFO]: " << passToCOUT << '\n'; \
    }

template <typename Key, typename Value>
using Dict = std::unordered_map<Key, Value>;

// Source/Encrypt.cpp.
std::string transitionEncryption(const std::string &prevState);
std::string parseFileContent(const std::string &filePath);

// Source/Compression.cpp.
BinContainer compressFileContent(const std::string &decodedText);

// Source/Decompression.cpp.
std::string decompressBinaryToText(BinContainer &encodedData);

// Source/TextAnalysis.cpp.
Dict<char, uint> getEncodingTable(const std::string &toAnalyze);

#endif // GUARD_COMMON_HPP_INCLUDED