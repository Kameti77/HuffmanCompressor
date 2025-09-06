#include "../include/BitWriter.h"
#include <iostream>

BitWriter::BitWriter(std::ofstream& outputStream)
    : out(outputStream), buffer(0), bitCount(0) {
}

BitWriter::~BitWriter() {
    flush(); // flush any pending bits before destruction
}

void BitWriter::writeBit(bool bit) {
    buffer = (buffer << 1) | bit;
    bitCount++;

    if (bitCount == 8) {
        out.write(reinterpret_cast<const char*>(&buffer), 1);
        bitCount = 0;
        buffer = 0;
    }
}

void BitWriter::writeBits(const std::string& bits) {
    for (char c : bits) {
        writeBit(c == '1');
    }
}

void BitWriter::flush() {
    if (bitCount > 0) {
        buffer <<= (8 - bitCount);
        out.write(reinterpret_cast<const char*>(&buffer), 1);
        bitCount = 0;
        buffer = 0;
    }
}
