#include "../include/BitReader.h"

BitReader::BitReader(std::ifstream& input) : in(input), buffer(0), bitCount(0) {}

bool BitReader::readBit(bool& bit) {
    if (bitCount == 0) {
        if (!in.read(reinterpret_cast<char*>(&buffer), 1))
            return false; // no more data
        bitCount = 8;
    }

    bit = (buffer >> (bitCount - 1)) & 1;
    bitCount--;
    return true;
}

bool BitReader::readByte(unsigned char& byte) {
    return static_cast<bool>(in.read(reinterpret_cast<char*>(&byte), 1));
}

