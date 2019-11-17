/**
 * BitOutputStream.hpp ; defines the class BitOutputStream
 * Also declares the variables and functions for the class
 *
 * Author: Andrew Masters / Abdulkhaliq Omar
 */
#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>

typedef unsigned char byte;

using namespace std;

/** Declaration of BitOutputStream; functions declared but not implemented */
class BitOutputStream {
  private:
    char buf;      // one byte buffer of bits
    int nbits;     // number of bits have been writen to buf
    ostream& out;  // reference to the output stream to use

  public:
    /* Class Constructor that sets the variables */
    explicit BitOutputStream(ostream& os) : out(os), nbits(0), buf(0){};

    /* Sends the buffer to the output stream,
     * then clear the buffer to allow further use.*/
    void flush();

    /* Writes the least significant bit of the given int to the bit buffer.
     * Flushes the buffer first if it is full.
     * Assume the given int is either 0 or 1.*/
    void writeBit(int i);
};

#endif
