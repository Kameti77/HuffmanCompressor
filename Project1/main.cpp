#include <iostream>
#include "../include/HuffmanCompressor.h"
#include <map>

int main() {
    HuffmanCompressor compressor;

    std::string filename = "../day1.bin";
    compressor.buildFrequencyTable(filename);

    std::map<unsigned char, int> freqTable = compressor.getFrequencyTable();

    int total = 0;
    std::cout << "Frequencies of bytes in " << filename << ":\n";
    for (auto& pair : freqTable) {
        std::cout << "Byte 0x" << std::hex << (int)pair.first
            << " : " << std::dec << pair.second << std::endl;
        total += pair.second;
    }

    std::cout << "\nTotal bytes counted: " << total << std::endl;
    return 0;
}
