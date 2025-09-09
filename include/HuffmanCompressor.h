#ifndef HUFFMANCOMPRESSOR_H
#define HUFFMANCOMPRESSOR_H

#include "ICompressor.h"
#include "HuffmanTree.h"
#include "BitWriter.h"
#include "BitReader.h"
#include <array>
#include <map>
#include <string>

class HuffmanCompressor : public ICompressor {
private:
    std::array<size_t, 256> frequencyTable;

public:
    HuffmanCompressor();

    // Core operations
    void buildFrequencyTable(const std::string& inputFile);
    std::array<size_t, 256> getFrequencyTable() const;

    // Implement ICompressor
    void compress(const std::string& inputFile, const std::string& outputFile) override;
    void decompress(const std::string& inputFile, const std::string& outputFile) override;

    size_t getFileSize(const std::string& filename) const {
        std::ifstream in(filename, std::ios::binary | std::ios::ate);
        return in ? static_cast<size_t>(in.tellg()) : 0;
    }
};

#endif
