/**
 * BitInputStream.hpp - declares the class BitInputStream
 * Also, declares variables and functions without implementation
 *
 * Author: Andrew Masters / Abdulkhaliq Omar
 */
#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** BitInputStream class declaration of variables
 *  and functions */
class BitInputStream {
  private:
    char buf;   // one byte buffer of bits
    int nbits;  // number of bits have been writen to buf

    istream& in;  // reference to the input stream to use

  public:
    /* Constructor of BitInputStream
     * Initializes member variable to be the proper values*/
    explicit BitInputStream(istream& is) : in(is), buf(0), nbits(8){};

    /* Fills the one byte buffer from input stream*/
    void fill();

    /* Reads the next bit from the bit buffer.
     * Fills the buffer with next byte from input stream if all
     * the bits have already been read.
     * It should return 0 if bit read is 0, and return 1 if bit read is 1.*/
    unsigned int readBit();
};

#endif
