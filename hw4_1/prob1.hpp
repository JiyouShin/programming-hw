// prob1.hpp
#ifndef PROB1_HPP
#define PROB1_HPP

#include <climits> // For INT_MIN and INT_MAX

struct Node {
    int key;
    bool isRed;
    Node* left;
    Node* right;
    Node* parent;
};

bool validateRedBlackTree(Node* root);

#endif // PROB1_HPP
