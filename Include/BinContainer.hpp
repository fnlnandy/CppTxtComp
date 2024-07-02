#ifndef GUARD_BIN_CONTAINER_HPP
#define GUARD_BIN_CONTAINER_HPP

#include <cstdint>
#include <string>
#include <vector>

class BinContainer
{
private:
    std::vector<uint8_t> m_RawData;
    uint32_t m_LastIdx;
    bool m_IsHalfPushState;
    bool m_IsHalfPopState;

public:
    BinContainer();
    BinContainer(const std::initializer_list<uint8_t> &elems);
    BinContainer(const std::vector<uint8_t> &src);
    void push4Bits(uint8_t toPush);
    void push8Bits(uint8_t toPush);
    uint8_t pop4Bits();
    uint8_t pop8Bits();
    bool readFromFile(const std::string &filePath);

public:
    bool isEmpty() const;
    uint8_t peek4Bits() const;
    bool writeIntoFile(const std::string &filePath) const;
};

#endif // GUARD_BIN_CONTAINER_HPP