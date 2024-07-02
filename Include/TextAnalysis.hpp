#ifndef GUARD_TEXT_ANALYSIS_HPP_INCLUDED
#define GUARD_TEXT_ANALYSIS_HPP_INCLUDED

#include <string>
#include <unordered_map>

template <typename Key, typename Value>
using Dict = std::unordered_map<Key, Value>;

Dict<char, uint> getEncodingTable(const std::string &toAnalyze);

#endif // GUARD_TEXT_ANALYSIS_HPP_INCLUDED