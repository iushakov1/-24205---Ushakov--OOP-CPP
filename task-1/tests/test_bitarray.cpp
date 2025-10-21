#include <gtest/gtest.h>
#include "bitarray.h"

// Constructors tests
TEST(BitArray, DefaultConstructor) {
    BitArray ba;
    EXPECT_TRUE(ba.empty());
    EXPECT_EQ(ba.size(), 0);
}

TEST(BitArray, SizeConstructor) {
    BitArray ba(5);
    EXPECT_EQ(ba.size(), 5);
    EXPECT_TRUE(ba.none());
}

TEST(BitArray, ValueConstructor) {
    BitArray ba(4, 0b1100);
    EXPECT_EQ(ba.size(), 4);
    EXPECT_EQ(ba.count(), 2);
}

TEST(BitArray, CopyConstructor) {
    BitArray original(4, 0b1010);
    BitArray copy(original);
    EXPECT_EQ(original.size(), copy.size());
    for (int i = 0; i < original.size(); ++i) {
        EXPECT_EQ(original[i], copy[i]);
    }
}

TEST(BitArray, NegativeNumBits){
    EXPECT_THROW(BitArray ba(-4),std::invalid_argument);
}

// memory access tests
TEST(BitArray, Swap) {
    BitArray a(3, 0b101);
    BitArray b(2, 0b10);

    a.swap(b);

    EXPECT_EQ(a.size(), 2);
    EXPECT_EQ(b.size(), 3);
    EXPECT_TRUE(a[0]);
    EXPECT_FALSE(a[1]);
    EXPECT_TRUE(b[0]);
    EXPECT_FALSE(b[1]);
    EXPECT_TRUE(b[2]);
}

TEST(BitArray, AssignmentOperator) {
    BitArray a(3, 0b101);
    BitArray b(2, 0b10);

    a = b;

    EXPECT_EQ(a.size(), 2);
    EXPECT_TRUE(a[0]);
    EXPECT_FALSE(a[1]);
}

TEST(BitArray, Resize) {
    BitArray ba(3, 0b101);
    ba.resize(5, true);

    EXPECT_EQ(ba.size(), 5);
    EXPECT_TRUE(ba[0]);
    EXPECT_FALSE(ba[1]);
    EXPECT_TRUE(ba[2]);
    EXPECT_TRUE(ba[3]);
    EXPECT_TRUE(ba[4]);
}

TEST(BitArray, Clear) {
    BitArray ba(5, 0b11111);
    ba.clear();

    EXPECT_TRUE(ba.empty());
    EXPECT_EQ(ba.size(), 0);
}

TEST(BitArray, PushBack) {
    BitArray ba;
    ba.push_back(true);
    ba.push_back(false);
    ba.push_back(true);

    EXPECT_EQ(ba.size(), 3);
    EXPECT_TRUE(ba[0]);
    EXPECT_FALSE(ba[1]);
    EXPECT_TRUE(ba[2]);
}

// Bitwise operations tests
TEST(BitArray, BitwiseAND) {
    BitArray a(4, 0b1100);
    BitArray b(4, 0b1010);

    a &= b;

    EXPECT_EQ(a.to_string(), "1000");
}

TEST(BitArray, BitwiseOR) {
    BitArray a(4, 0b1100);
    BitArray b(4, 0b1010);

    a |= b;

    EXPECT_EQ(a.to_string(), "1110");
}

TEST(BitArray, BitwiseXOR) {
    BitArray a(4, 0b1100);
    BitArray b(4, 0b1010);

    a ^= b;

    EXPECT_EQ(a.to_string(), "0110");
}

TEST(BitArray, BitwiseOperationsDifferentSize) {
    BitArray a(3);
    BitArray b(4);

    EXPECT_THROW(a &= b, std::invalid_argument);
    EXPECT_THROW(a |= b, std::invalid_argument);
    EXPECT_THROW(a ^= b, std::invalid_argument);
}

// bit shift operators tests
TEST(BitArray, LeftShiftAssignment) {
    BitArray ba(4, 0b1101);

    ba <<= 1;

    EXPECT_EQ(ba.to_string(), "1010");
}

TEST(BitArray, ShiftLeftZero) {
    BitArray ba(4, 0b1101);
    BitArray original = ba;
    ba <<= 0;
    EXPECT_EQ(ba, original);
    EXPECT_EQ(ba.to_string(), "1101");
}

TEST(BitArray, ShiftLeftNegative) {
    BitArray ba(4, 0b1101);
    ba <<= -2;
    EXPECT_EQ(ba.to_string(), "0011");
}

TEST(BitArray, RightShiftAssignment) {
    BitArray ba(4, 0b1101);

    ba >>= 1;

    EXPECT_EQ(ba.to_string(), "0110");
}

TEST(BitArray, ShiftRightZero) {
    BitArray ba(4, 0b1101);
    BitArray original = ba;
    ba >>= 0;
    EXPECT_EQ(ba, original);
    EXPECT_EQ(ba.to_string(), "1101");
}

TEST(BitArray, ShiftRightNegative) {
    BitArray ba(4, 0b1101);
    ba >>= -2;
    EXPECT_EQ(ba.to_string(), "0100");
}

TEST(BitArray, LeftShift) {
    BitArray ba(4, 0b1101);

    BitArray result = ba << 2;

    EXPECT_EQ(result.to_string(), "0100");
    EXPECT_EQ(ba.to_string(), "1101");
}

TEST(BitArray, RightShift) {
    BitArray ba(4, 0b1101);

    BitArray result = ba >> 2;

    EXPECT_EQ(result.to_string(), "0011");
    EXPECT_EQ(ba.to_string(), "1101");
}

TEST(BitArray, ShiftBeyondSize) {
    BitArray ba(3, 0b111);

    ba <<= 5;

    EXPECT_EQ(ba.to_string(), "000");
}

TEST(BitArray, NegativeShift) {
    BitArray ba(4, 0b1101);

    ba <<= -1;

    EXPECT_EQ(ba.to_string(), "0110");
}

TEST(BitArray, BitsIsEmptyOrNIsBigger){
    BitArray ba1(0);
    BitArray ba2(3, 0b101);
    ba1 <<= 2;
    ba2 <<= 5;
    EXPECT_EQ(ba1.to_string(), "");
    EXPECT_EQ(ba2.to_string(), "000");

    BitArray ba3(0);
    BitArray ba4(3, 0b101);
    ba1 >>= 2;
    ba2 >>= 5;
    EXPECT_EQ(ba1.to_string(), "");
    EXPECT_EQ(ba2.to_string(), "000");
}

// set bits operators tests
TEST(BitArray, SetSingleBit) {
    BitArray ba(4);

    ba.set(1, true);
    ba.set(3, true);

    EXPECT_EQ(ba.to_string(), "0101");
}

TEST(BitArray, SetAllBits) {
    BitArray ba(4);

    ba.set();

    EXPECT_EQ(ba.to_string(), "1111");
    EXPECT_EQ(ba.count(), 4);
}

TEST(BitArray, ResetSingleBit) {
    BitArray ba(4, 0b1111);

    ba.reset(0);
    ba.reset(2);

    EXPECT_EQ(ba.to_string(), "0101");
}

TEST(BitArray, ResetAllBits) {
    BitArray ba(4, 0b1111);

    ba.reset();

    EXPECT_EQ(ba.to_string(), "0000");
    EXPECT_EQ(ba.count(), 0);
}

// check bits test
TEST(BitArray, Any) {
    BitArray empty(3);
    BitArray some(4, 0b1000);
    BitArray full(3, 0b111);

    EXPECT_FALSE(empty.any());
    EXPECT_TRUE(some.any());
    EXPECT_TRUE(full.any());
}

TEST(BitArray, None) {
    BitArray empty(3);
    BitArray some(4, 0b1000);
    BitArray full(3, 0b111);

    EXPECT_TRUE(empty.none());
    EXPECT_FALSE(some.none());
    EXPECT_FALSE(full.none());
}

TEST(BitArray, NotOperator) {
    BitArray ba(4, 0b1100);

    BitArray result = ~ba;

    EXPECT_EQ(result.to_string(), "0011");
    EXPECT_EQ(ba.to_string(), "1100");
}

TEST(BitArray, Count) {
    BitArray empty(3);
    BitArray some(4, 0b1010);
    BitArray full(3, 0b111);

    EXPECT_EQ(empty.count(), 0);
    EXPECT_EQ(some.count(), 2);
    EXPECT_EQ(full.count(), 3);
}

// bits access tests
TEST(BitArray, OperatorBrackets) {
    BitArray ba(4, 0b1010);

    EXPECT_TRUE(ba[0]);
    EXPECT_FALSE(ba[1]);
    EXPECT_TRUE(ba[2]);
    EXPECT_FALSE(ba[3]);
}

TEST(BitArray, OperatorBracketsOutOfRange) {
    BitArray ba(3);

    EXPECT_THROW(ba[-1], std::out_of_range);
    EXPECT_THROW(ba[3], std::out_of_range);
}

TEST(BitArray, Size) {
    BitArray empty;
    BitArray small(3);
    BitArray large(100);

    EXPECT_EQ(empty.size(), 0);
    EXPECT_EQ(small.size(), 3);
    EXPECT_EQ(large.size(), 100);
}

TEST(BitArray, Empty) {
    BitArray empty;
    BitArray nonEmpty(1);

    EXPECT_TRUE(empty.empty());
    EXPECT_FALSE(nonEmpty.empty());
}

TEST(BitArray, ToString) {
    BitArray ba(4, 0b1101);

    std::string result = ba.to_string();

    EXPECT_EQ(result, "1101");
}

TEST(BitArray, ToStringEmpty) {
    BitArray ba;

    std::string result = ba.to_string();

    EXPECT_EQ(result, "");
}

// Comparison operators tests
TEST(BitArray, EqualityOperator) {
    BitArray a(4, 0b1100);
    BitArray b(4, 0b1100);
    BitArray c(4, 0b1010);
    BitArray d(3, 0b110);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a == d);
}

TEST(BitArray, InequalityOperator) {
    BitArray a(4, 0b1100);
    BitArray b(4, 0b1010);

    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a != a);
}

// Bitwise operators tests
TEST(BitArray, GlobalAND) {
    BitArray a(4, 0b1100);
    BitArray b(4, 0b1010);

    BitArray result = a & b;

    EXPECT_EQ(result.to_string(), "1000");
    EXPECT_EQ(a.to_string(), "1100");
    EXPECT_EQ(b.to_string(), "1010");
}

TEST(BitArray, GlobalOR) {
    BitArray a(4, 0b1100);
    BitArray b(4, 0b1010);

    BitArray result = a | b;

    EXPECT_EQ(result.to_string(), "1110");
}

TEST(BitArray, GlobalXOR) {
    BitArray a(4, 0b1100);
    BitArray b(4, 0b1010);

    BitArray result = a ^ b;

    EXPECT_EQ(result.to_string(), "0110");
}

TEST(BitArray, GlobalOperationsDifferentSize) {
    BitArray a(3);
    BitArray b(4);

    EXPECT_THROW(a & b, std::invalid_argument);
    EXPECT_THROW(a | b, std::invalid_argument);
    EXPECT_THROW(a ^ b, std::invalid_argument);
}

// edge cases
TEST(BitArray, SingleBitArray) {
    BitArray ba(1, true);

    EXPECT_EQ(ba.size(), 1);
    EXPECT_TRUE(ba[0]);
    EXPECT_TRUE(ba.any());
    EXPECT_FALSE(ba.none());
    EXPECT_EQ(ba.count(), 1);
    EXPECT_EQ(ba.to_string(), "1");

    ba.reset();
    EXPECT_FALSE(ba[0]);

    ba.set();
    EXPECT_TRUE(ba[0]);
}

TEST(BitArray, LargeArray) {
    BitArray ba(1000, 0xFFFFFFFF);

    EXPECT_EQ(ba.size(), 1000);
    EXPECT_EQ(ba.count(), 32);

    ba.reset(36);
    EXPECT_EQ(ba.count(), 31);
}

TEST(BitArray, SelfAssignment) {
    BitArray ba(4, 0b1100);
    ba = ba;
    EXPECT_EQ(ba.to_string(), "1100");
}

TEST(BitArray, ChainOperations) {
    BitArray ba(4, 0b1111);
    ba.set(0, false).reset(1).set(2, true).set(3, false);
    EXPECT_EQ(ba.to_string(), "0010");
}