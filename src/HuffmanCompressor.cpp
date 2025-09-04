#include "../include/HuffmanCompressor.h"
//#include "BitWriter.h"
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

void HuffmanCompressor::compress(const std::string& inputFile, const std::string& outputFile) {
    // TODO: implement Huffman compression using HuffmanTree + BitWriter
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