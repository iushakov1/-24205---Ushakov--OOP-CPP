#include "bitarray.h"

#include <iostream>
#include <stdexcept>

#define byteToBits 8

BitArray::BitArray(int numBits, unsigned int value) {
    if (numBits < 0) {
        throw std::invalid_argument("Number of bytes cannot be negative");
    }
    //bytes.resize(numBits, value);
    this->resize(numBits, value);
}

BitArray::BitArray(const BitArray& b){
    bytes = b.bytes;
    bitCount = b.bitCount;
}

void BitArray::swap(BitArray &b) {
    BitArray temp = *this;
    *this = b;
    b = temp;
}

BitArray& BitArray::operator=(const BitArray &b) {
    if(this != &b){
        bytes = b.bytes;
        bitCount = b.bitCount;
    }
    return *this;
}

void BitArray::resize(int numBits, unsigned int value) {
    if(numBits > bitCount){
        bytes.resize((numBits / byteToBits) + (numBits % byteToBits != 0), false);
        int valueBitInx = 0;
        for(int i = sizeof(value)*8 - 1; i >= 0; --i){
            if(1<<i & value){
                valueBitInx = i;
                break;
            }
        }
        for(int i = bitCount; i < numBits; ++i){
            auto& curByte = bytes[i / byteToBits];
            if(value & (1 << (valueBitInx))){
                curByte |= (1 << (byteToBits - i%byteToBits - 1));
            }
            --valueBitInx;
            if(valueBitInx < 0){
                break;
            }
        }
    }
    else{
        bytes.resize((numBits / byteToBits) + (numBits % byteToBits != 0), false);
    }
    bitCount = numBits;
}

void BitArray::clear() {
    bytes.clear();
    bitCount = 0;
}

void BitArray::push_back(bool bit) {
    this->resize(bitCount + 1, bit ? 1 : 0);
}

BitArray &BitArray::operator&=(const BitArray &b) {
    if(bitCount != b.bitCount){
        throw std::invalid_argument("BitArray's must have equal size for &=");
    }
    for(size_t i = 0; i < bytes.size(); ++i){
        bytes[i] = bytes[i] & b.bytes[i];
    }
    return *this;
}

BitArray &BitArray::operator|=(const BitArray &b) {
    if(bitCount != b.bitCount){
        throw std::invalid_argument("BitArray's must have equal size for |=");
    }
    for(size_t i = 0; i < bytes.size(); ++i){
        bytes[i] = bytes[i] | b.bytes[i];
    }
    return *this;
}

BitArray &BitArray::operator^=(const BitArray &b) {
    if(bitCount != b.bitCount){
        throw std::invalid_argument("BitArray's must have equal size for ^=");
    }
    for(size_t i = 0; i < bytes.size(); ++i){
        bytes[i] = bytes[i] ^ b.bytes[i];
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
    if(n >= bitCount){
        std::fill(bytes.begin(), bytes.end(), false);
        return *this;
    }
    for(int i = 0; i < bitCount; ++i){
        (*this)[i] = (*this)[i+n];
    }
    for(int i = bitCount - n; i < bitCount; ++i){
        (*this)[i] = false;
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
    if (n >= bitCount) {
        std::fill(bytes.begin(), bytes.end(), false);
        return *this;
    }
    for(int i = bitCount - 1; i >= n; --i){
        (*this)[i] = (*this)[i-n];
    }
    for(int i = 0; i < n; ++i){
        (*this)[i] = false;
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
    if(val == false){
        bytes[n/byteToBits] &= ~(1 << (byteToBits - n%byteToBits - 1));
    }
    else{
        bytes[n/byteToBits] |= (1 << (byteToBits - n%byteToBits - 1));
    }
    return *this;
}

BitArray &BitArray::set() {
    for(int i = 0; i < bitCount; ++i){
        bytes[i/byteToBits] |= (1 << (byteToBits - i%byteToBits - 1));
    }
    return *this;
}

BitArray &BitArray::reset(int n) {
    bytes[n/byteToBits] &= ~(1 << (byteToBits - n%byteToBits - 1));
    return *this;
}

BitArray &BitArray::reset() {
    for(int i = 0; i < bitCount; ++i){
        bytes[i/byteToBits] &= ~(1 << (byteToBits - i%byteToBits - 1));
    }
    return *this;
}

bool BitArray::any() const {
    for(int i = 0; i < bitCount; ++i){
        if((*this)[i]){
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
    result.resize(bitCount);
    for(int i = 0; i < bitCount; ++i){
        result[i] = !(*this)[i];
    }
    return result;
}

int BitArray::count() const {
    int c = 0;
    for(int i = 0; i < bitCount; ++i){
        c += (*this)[i];
    }
    return c;
}

BitArray::Bit::Bit(std::vector<uint8_t>& bytes, int bitInx) : bytes(bytes), bitInx(bitInx) {}
BitArray::Bit::operator bool() const noexcept {
    return bool(( 1<<(byteToBits - bitInx%byteToBits - 1) ) & ( bytes[bitInx/byteToBits] ));
}

BitArray::Bit &BitArray::Bit::operator=(bool v) noexcept {
    if(!v){
        bytes[bitInx/byteToBits] &= ~(1 << (byteToBits - bitInx%byteToBits - 1));
    }
    else{
        bytes[bitInx/byteToBits] |= (1 << (byteToBits - bitInx%byteToBits - 1));
    }
    return *this;
}

BitArray::Bit &BitArray::Bit::operator=(const BitArray::Bit &other) noexcept {
    bool value = static_cast<bool>(other);
    *this = value;
    return *this;
}

BitArray::Bit BitArray::operator[](int i) {
    if (i < 0 || i >= bytes.size()*byteToBits) {
        throw std::out_of_range("BitArray index out of range");
    }
    return Bit(bytes, i);
}

bool BitArray::operator[](int i) const{
    if (i < 0 || i >= bytes.size()*byteToBits) {
        throw std::out_of_range("BitArray index out of range");
    }
    return bytes[i/byteToBits] & 1<<(byteToBits - i%byteToBits - 1);
}

int BitArray::size() const {
    return bytes.size();
}

bool BitArray::empty() const {
    return bitCount == 0;
}

std::string BitArray::to_string() const {
    std::string result;
    for(int i = 0; i < bitCount; ++i){
        result += (*this)[i] ? '1' : '0';
    }
    return result;
}

bool operator==(const BitArray & a, const BitArray & b){
    if (a.getBitCount() != b.getBitCount()) {
        return false;
    }
    for (int i = 0; i < a.getBitCount(); ++i) {
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
    if (b1.getBitCount() != b2.getBitCount()) {
        throw std::invalid_argument("BitArray sizes must be equal for &");
    }
    BitArray result;
    result.resize(b1.getBitCount());
    for (int i = 0; i < b1.getBitCount(); ++i) {
        auto val = b1[i] && b2[i];
        result.set(i, b1[i] && b2[i]);
    }
    return result;
}

BitArray operator|(const BitArray& b1, const BitArray& b2){
    if (b1.getBitCount() != b2.getBitCount()) {
        throw std::invalid_argument("BitArray sizes must be equal for |");
    }
    BitArray result;
    result.resize(b1.getBitCount());
    for (int i = 0; i < b1.getBitCount(); ++i) {
        result.set(i, b1[i] | b2[i]);
    }
    return result;
}

BitArray operator^(const BitArray& b1, const BitArray& b2){
    if (b1.getBitCount() != b2.getBitCount()) {
        throw std::invalid_argument("BitArray sizes must be equal for ^");
    }
    BitArray result;
    result.resize(b1.getBitCount());
    for (int i = 0; i < b1.getBitCount(); ++i) {
        result.set(i, b1[i] ^ b2[i]);
    }
    return result;
}

int BitArray::getBitCount() const {
    return bitCount;
}