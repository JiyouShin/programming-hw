#include <iostream> 
#include <climits> 
#include <queue>
#include <cmath>
#include <stack>

#include "functions.hpp"

using namespace std; 

MaxHeap::MaxHeap(){
    root = nullptr;
    last_node = nullptr;
    heapsize = 0;   
}  

Node * MaxHeap::getMax(){
    return root;
}

void MaxHeap::printHeap(){
    Node * currNode = root;
    queue<Node*> q;

    q.push(root);
    std::cout << "Print Heap: ";
    while (!q.empty() && q.front()){
        std::cout << q.front()->val << " ";
        if (q.front()->left){
            q.push(q.front()->left);
        }

        if (q.front()->right){
            q.push(q.front()->right);
        }

        q.pop();
    }
    std::cout << std::endl;
}

void MaxHeap::swap(Node * a, Node * b){
    int temp = a->val;
    a->val = b->val;
    b->val = temp;
}

// Inserts a new key 'k' 
void MaxHeap::enqueue(int k) 
{ 
    Node* newNode = new Node();
    newNode->val = k;

    if (!root) {
        root = newNode;
        last_node = newNode;
        heapsize++;
        return;
    }
    heapsize++;

    Node* parent = root;
    int path = heapsize;
    int level = (int)log2(path);
    for (int i = level - 1; i > 0; --i) {
        if (path & (1 << i)) {
            parent = parent->right;
        } else {
            parent = parent->left;
        }
    }

    if (path & 1) {
        parent->right = newNode;
    } else {
        parent->left = newNode;
    }
    newNode->parent = parent;
    last_node = newNode;

    // stack<int> binaryStack;
    // int lastNodeIdx = heapsize + 1;

    // while (lastNodeIdx > 0) {
    //     binaryStack.push(lastNodeIdx % 2);
    //     lastNodeIdx /= 2;
    // }
    // binaryStack.pop();

    // Node* targetNode = root;
    // while (binaryStack.size() > 1) {
    //     int direction = binaryStack.top();
    //     binaryStack.pop();
    //     if (direction == 0) {
    //         targetNode = targetNode->left;
    //     } else {
    //         targetNode = targetNode->right;
    //     }
    // }

    // if (binaryStack.top() == 0) {
    //     targetNode->left = newNode;
    // } else {
    //     targetNode->right = newNode;
    // }
    // newNode->parent = targetNode;

    // last_node = newNode;

    Node* currNode = newNode;
    while (currNode->parent && currNode->val > currNode->parent->val) {
        swap(currNode, currNode->parent);
        currNode = currNode->parent;
    }
    
} 

// Removes the root node and heapify
void MaxHeap::dequeue(){
    if (!root) return;
    if (root->left == nullptr && root->right == nullptr) {
        delete root;
        root = nullptr;
        last_node = nullptr;
        heapsize = 0;
        return;
    }

    swap(root, last_node);

    Node* parent = root;
    int path = heapsize;
    int level = (int)log2(path);
    for (int i = level - 1; i > 0; --i) {
        if (path & (1 << i)) {
            parent = parent->right;
        } else {
            parent = parent->left;
        }
    }

    if (path & 1) {
        delete parent->right;
        parent->right = nullptr;
    } else {
        delete parent->left;
        parent->left = nullptr;
    }
    last_node = parent;
    heapsize--;
    
    // Node* lastParent = last_node->parent;
    // if (last_node->parent) {
    //     if (last_node->parent->left == last_node) {
    //         last_node->parent->left = nullptr;
    //     } else {
    //         last_node->parent->right = nullptr;
    //     }
    // } else {
    //     root = nullptr;
    // }
    // last_node = nullptr;
    // heapsize--;

    Node* new_last_node = root;
    int new_path = heapsize;
    level = (int)log2(new_path);
    for (int i = level - 1; i >= 0; --i) {
        if (new_path & (1 << i)) {
            new_last_node = new_last_node->right;
        } else {
            new_last_node = new_last_node->left;
        }
    }
    last_node = new_last_node;

    Node* curr_node = root;
    while (curr_node) {
        Node* max_node = curr_node;
        if (curr_node->left && curr_node->left->val > max_node->val) {
            max_node = curr_node->left;
        }
        if (curr_node->right && curr_node->right->val > max_node->val) {
            max_node = curr_node->right;
        }
        if (max_node == curr_node) {
            break;
        }

        swap(curr_node, max_node);
        curr_node = max_node;
    }

}
