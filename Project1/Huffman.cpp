#include "Huffman.h"
#include <fstream>
#include <iostream>

using namespace std;
void HuffmanCompressor::buildFrequencyTable(const std::string& inputFile) {
    frequencyTable.clear();
    // read file and count characters
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Error: Cannot open file " << inputFile << std::endl;
        return;
    }

    unsigned char ch;
    while (in.read(reinterpret_cast<char*>(&ch), 1)) {
        frequencyTable[ch]++;
    }

    in.close();
}

std::map<unsigned char, int> HuffmanCompressor::getFrequencyTable() const {
    return frequencyTable;
}

void HuffmanCompressor::compress(const std::string& inputFile, const std::string& outputFile) {
    // TODO: implement Huffman compression using HuffmanTree + BitWriter
}

void HuffmanCompressor::decompress(const std::string& inputFile, const std::string& outputFile) {
    // TODO: implement Huffman decompression using BitReader + HuffmanTree
}
