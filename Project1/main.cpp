#include <iostream>
#include "../include/HuffmanCompressor.h"
#include <map>
#include <fstream>
#include <array>

int main() {
    HuffmanCompressor compressor;

#if 0
    std::string filename = "../examples/day1.bin";

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


    std::cout << "\n================\n" << std::endl;

    // Day 5: compress 
    std::string input = "../examples/day1.bin";
    std::string output = "../examples/compressed.huf";

    compressor.compress(input, output);

    // Day 6: decompress
    compressor.decompress("../compressed.huf", "../examples/restored.bin");
#endif

    // Test for text file
	std::string input = "../examples/large.txt";
	std::string output = "../examples/large.huf";

	compressor.compress(input, output);
	compressor.decompress("../examples/large.huf", "../examples/large_restored.txt");

    return 0;
}
