/**
 * BitInputStream.cpp
 * Implementation of functions defined in BitInputStream.hpp
 *
 * Author: Andrew Masters / Abdulkhaliq Omar
 */
#include "BitInputStream.hpp"
#include <cstdio>

/* Fills the one byte buffer from input stream*/
void BitInputStream::fill() {
    // read one byte from input stream into buf char array
    buf = in.get();
    nbits = 0;
}

/* Reads the next bit from the bit buffer.
 * Fills the buffer with next byte from input stream if all the bits
 * have already been read.
 * It should return 0 if bit read is 0, and return 1 if bit read is 1. */
unsigned int BitInputStream::readBit() {
    int maxBits = 8;  // max number of bits to read
    int maxDigits = 7;

    // if 8 bits were already read, get next byte
    if (nbits == maxBits) {
        fill();
    }

    unsigned char mask = 1;

    unsigned char bit =
        (buf & (mask << maxDigits - nbits)) >> (maxDigits - nbits);

    nbits++;  // increment number of bits read so far

    return bit;  // return the bits
}
