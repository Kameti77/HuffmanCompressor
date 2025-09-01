#include "BitReader.h"

BitReader::BitReader(const std::string& filename) : buffer(0), bitCount(0) {
    in.open(filename, std::ios::binary);
}

BitReader::~BitReader() {
    in.close();
}

bool BitReader::readBit(bool& bit) {
    // TODO: read bit from buffer
    return false;
}

bool BitReader::readByte(unsigned char& byte) {
    // TODO: read byte
    return false;
}
