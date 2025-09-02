#ifndef HUFFMANCOMPRESSOR_H
#define HUFFMANCOMPRESSOR_H

#include "../include/ICompressor.h"
#include "../include/HuffmanTree.h"
#include <unordered_map>
#include <string>
#include <map> 

class HuffmanCompressor : public ICompressor {
public:
    HuffmanCompressor() = default;
    ~HuffmanCompressor() override = default;

    void compress(const std::string& inputFile, const std::string& outputFile) override;
    void decompress(const std::string& inputFile, const std::string& outputFile) override;

    std::map<unsigned char, int> getFrequencyTable() const;
private:
    void buildFrequencyTable(const std::string& inputFile);
};

#endif

