#ifndef BITOUTPUTSTREAM_H
#define BITOUTPUTSTREAM_H

#include <iostream>

typedef unsigned char byte;

using namespace std;

class BitOutputStream {
    private:
        unsigned char buf; // bitwise buffer (one byte)
        int nbits;         // number of bits that have been written to the bitwise buffer
        ostream & out;     // reference to the bytewise output stream (a C++ ostream)

    public:
        // constructor: assign 'out' to 'os', 'buf' to 0, and 'nbits' to 0
        BitOutputStream(ostream & os) : out(os), buf(0), nbits(0) {}

        // send the bitwise buffer to the output stream, and clear the bitwise buffer
        void flush();

        // write bit to the bitwise buffer
        void writeBit(unsigned int bit);

        // write byte to the bitwise buffer (encoding the character of in a leaf node)
        void writeByte(unsigned int sym);
};

#endif 