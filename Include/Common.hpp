#ifndef GUARD_COMMON_HPP_INCLUDED
#define GUARD_COMMON_HPP_INCLUDED

#include <iostream>
#include <string>

#include "BinContainer.hpp"

std::string parseFileContent(const std::string &filePath);
BinContainer compressFileContent(const std::string &decodedText);
std::string decompressBinaryToText(BinContainer &encodedData);

#endif // GUARD_COMMON_HPP_INCLUDED