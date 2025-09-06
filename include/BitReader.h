#ifndef BITREADER_H
#define BITREADER_H

#include <fstream>
#include <vector>

class BitReader {
private:
    std::ifstream& in;
    unsigned char buffer;
    int bitCount;

public:
    BitReader(std::ifstream& input);

    bool readBit(bool& bit);
    bool readByte(unsigned char& byte);
};

#endif
