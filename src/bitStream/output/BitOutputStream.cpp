/**
 * BitOutputStream.cpp
 * Implements functions that were declared in BitOutputStream.hpp
 *
 * Author: Andrew Masters / Abdulkhaliq Omar
 */
#include "BitOutputStream.hpp"

/* Sends the buffer to the output stream, and then clear
 *the buffer to allow further use.
 */
void BitOutputStream::flush() {
    out.write((char*)&buf, sizeof(buf));

    // clear buffer stream
    out.flush();

    buf = 0;    // empty out buffer
    nbits = 0;  // set nbits to zero
}

/* Writes the least significant bit of the given int to the bit buffer.
 * Flushes the buffer first if it is full (which means
 * all the bits in the buffer have already been written out).
 */
void BitOutputStream::writeBit(int i) {
    int maxBits = 8;  // max number of bits to send to output

    // if buffer is full,flush it first
    if (nbits == maxBits) {
        flush();
    }

    // set bit if i is 1 else unset bit
    i == 1 ? buf |= (1 << (7 - nbits)) : buf &= ~(1 << (7 - nbits));

    nbits++;  // increment bits read so far
}
