#ifndef HUFFMANCOMPRESSOR_H
#define HUFFMANCOMPRESSOR_H

#include "ICompressor.h"
#include "HuffmanTree.h"
#include <unordered_map>
#include <string>
#include <map>
#include <array>

// Node struct for Huffman tree
struct HuffNode {
    unsigned char value;      // The byte value (0–255)
    size_t freq;             // Frequency of the byte
    HuffNode* left;
    HuffNode* right;
    HuffNode* parent;


    HuffNode(short _value, unsigned int _freq, HuffNode* _left = nullptr, HuffNode* _right = nullptr, HuffNode* _parent = nullptr)
        : value(_value), freq(_freq), left(_left), right(_right), parent(_parent) {
    }

    HuffNode(const HuffNode& _hnode)
        : value(_hnode.value), freq(_hnode.freq), left(_hnode.left), right(_hnode.right), parent(_hnode.parent) {
    }
};

// Comparator for priority_queue 
struct CompareNode {
    bool operator()(HuffNode* a, HuffNode* b) {
        return a->freq > b->freq;
    }
};



class HuffmanCompressor : public ICompressor {
public:
    HuffmanCompressor() = default;
    ~HuffmanCompressor() override = default;

    void compress(const std::string& inputFile, const std::string& outputFile) override;
    void decompress(const std::string& inputFile, const std::string& outputFile) override;

    std::array<size_t, 256> getFrequencyTable() const;
    void buildFrequencyTable(const std::string& inputFile);



    HuffNode* GenerateTree(const std::array<size_t, 256>& frequencies);
    void FreeTree(HuffNode* root);

    void GenerateCodes(HuffNode* root);

    // For testing
    void PrintFirstCodes(int n = 10);

    // Append the codes to a growing string of '0' and '1'.
    std::string encodeFile(const std::string& filename);

private:
    //std::map<unsigned char, int> 
    // std::array<std::size_t, 256> mFrequencyTable{};
    std::array<std::size_t, 256> mFrequencyTable{};

    std::vector<HuffNode*> mLeafList;
    HuffNode* mRoot = reinterpret_cast<HuffNode*>(-1);
    std::map<unsigned char, std::string> mCodes;

    void GenerateCodesRecursive(HuffNode* node, const std::string& prefix);
};

#endif
