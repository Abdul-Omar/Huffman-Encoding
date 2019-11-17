#include <iostream>
#include <string>
#include <vector>

#include <gtest/gtest.h>
#include "HCTree.hpp"

using namespace std;
using namespace testing;

class SimpleHCTreeFixture3 : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    SimpleHCTreeFixture3() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 5;
        freqs['b'] = 2;
        freqs['c'] = 1;
        freqs['d'] = 3;
        tree.build(freqs);
    }
};
class SimpleHCTreeFixture2 : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    SimpleHCTreeFixture2() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 3;
        freqs['b'] = 2;
        freqs['c'] = 1;
        freqs['d'] = 4;
        tree.build(freqs);
    }
};

class SimpleHCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    SimpleHCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 2;
        freqs['b'] = 3;
        tree.build(freqs);
    }
};
class HCTreeFixture : public ::testing::Test {
  protected:
    HCTree tree;

  public:
    HCTreeFixture() {
        // initialization code here
        vector<unsigned int> freqs(256);
        freqs['a'] = 2;
        tree.build(freqs);
    }
};

TEST_F(SimpleHCTreeFixture, TEST_ENCODE) {
    ostringstream os;
    tree.encode('a', os);
    ASSERT_EQ(os.str(), "0");
}

TEST_F(SimpleHCTreeFixture, TEST_DECODE) {
    istringstream is("1");
    ASSERT_EQ(tree.decode(is), 'b');
}

TEST_F(SimpleHCTreeFixture2, TEST_ENCODE_2) {
    ostringstream os;
    tree.encode('c', os);
    ASSERT_EQ(os.str(), "110");
}

TEST_F(SimpleHCTreeFixture2, TEST_DECODE_2) {
    istringstream is("111");
    ASSERT_EQ(tree.decode(is), 'b');
}

TEST_F(SimpleHCTreeFixture3, TEST_ENCODE_3) {
    ostringstream os;
    tree.encode('a', os);
    ASSERT_EQ(os.str(), "0");
}

TEST_F(SimpleHCTreeFixture3, TEST_ENCODE_4) {
    ostringstream os;
    tree.encode('c', os);
    ASSERT_EQ(os.str(), "100");
}

TEST_F(SimpleHCTreeFixture3, TEST_DECODE_3) {
    istringstream is("0");
    ASSERT_EQ(tree.decode(is), 'a');
}
TEST_F(SimpleHCTreeFixture3, TEST_DECODE_4) {
    istringstream is("11");
    ASSERT_EQ(tree.decode(is), 'd');
}

TEST_F(SimpleHCTreeFixture3, TEST_DECODE_5) {
    HCNode node(5, 'a', nullptr, nullptr);
    cout << node;
}

TEST_F(HCTreeFixture, TEST_DECODE_6) {
    istringstream is("0");
    ASSERT_EQ(tree.decode(is), 'a');
}
TEST_F(HCTreeFixture, TEST_ENCODE_6) {
    ostringstream os;
    tree.encode('a', os);
    ASSERT_EQ(os.str(), "0");
}
TEST_F(SimpleHCTreeFixture3, TEST_ENCODE_WITH_BITOUTPUT) {
    stringstream ss;
    BitOutputStream bos(ss);

    tree.encode('a', bos);
    ASSERT_EQ(0, 0);
}
TEST_F(SimpleHCTreeFixture3, TEST_DECODE_WITH_BITINPUT) {
    string bitsStr = "10000000";
    string ascii = string(1, stoi(bitsStr, nullptr, 2));

    stringstream ss;
    ss.str(ascii);
    BitInputStream bis(ss);

    ASSERT_EQ('c', tree.decode(bis));
}
