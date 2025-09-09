#include "../include/HuffmanTree.h"
#include <iostream>

HuffmanTree::HuffmanTree() : root(nullptr) {}

HuffmanTree::~HuffmanTree() {
    freeTree(root);
}

Node* HuffmanTree::buildTree(const std::array<size_t, 256>& freqs) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> pq;

    // Create leaf nodes
    for (int i = 0; i < 256; i++) {
        if (freqs[i] > 0) {
            pq.push(new Node((unsigned char)i, freqs[i]));
        }
    }

    if (pq.empty()) return nullptr;

    // Merge nodes
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* parent = new Node(0, left->freq + right->freq, left, right);
        pq.push(parent);
    }

    root = pq.top();
    return root;
}

void HuffmanTree::generateCodesRecursive(Node* node, const std::string& prefix) {
    if (!node) return;

    // Leaf
    if (!node->left && !node->right) {
        codes[node->value] = prefix;
        return;
    }

    generateCodesRecursive(node->left, prefix + "0");
    generateCodesRecursive(node->right, prefix + "1");
}

void HuffmanTree::generateCodes(Node* r) {
    codes.clear();
    generateCodesRecursive(r, "");
}

std::map<unsigned char, std::string> HuffmanTree::getCodes() const {
    return codes;
}

void HuffmanTree::freeTree(Node* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    delete node;
}
