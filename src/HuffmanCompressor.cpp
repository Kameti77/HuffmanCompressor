#include "HuffmanCompressor.h"
#include "BitWriter.h"
#include "BitReader.h"
#include <fstream>
#include <iostream>

std::unordered_map<char, int> HuffmanCompressor::buildFrequencyMap(const std::string& inputFile) {
    std::unordered_map<char, int> freqMap;
    // TODO: read file and count characters
    return freqMap;
}

void HuffmanCompressor::compress(const std::string& inputFile, const std::string& outputFile) {
    // TODO: implement Huffman compression using HuffmanTree + BitWriter
}

void HuffmanCompressor::decompress(const std::string& inputFile, const std::string& outputFile) {
    // TODO: implement Huffman decompression using BitReader + HuffmanTree
}
