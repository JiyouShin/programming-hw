#include <iostream>
#include <stack>
#include "prob1.hpp"

using namespace std;

bool validateRedBlackTree(Node* root) {
    if (!root) {
        return true;
    }

    if (root->isRed) {
        return false;
    }

    stack<pair<Node*, int> > nodeStack;
    nodeStack.push({root, 1});

    int expectedBlackHeight = -1;

    while (!nodeStack.empty()) {
        Node* currNode = nodeStack.top().first;
        int currBlackHeight = nodeStack.top().second;
        nodeStack.pop();

        if (!currNode) {
            if (expectedBlackHeight == -1) {
                expectedBlackHeight = currBlackHeight;
            } else if (expectedBlackHeight != currBlackHeight) {
                return false;
            }
            continue;
        }

        if (currNode->isRed && currNode->parent && currNode->parent->isRed) {
            return false;
        }

        if (currNode->left && currNode->left->key > currNode->key) {
            return false;
        }
        if (currNode->right && currNode->right->key < currNode->key) {
            return false;
        }

        if (!currNode->isRed) {
            currBlackHeight++;
        }

        nodeStack.push({currNode->left, currBlackHeight});
        nodeStack.push({currNode->right, currBlackHeight});

    }

    return true;
}
