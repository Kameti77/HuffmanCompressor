#include "../include/HuffmanCompressor.h"
#include <fstream>
#include <iostream>

HuffmanCompressor::HuffmanCompressor() {
    frequencyTable.fill(0);
}

void HuffmanCompressor::buildFrequencyTable(const std::string& inputFile) {
    frequencyTable.fill(0);

    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Error: Cannot open " << inputFile << "\n";
        return;
    }

    unsigned char byte;
    while (in.read(reinterpret_cast<char*>(&byte), 1)) {
        frequencyTable[byte]++;
    }
}

std::array<size_t, 256> HuffmanCompressor::getFrequencyTable() const {
    return frequencyTable;
}

void HuffmanCompressor::compress(const std::string& inputFile, const std::string& outputFile) {
    // 1. Build frequency table
    buildFrequencyTable(inputFile);

    HuffmanTree tree;
    Node* root = tree.buildTree(frequencyTable);
    if (!root) {
        std::cerr << "Error: File empty\n";
        return;
    }

    tree.generateCodes(root);
    auto codes = tree.getCodes();

    // 2. Write header (frequency table)
    std::ofstream out(outputFile, std::ios::binary);
    if (!out) {
        std::cerr << "Error: Cannot open output " << outputFile << "\n";
        return;
    }

    for (int i = 0; i < 256; i++) {
        uint32_t f = static_cast<uint32_t>(frequencyTable[i]);
        out.write(reinterpret_cast<const char*>(&f), sizeof(f));
    }

    // 3. Encode input
    std::ifstream in(inputFile, std::ios::binary);
    std::string bitString;
    unsigned char byte;

    while (in.read(reinterpret_cast<char*>(&byte), 1)) {
        bitString += codes[byte];
    }

    // 4. Write compressed data
    BitWriter writer(out);
    writer.writeBits(bitString);
    writer.flush();

    std::cout << "Compressed -> " << outputFile << "\n";

    // Show compression ratio
    auto originalSize = getFileSize(inputFile);
    auto compressedSize = getFileSize(outputFile);


    if (originalSize > 0) {
        double ratio = (double)compressedSize / (double)originalSize;
        std::cout << "Compression ratio: " << ratio << std::endl;
    }
    else if (originalSize == 0) {
        std::cerr << "Error: Input file is empty.\n";
        return;
    }
}

void HuffmanCompressor::decompress(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream in(inputFile, std::ios::binary);
    if (!in) {
        std::cerr << "Error: Cannot open " << inputFile << "\n";
        return;
    }

    // 1. Read header
    frequencyTable.fill(0);
    for (int i = 0; i < 256; i++) {
        uint32_t f;
        in.read(reinterpret_cast<char*>(&f), sizeof(f));
        frequencyTable[i] = f;
    }

    // 2. Rebuild tree
    HuffmanTree tree;
    Node* root = tree.buildTree(frequencyTable);
    if (!root) {
        std::cerr << "Error: Invalid tree\n";
        return;
    }

    size_t totalSymbols = 0;
    for (auto f : frequencyTable) totalSymbols += f;

    // 3. Decode
    std::ofstream out(outputFile, std::ios::binary);
    BitReader reader(in);
    Node* node = root;

    size_t decoded = 0;
    bool bit;

    while (decoded < totalSymbols && reader.readBit(bit)) {
        node = bit ? node->right : node->left;

        if (!node->left && !node->right) {
            unsigned char symbol = node->value;
            out.write(reinterpret_cast<char*>(&symbol), 1);
            decoded++;
            node = root;
        }
    }

    std::cout << "Decompressed -> " << outputFile << "\n";
}
