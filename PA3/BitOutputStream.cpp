#include "BitOutputStream.h"
#include <iostream>

using namespace std;

    void BitOutputStream::flush() {
    	out << buf;  // write the bitwise buffer to the ostream
    	out.flush();   // flush the ostream (optional, slower to do it here)

    	buf = 0;       // clear the bitwise buffer
    	nbits = 0;     // bitwise buffer is cleared, so there are 0 bits in it
    }

    // write bit to the bitwise buffer
    void BitOutputStream::writeBit(unsigned int bit) {
    	// flush the bitwise buffer if it is full
        if(nbits == 8) {
            flush();
        }

      	buf |= (bit << (7-nbits));

        // increment the number of bits in our bitwise buffer
        nbits++;
	}

    void BitOutputStream::writeByte(unsigned int sym){
        int pos = 0;
        int mask = 0x80;
        while(pos < 8){
            writeBit( (sym & mask) >> (7-pos));
            mask = mask >> 1;
            pos++;
        }
    }