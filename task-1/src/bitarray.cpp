#include "bitarray.h"

#include <stdexcept>

BitArray::BitArray(int num_bits, unsigned long value) {
    if (num_bits < 0) {
        throw std::invalid_argument("Number of bits cannot be negative");
    }
    bits.resize(num_bits, false);
    int bitsToInit = std::min(num_bits, static_cast<int>(sizeof(value) * 8));
    for (int i = 0; i < bitsToInit; ++i) {
        if (value & (1UL << i)) {
            bits[bitsToInit - 1 - i] = true;
        }
    }
}

BitArray::BitArray(const BitArray& b){
    bits = b.bits;
}

void BitArray::swap(BitArray &b) {
    BitArray temp = *this;
    *this = b;
    b = temp;
}

BitArray &BitArray::operator=(const BitArray &b) {
    if(this != &b){
        bits = b.bits;
    }
    return *this;
}

void BitArray::resize(int num_bits, bool value) {
    bits.resize(num_bits, value);
}

void BitArray::clear() {
    bits.clear();
}

void BitArray::push_back(bool bit) {
    bits.push_back(bit);
}

BitArray &BitArray::operator&=(const BitArray &b) {
    if(bits.size() != b.bits.size()){
        throw std::invalid_argument("BitArray's must have equal size for &=");
    }
    for(size_t i = 0; i < bits.size(); ++i){
        bits[i] = bits[i] & b.bits[i];
    }
    return *this;
}

BitArray &BitArray::operator|=(const BitArray &b) {
    if(bits.size() != b.bits.size()){
        throw std::invalid_argument("BitArray's must have equal size for |=");
    }
    for(size_t i = 0; i < bits.size(); ++i){
        bits[i] = bits[i] | b.bits[i];
    }
    return *this;
}

BitArray &BitArray::operator^=(const BitArray &b) {
    if(bits.size() != b.bits.size()){
        throw std::invalid_argument("BitArray's must have equal size for ^=");
    }
    for(size_t i = 0; i < bits.size(); ++i){
        bits[i] = bits[i] ^ b.bits[i];
    }
    return *this;
}

BitArray &BitArray::operator<<=(int n) {
    if(n == 0){
        return *this;
    }
    if(n < 0){
        return *this >>= (-n);
    }
    if(bits.empty() || n >= bits.size()){
        std::fill(bits.begin(), bits.end(), false);
        return *this;
    }
    for(size_t i = 0; i < bits.size() - n; ++i){
        bits[i] = bits[i+n];
    }
    for(size_t i = bits.size() - n; i < bits.size(); ++i){
        bits[i] = false;
    }
    return *this;
}

BitArray &BitArray::operator>>=(int n) {
    if(n == 0){
        return *this;
    }
    if(n < 0){
        return *this <<= (-n);
    }
    if (bits.empty() || n >= bits.size()) {
        std::fill(bits.begin(), bits.end(), false);
        return *this;
    }
    for (size_t i = bits.size() - 1; i >= n; --i) {
        bits[i] = bits[i - n];
    }
    for (size_t i = 0; i < n; ++i) {
        bits[i] = false;
    }
    return *this;
}

BitArray BitArray::operator<<(int n) const {
    BitArray result = *this;
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(int n) const {
    BitArray result = *this;
    result >>= n;
    return result;
}

BitArray &BitArray::set(int n, bool val) {
    bits[n] = val;
    return *this;
}

BitArray &BitArray::set() {
    for(size_t i = 0; i < size(); ++i){
        bits[i] = true;
    }
    return *this;
}

BitArray &BitArray::reset(int n) {
    bits[n] = false;
    return *this;
}

BitArray &BitArray::reset() {
    for(size_t i = 0; i < size(); ++i){
        bits[i] = false;
    }
    return *this;
}

bool BitArray::any() const {
    for(size_t i = 0; i < size(); ++i){
        if(bits[i]){
            return true;
        }
    }
    return false;
}

bool BitArray::none() const {
    return !(any());
}

BitArray BitArray::operator~() const {
    BitArray result;
    result.resize((int)bits.size());
    for(size_t i = 0; i < bits.size(); ++i){
        result.bits[i] = !(bits[i]);
    }
    return result;
}

int BitArray::count() const {
    int c = 0;
    for(size_t i = 0; i < size(); ++i){
        c+= bits[i];
    }
    return c;
}

bool BitArray::operator[](int i) const {
    if (i < 0 || i >= static_cast<int>(bits.size())) {
        throw std::out_of_range("BitArray index out of range");
    }
    return bits[i];
}

int BitArray::size() const {
    return (int)bits.size();
}

bool BitArray::empty() const {
    return bits.empty();
}

std::string BitArray::to_string() const {
    std::string result;
    for (bool bit : bits) {
        result += bit ? '1' : '0';
    }
    return result;
}

bool operator==(const BitArray & a, const BitArray & b){
    if (a.size() != b.size()) {
        return false;
    }
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

bool operator!=(const BitArray& a, const BitArray& b) {
    return !(a == b);
}

BitArray operator&(const BitArray& b1, const BitArray& b2){
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("BitArray sizes must be equal for &");
    }
    BitArray result;
    result.resize(b1.size());
    for (int i = 0; i < b1.size(); ++i) {
        result.set(i, b1[i] && b2[i]);
    }
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b2){
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("BitArray sizes must be equal for |");
    }
    BitArray result;
    result.resize(b1.size());
    for (int i = 0; i < b1.size(); ++i) {
        result.set(i, b1[i] | b2[i]);
    }
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2){
    if (b1.size() != b2.size()) {
        throw std::invalid_argument("BitArray sizes must be equal for ^");
    }
    BitArray result;
    result.resize(b1.size());
    for (int i = 0; i < b1.size(); ++i) {
        result.set(i, b1[i] ^ b2[i]);
    }
    return result;
}
