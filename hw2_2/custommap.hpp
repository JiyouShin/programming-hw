#include <iostream>
#include <string>
#include <functional>

using namespace std;

// Fill in the empty templates and implement the definition of the class and each member functions
// TODO
template <typename K, typename V>
class TreeNode {
    private:
        K key;
        V value;
        TreeNode<K, V>* left;
        TreeNode<K, V>* right;
    
    public:
        TreeNode(K k, V v):
        key(k), value(v), left(nullptr), right(nullptr) {};

        ~TreeNode() {};

        K& getKey() {
            return key;
        }

        V& getValue() {
            return value;
        }

        TreeNode<K, V>*& getLeftTreeNode() {
            return left;
        }

        TreeNode<K, V>*& getRightTreeNode() {
            return right;
        }

        void setKey(K& k) {
            key = k;
        }

        void setValue(V& v) {
            value = v;
        }

        void setRightTreeNode(TreeNode* rtn) {
            right = rtn;
        }

        void setLeftTreeNode(TreeNode* ltn) {
            left = ltn;
        }

};

// Fill in the empty templates and implement the definition of the class and each member functions
// TODO
template <typename K, typename V, typename Compare = less<K> >
class CustomMap {
    private:
        TreeNode<K, V>* root;
        Compare comp;

    public:
        CustomMap():
        root() {};

        ~CustomMap(){};

        const TreeNode<K, V>* get_root() const {
            return root;
        }

        const Compare get_compare() const {
            return comp;
        }

        TreeNode<K, V>* insertNode(TreeNode<K, V>*& tn, K key, V value) {
            TreeNode<K, V>* current = tn;
            if (tn) {
                if (comp(key, tn->getKey())) {
                    current = insertNode(tn->getLeftTreeNode(), key, value);
                } else if (comp(tn->getKey(), key)) {
                    current = insertNode(tn->getRightTreeNode(), key, value);
                } else {
                    return current;
                }
            } else {
                tn = new TreeNode<K, V>(key, value);
                return tn;
            }
            return current;
        }

        TreeNode<K, V>* insert(K key, V value) {
            return insertNode(root, key, value);
        }

        void inOrderPrint(TreeNode<K, V>* tn) {
            if (tn == nullptr) {return;}
            inOrderPrint(tn->getLeftTreeNode());
            cout << tn->getKey() << ":" << tn->getValue() << endl; 
            inOrderPrint(tn->getRightTreeNode());
        }

        void print_map() {
            inOrderPrint(root);
        }

        void deleteKey(K key) {
            TreeNode<K, V>* parentNode = nullptr;
            TreeNode<K, V>* matchNode = root;
            bool isLeft;

            while (matchNode && matchNode->getKey() != key) {
                parentNode = matchNode;
                if (comp(key, matchNode->getKey())) {
                    matchNode = matchNode->getLeftTreeNode();
                    isLeft = true;
                } else {
                    matchNode = matchNode->getRightTreeNode();
                    isLeft = false;
                } 
            }
            
            if (!matchNode) {
                return;
            }

            if (matchNode) {
                if (matchNode->getLeftTreeNode() && matchNode->getRightTreeNode()) {
                    TreeNode<K, V>* successor = matchNode->getRightTreeNode();
                    TreeNode<K, V>* successorParent = matchNode;
                    bool isSuccessorLeft = false;
                    while (successor && successor->getLeftTreeNode()) {
                        successorParent = successor;
                        successor = successor->getLeftTreeNode();
                        isSuccessorLeft = true;
                    }
                    matchNode->setKey(successor->getKey());
                    matchNode->setValue(successor->getValue());

                    delete successor;
                    if (isSuccessorLeft) {
                        successorParent->setLeftTreeNode(nullptr);
                    } else {
                        successorParent->setRightTreeNode(nullptr);
                    }
                    
                } else if (matchNode->getLeftTreeNode()){
                    TreeNode<K, V>* temp = matchNode->getLeftTreeNode();
                    matchNode = temp;
                    temp = nullptr;
                    if (parentNode) {
                        if (isLeft) {
                            parentNode->setLeftTreeNode(matchNode);
                        } else {
                            parentNode->setRightTreeNode(matchNode);
                        }
                    } else {
                        root = matchNode;
                    }
                    
                } else if (matchNode->getRightTreeNode()){
                    TreeNode<K, V>* temp = matchNode->getRightTreeNode();
                    matchNode = temp;
                    temp = nullptr;
                    if (parentNode) {
                        if (isLeft) {
                            parentNode->setLeftTreeNode(matchNode);
                        } else {
                            parentNode->setRightTreeNode(matchNode);
                        }
                    } else {
                        root = matchNode;
                    }
                } else {
                    if (parentNode) {
                        if (isLeft) {
                            parentNode->setLeftTreeNode(nullptr);
                        } else {
                            parentNode->setRightTreeNode(nullptr);
                        }
                    }
                    delete matchNode;
                }
            }
        }

        V get_value(K key) {
            TreeNode<K, V>* matchNode = root;
            while (matchNode && matchNode->getKey() != key) {
                if (comp(key, matchNode->getKey())) {
                    matchNode = matchNode->getLeftTreeNode();
                } else {
                    matchNode = matchNode->getRightTreeNode();
                }
            }

            if (!matchNode) {
                return V();
            }
            return matchNode->getValue();
        }

        V& operator[](const K& key) {
            TreeNode<K, V>* matchNode = root;
            while (matchNode && matchNode->getKey() != key) {
                if (comp(key, matchNode->getKey())) {
                    matchNode = matchNode->getLeftTreeNode();
                } else {
                    matchNode = matchNode->getRightTreeNode();
                }
            }
            if (!matchNode) {
                TreeNode<K, V>* newNode = insert(key, V());
               return newNode->getValue();
            }
            return matchNode->getValue();
        }
};
