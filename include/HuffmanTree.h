#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include "Node.h"
#include <unordered_map>
#include <string>
#include <memory>

class HuffmanTree {
public:
    HuffmanTree();
    ~HuffmanTree();

    // Build tree from frequency map
    void build(const std::unordered_map<char, int>& freqMap);

    // Generate codes from tree
    std::unordered_map<char, std::string> getCodes() const;

    // Get root node
    std::shared_ptr<Node> getRoot() const;

private:
    std::shared_ptr<Node> root;

    void generateCodes(std::shared_ptr<Node> node, const std::string& prefix,
                       std::unordered_map<char, std::string>& codeMap) const;
};

#endif
