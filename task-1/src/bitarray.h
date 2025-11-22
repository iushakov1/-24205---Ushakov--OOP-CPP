#ifndef TASK_1_BITARRAY_H
#define TASK_1_BITARRAY_H

#include <cstdint>
#include <string>
#include <vector>

/**
 * @brief Dynamic array of bytes with bitwise operations.
 *
 * Stores bytes and provides operations like AND, OR, XOR, shifts.
 */

class BitArray
{
public:
    BitArray() = default;
    ~BitArray() = default;

    /**
     * @brief Create bit array with initial size and value
     * @param numBits Number of bytes
     * @param value Initial value for bytes
     */
    explicit BitArray(int numBits, unsigned int value = 0);

    /// Copy constructor
    BitArray(const BitArray& b);

    /// Swap contents with another bit array
    void swap(BitArray& b);

    /// Assignment operator
    BitArray& operator=(const BitArray& b);


    /**
     * @brief Change size of bit array
     * @param numBits New size
     * @param value Value for new bytes (if expanding)
     */
    void resize(int numBits, unsigned int value = 0);
    /// Remove all bytes
    void clear();
    /// Add bit to the end. Making memory redistribution if necessary.
    void push_back(bool bit);


    // Bitwise operations (modify current array).
    // Works only with array's that have same size
    BitArray& operator&=(const BitArray& b); ///< AND
    BitArray& operator|=(const BitArray& b); ///< OR
    BitArray& operator^=(const BitArray& b); ///< XOR

    ///Bit shifts (modify current array)
    BitArray& operator<<=(int n); ///< left shift
    BitArray& operator>>=(int n); ///< right shift

    // Bit shifts (create new array)
    BitArray operator<<(int n) const;  ///< left shift (new array)
    BitArray operator>>(int n) const;  ///< right shift (new array)

    // Set bytes to true/false
    BitArray& set(int n, bool val = true); ///< set one bit on n-index with val
    BitArray& set(); ///< set all bytes to true
    BitArray& reset(int n); ///< set one bit to false on n-index
    BitArray& reset(); ///< set all bytes to false

    // Check bytes
    bool any() const; ///< True if any bit is 1
    bool none() const; ///< True if all bytes are 0
    BitArray operator~() const; ///< Invert all bytes (NOT)
    int count() const; ///< Count 1 bytes


    // Access bytes
    bool operator[](int i) const; ///< Get bit at position i
    /**
     * @brief Proxy object for a singe bit
     *
     * Behaves like a reference to bool for packed storage
     */
    class Bit{
    public:
        /**
         * Create a proxy for the given bit
         */
        Bit(std::vector<uint8_t>&, int bitInx);
        /**
         * Set the bit to the given value
         */
        Bit& operator=(bool v) noexcept;
        /**
        * Copy the value from another bit proxy.
        */
        Bit& operator=(const Bit& other) noexcept;
        /**
        * Read the current bit value as bool.
        */
        operator bool() const noexcept;
    private:
        std::vector<uint8_t>& bytes;
        int bitInx;
    };
    /**
    * Non-const indexed access to a bit.
    * Returns a proxy that can read/write the bit.
    * May throw std::out_of_range if index is invalid.
    */
    Bit operator[](int i);

    // Size information
    int size() const;     ///< Get number of bytes
    int getBitCount() const;
    bool empty() const;   ///< Check if array is empty

    /// Convert to string of '1's and '0's
    std::string to_string() const;
private:
    std::vector<uint8_t> bytes;
    int bitCount = 0;
};

// Comparison operators
bool operator==(const BitArray & a, const BitArray & b);
bool operator!=(const BitArray & a, const BitArray & b);

// Bitwise operators (create new arrays)
BitArray operator&(const BitArray& b1, const BitArray& b2);  ///< AND
BitArray operator|(const BitArray& b1, const BitArray& b2);  ///< OR
BitArray operator^(const BitArray& b1, const BitArray& b2);  ///< XOR
#endif //TASK_1_BITARRAY_H
