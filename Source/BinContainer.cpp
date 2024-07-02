#include <fstream>
#include <new>

#include "Common.hpp"

BinContainer::BinContainer()
{
    m_RawData = {};
    m_LastIdx = 0;
    m_IsHalfPushState = false;
    m_IsHalfPopState = false;
}

BinContainer::BinContainer(const std::initializer_list<uint8_t> &elems) : BinContainer()
{
    m_RawData = elems;
}

BinContainer::BinContainer(const std::vector<uint8_t> &src) : BinContainer()
{
    m_RawData = src;
}

void BinContainer::push4Bits(uint8_t toPush)
{
    uint8_t clean = toPush & 0xF;
    uint8_t toWrite = {};

    if (!m_IsHalfPushState)
    {
        toWrite = clean << 4;
        m_RawData.push_back(toWrite);
        m_LastIdx = m_RawData.size() - 1;
    }
    else
    {
        toWrite = m_RawData[m_LastIdx] | clean;
        m_RawData[m_LastIdx] = toWrite;
    }

    m_IsHalfPushState = !m_IsHalfPushState;
}

void BinContainer::push8Bits(uint8_t toPush)
{
    uint8_t clean = toPush;

    push4Bits(clean >> 0x4);
    push4Bits(clean);
}

uint8_t BinContainer::pop4Bits()
{
    uint8_t readBits = {};

    if (isEmpty())
        return readBits;

    if (!m_IsHalfPopState)
    {
        readBits = m_RawData[0] >> 0x4;
    }
    else
    {
        std::vector<uint8_t>::const_iterator firstElem = m_RawData.begin();

        readBits = *firstElem & 0xF;
        m_RawData.erase(firstElem);
    }

    m_IsHalfPopState = !m_IsHalfPopState;
    return readBits;
}

uint8_t BinContainer::pop8Bits()
{
    uint8_t readByte = (pop4Bits() << 0x4) | (pop4Bits());

    return readByte;
}

bool BinContainer::readFromFile(const std::string &filePath)
{
    std::ifstream srcFile = std::ifstream(filePath, std::ios::binary);

    if (!srcFile.is_open())
        return false;

    uint32_t fileSize = {};

    // Getting the file size to reserve for the vector
    // so that we don't suffer from constant resizing
    // with push_back.
    srcFile.seekg(0, std::ios::end);
    fileSize = srcFile.tellg();
    srcFile.seekg(0, std::ios::beg);

    // Clear the eof bit.
    srcFile.clear();

    // Clear any previous data and reserve the new
    // size.
    m_RawData.clear();
    m_RawData.reserve(fileSize);

    char *buf = nullptr;

    try
    {
        buf = new char[fileSize];
    }
    catch (const std::bad_alloc &e)
    {
        ERROR("Unable to allocate memory of size: " << fileSize << ". Aborting.");
    }

    srcFile.read(buf, fileSize);

    for (uint i = 0; i < fileSize; ++i)
        m_RawData.push_back(buf[i]);

    delete[] buf;

    return true;
}

bool BinContainer::isEmpty() const
{
    return m_RawData.size() == 0;
}

uint8_t BinContainer::peek4Bits() const
{
    BinContainer copy = *this;

    return copy.pop4Bits();
}

bool BinContainer::writeIntoFile(const std::string &filePath) const
{
    std::ofstream destFile = std::ofstream(filePath);

    if (!destFile.is_open())
        return false;

    destFile.write(reinterpret_cast<const char *>(m_RawData.data()), m_RawData.size());
    destFile.flush();

    return true;
}