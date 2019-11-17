#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include "BitOutputStream.hpp"

using namespace std;
using namespace testing;

TEST(BitOutputStreamTests, SIMPLE_TEST) {
    stringstream ss;
    BitOutputStream bos(ss);
    bos.writeBit(1);
    bos.flush();

    string bitsStr = "10000000";
    unsigned int asciiVal = stoi(bitsStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}

TEST(BitOutputStreamTests, SIMPLE_TEST_2) {
    stringstream ss;
    BitOutputStream bos(ss);
    bos.writeBit(0);
    bos.flush();

    string bitsStr = "00000000";
    unsigned int asciiVal = stoi(bitsStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}

TEST(BitOutputStreamTests, SIMPLE_TEST_3) {
    stringstream ss;
    BitOutputStream bos(ss);
    bos.writeBit(1);
    bos.writeBit(1);

    bos.flush();

    string bitsStr = "11000000";
    unsigned int asciiVal = stoi(bitsStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}

TEST(BitOutputStreamTests, SIMPLE_TEST_4) {
    stringstream ss;
    BitOutputStream bos(ss);
    bos.writeBit(1);
    bos.writeBit(0);
    bos.writeBit(1);
    bos.writeBit(1);

    bos.flush();

    string bitsStr = "10110000";
    unsigned int asciiVal = stoi(bitsStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}

TEST(BitOutputStreamTests, SIMPLE_TEST_5) {
    stringstream ss;
    BitOutputStream bos(ss);

    bos.writeBit(1);
    bos.writeBit(0);
    bos.writeBit(1);
    bos.writeBit(1);
    bos.writeBit(1);
    bos.writeBit(0);
    bos.writeBit(1);
    bos.writeBit(1);

    bos.flush();

    string bitsStr = "10111011";

    unsigned int asciiVal = stoi(bitsStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}

TEST(BitOutputStreamTests, SIMPLE_TEST_6) {
    stringstream ss;
    BitOutputStream bos(ss);
    bos.writeBit(1);
    bos.writeBit(0);
    bos.writeBit(1);
    bos.writeBit(1);
    bos.writeBit(1);
    bos.writeBit(0);
    bos.writeBit(1);

    bos.flush();

    string bitsStr = "10111010";
    unsigned int asciiVal = stoi(bitsStr, nullptr, 2);
    ASSERT_EQ(ss.get(), asciiVal);
}
