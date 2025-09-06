#ifndef BITWRITER_H
#define BITWRITER_H

#include <fstream>
#include <string>

class BitWriter {
private:
    std::ofstream& out;
    unsigned char buffer;
    int bitCount;

public:
    BitWriter(std::ofstream& outputStream);
    ~BitWriter();

    void writeBit(bool bit);
    void writeBits(const std::string& bits);
    void flush();  // flush remaining bits (pad with zeros)
};

#endif
