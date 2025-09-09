#ifndef NODE_H
#define NODE_H

struct Node {
    unsigned char value;   // byte value
    size_t freq;           // frequency
    Node* left;
    Node* right;

    Node(unsigned char v, size_t f, Node* l = nullptr, Node* r = nullptr)
        : value(v), freq(f), left(l), right(r) {
    }
};

// Comparator for priority_queue
struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq; 
    }
};

#endif