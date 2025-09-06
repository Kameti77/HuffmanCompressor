#include "../include/HuffmanCompressor.h"
#include "../include/BitWriter.h"
//#include "BitReader.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <array>

using namespace std;
void HuffmanCompressor::buildFrequencyTable(const std::string& inputFile) {
   // mFrequencyTable.clear();
    // mFrequencyTable.fill(0);

    // read file and count characters
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Error: Cannot open file " << inputFile << std::endl;
        return;
    }

    unsigned char ch;
    while (in.read(reinterpret_cast<char*>(&ch), 1)) {
        mFrequencyTable[ch]++;
    }

    in.close();
}

std::array<size_t, 256> HuffmanCompressor::getFrequencyTable() const {
    return mFrequencyTable;
}



void HuffmanCompressor::decompress(const std::string& inputFile, const std::string& outputFile) {
    // TODO: implement Huffman decompression using BitReader + HuffmanTree
}



HuffNode* HuffmanCompressor::GenerateTree(const std::array<size_t, 256>& freqs) {
    std::priority_queue<HuffNode*, std::vector<HuffNode*>, CompareNode> pq;

    // Create leaf nodes for all nonzero frequencies
    std::vector<size_t> frequencies(freqs.begin(), freqs.end());

    for (size_t i = 0; i < frequencies.size(); ++i) {
        if (freqs[i] > 0) {
            pq.push(new HuffNode(i, freqs[i]));
        }
    }

    while (pq.size() > 1) {
        HuffNode* tempLeft = pq.top();
        pq.pop();
        HuffNode* tempRight = pq.top();
        pq.pop();
        unsigned int totalFreq = tempLeft->freq + tempRight->freq;
        HuffNode* newParent = new HuffNode(-1, totalFreq, tempLeft, tempRight);
        tempLeft->parent = newParent;
        tempRight->parent = newParent;
        pq.push(newParent);
    }
    mRoot = pq.top(); 

    return mRoot;
}

void HuffmanCompressor::FreeTree(HuffNode* root) {
    if (!root) return;
    FreeTree(root->left);
    FreeTree(root->right);
    delete root;
}

// Recursive code generation
void HuffmanCompressor::GenerateCodesRecursive(HuffNode* node, const std::string& prefix) {
    if (!node) return;

    if (!node->left && !node->right) {
        mCodes[node->value] = prefix;
        return;
    }

    GenerateCodesRecursive(node->left, prefix + "0");
    GenerateCodesRecursive(node->right, prefix + "1");
}

void HuffmanCompressor::GenerateCodes(HuffNode* root) {
    mCodes.clear();
    GenerateCodesRecursive(root, "");
}

void HuffmanCompressor::PrintFirstCodes(int n) {
    int count = 0;
    for (auto& pair : mCodes) {
        std::cout << (int)pair.first << " : " << pair.second << std::endl;
        if (++count >= n) break;
    }
}

std::string HuffmanCompressor::encodeFile(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "Error: cannot open file " << filename << std::endl;
        return "";
    }

    std::string encodedBits;
    unsigned char byte;

    while (in.read(reinterpret_cast<char*>(&byte), 1)) {
        encodedBits += mCodes[byte];  // append Huffman code for each byte
    }

    // Debug: show first 64 bits
    std::cout << "First 64 bits: "
        << encodedBits.substr(0, 64) << std::endl;

    return encodedBits;
} 

void HuffmanCompressor::compress(const std::string& inputFile, const std::string& outputFile) {
    // 1. Build frequency table
    buildFrequencyTable(inputFile);
    auto freqTable = this->getFrequencyTable();

    // 2. Build tree and codes
    HuffNode* root = GenerateTree(freqTable);
    GenerateCodes(root);

    // 3. Open output file
    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Cannot open output file: " << outputFile << std::endl;
        return;
    }

    // 4. Write header (frequency table, 256 ints)
    for (int i = 0; i < 256; i++) {
        int freq = freqTable[(unsigned char)i];
        out.write(reinterpret_cast<const char*>(&freq), sizeof(int));
    }

    // 5. Encode input file into bitstring
    std::string bitString = encodeFile(inputFile);

    // 6. Use BitWriter for compressed data
    BitWriter writer(out);
    writer.writeBits(bitString);
    writer.flush();

    std::cout << "Compressed file written: " << outputFile << std::endl;

    FreeTree(root);
}
