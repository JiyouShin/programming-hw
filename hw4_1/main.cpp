#include "prob1.hpp"
#include <iostream>

using namespace std;

int main() {
    
    Node* root = new Node{5, false, nullptr, nullptr, nullptr};
    if ( validateRedBlackTree(root)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    delete root;

    return 0;
}
