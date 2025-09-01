#ifndef NODE_H
#define NODE_H

#include <memory>

struct Node {
    char ch;
    int freq;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(char c, int f);
    Node(std::shared_ptr<Node> l, std::shared_ptr<Node> r);

    // Utility: check if node is leaf
    bool isLeaf() const;
};

#endif
