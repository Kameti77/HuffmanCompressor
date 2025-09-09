#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "Node.h"
#include <array>
#include <map>
#include <queue>
#include <string>

class HuffmanTree {
private:
    Node* root;
    std::map<unsigned char, std::string> codes;

    void generateCodesRecursive(Node* node, const std::string& prefix);

public:
    HuffmanTree();
    ~HuffmanTree();

    Node* buildTree(const std::array<size_t, 256>& freqs);
    void generateCodes(Node* root);
    std::map<unsigned char, std::string> getCodes() const;

    void freeTree(Node* node);
};

#endif
