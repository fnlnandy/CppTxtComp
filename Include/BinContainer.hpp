#ifndef GUARD_BIN_CONTAINER_HPP
#define GUARD_BIN_CONTAINER_HPP

#include <cstdint>
#include <string>
#include <vector>

/**
 * @brief Base container for
 * bytes. This merely acts as an
 * intermediary for actions on a
 * raw byte array.
 */
class BinContainer
{
private:
    //! @brief The actual array of bytes.
    std::vector<uint8_t> m_RawData;
    //! @brief The last index in the array.
    uint32_t m_LastIdx;
    //! @brief "Half" push state, for 4 bits.
    bool m_IsHalfPushState;
    //! @brief "Half" pop state, for 4 bits.
    bool m_IsHalfPopState;

public:
    /**
     * @brief Default constructor.
     */
    BinContainer();
    /**
     * @param elems
     *
     * @brief Constructor that takes in a
     * brace-enclosed initializer list.
     */
    BinContainer(const std::initializer_list<uint8_t> &elems);
    /**
     * @param src
     *
     * @brief Constructor that takes in a
     * vector.
     */
    BinContainer(const std::vector<uint8_t> &src);
    /**
     * @param toPush
     *
     * @brief Pushes 4 bits to the vector.
     */
    void push4Bits(uint8_t toPush);
    /**
     * @param toPush
     *
     * @brief Pushes 8 bits / a byte to
     * the vector.
     */
    void push8Bits(uint8_t toPush);
    /**
     * @brief Pops 4 bits from the vector.
     *
     * @warning This pops from the front,
     * unlike push which acts on the back.
     *
     * @return The popped 4 bits.
     * @returns uint8_t
     */
    uint8_t pop4Bits();
    /**
     * @brief Pops 8 bits / a byte from
     * the vector.
     *
     * @warning This pops from the front,
     * unlike push which acts on the back.
     *
     * @return The popped 8 bits.
     * @returns uint8_t
     */
    uint8_t pop8Bits();
    /**
     * @param filePath
     *
     * @brief Reads bytes from a file and
     * stores it inside this container.
     *
     * @warning This method wipes the previous
     * data inside m_RawData.
     *
     * @return Whether it successfully read from
     * the file or not.
     * @returns bool
     */
    bool readFromFile(const std::string &filePath);

public:
    /**
     * @brief Returns whether this container
     * is empty or not.
     *
     * @return If it's empty or not.
     * @returns bool
     */
    bool isEmpty() const;
    /**
     * @brief Peeks 4 bits from this container
     *
     * @todo Maybe actually make the peek not
     * use a copy of this object ? I don't know
     * if that would be faster.
     *
     * @return The peeked 4 bits.
     * @returns uint8_t
     */
    uint8_t peek4Bits() const;
    /**
     * @param filePath
     *
     * @brief Writes the content inside
     * this container into a file.
     *
     * @return Whether it successfully wrote or not.
     * @returns bool
     */
    bool writeIntoFile(const std::string &filePath) const;
};

#endif // GUARD_BIN_CONTAINER_HPP