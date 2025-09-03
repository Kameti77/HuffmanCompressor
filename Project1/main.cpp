#include <iostream>
#include "../include/HuffmanCompressor.h"
#include <map>
#include <fstream>
#include <array>

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


    std::cout << "\n================\n" << std::endl;
    std::ifstream in("../src/test.bin", std::ios::binary);

    if (!in) {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    std::array<size_t, 256> freq = { 0 };
    unsigned char byte;

    while (in.read(reinterpret_cast<char*>(&byte), 1)) {
        freq[byte]++;
        total++;
    }

   
    HuffNode* root = compressor.GenerateTree(freq);
    compressor.GenerateCodes(root);

    if (root) {
        std::cout << "Root frequency = " << root->freq
            << " (file size = " << total << " bytes)\n";
        compressor.FreeTree(root);
    }
    else {
        std::cout << "File empty, no tree built.\n";
    }

    std::cout << "\n================\n" << std::endl;
    compressor.printFirstCodes(10);


    return 0;

}
