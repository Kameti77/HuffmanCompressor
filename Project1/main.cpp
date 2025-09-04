#include <iostream>
#include "../include/HuffmanCompressor.h"
#include <map>
#include <fstream>
#include <array>

int main() {
#if 1
    HuffmanCompressor compressor;
    
    std::string filename = "../day1.bin";

    // Day 1: build frequency table
    compressor.buildFrequencyTable(filename);

    auto freqTable = compressor.getFrequencyTable();

    int total = 0;
    std::cout << "Frequencies of bytes in " << filename << ":\n";
    for (auto& freq : freqTable) {
        total += freq;
    }
    

    std::cout << "\nTotal bytes counted: " << total << std::endl;


    std::cout << "\n================\n" << std::endl;
    // Day 2: build Huffman tree

    HuffNode* root = compressor.GenerateTree(freqTable);

    // Day 3: generate Huffman codes
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


    // Print first 10 codes
    compressor.PrintFirstCodes(10);

    std::cout << "\n================\n" << std::endl;

    // Day 4: encode file
    std::string encodedBits = compressor.encodeFile(filename);
    std::cout << "Encoded length (bits): " << encodedBits.size() << std::endl;
#endif

    return 0;
}
