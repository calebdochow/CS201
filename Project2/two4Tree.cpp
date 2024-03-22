#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<typename KeyType, typename ValueType>
class Node {
public:
    vector<KeyType> keys;
    vector<ValueType> values;
    vector<Node*> children;
    Node* parent;

    Node(){
        
    }
    // Constructor
    Node(KeyType key, ValueType value, Node* parent = nullptr) {
        keys.push_back(key);
        values.push_back(value);
        this->parent = parent;
    }

    // Insert key-value pair into the node
    void insert(KeyType key, ValueType value) {
        keys.push_back(key);
        values.push_back(value);
        sort(keys.begin(), keys.end());
    }

    // Check if node is full
    bool isFull() {
        return keys.size() == 3;
    }

    // Split the node
    Node* split() {
        Node* new_node = new Node(keys[2], values[2], parent);
        
        // Check if the current node is a leaf
        if (!isLeaf()) {
            new_node->children.push_back(children[2]);
            new_node->children.push_back(children[3]);

            if (children[2])
                children[2]->parent = new_node;
            if (children[3])
                children[3]->parent = new_node;

            children.erase(children.begin() + 2, children.end());
        }
        
        keys.pop_back();
        keys.pop_back();
        values.pop_back();
        values.pop_back();
        return new_node;
    }

    // Check if the node is a leaf
    bool isLeaf() {
        return children.empty();
    }

    // Find the appropriate child for the given key
    // Find the appropriate child for the given key
    Node* getChild(KeyType key) {
        int num_keys = keys.size();
        int index = 0;
        while (index < num_keys && key > keys[index]) {
            index++;
        }

        if (isLeaf() || index >= children.size()) {
            return nullptr;
        }
        return children[index];
    }


};

template<typename KeyType, typename ValueType>
class Two4Tree {
public:
    Node<KeyType, ValueType>* root;

    // Constructor
    Two4Tree(KeyType keys[], ValueType values[], int size) {
        root = nullptr;
        for (int i = 0; i < size; ++i) {
            insert(keys[i], values[i]);
        }
    }

    // Insert a key-value pair into the tree
    void insert(KeyType key, ValueType value) {
        if (!root) {
            root = new Node<KeyType, ValueType>(key, value);
            return;
        }

        Node<KeyType, ValueType>* current = root;
        while (!current->isLeaf()) {
            current = current->getChild(key);
        }

        current->insert(key, value);
        while (current->isFull()) {
            if (current == root) {
                root = new Node<KeyType, ValueType>(current->keys[1], current->values[1]);
                root->children.push_back(current);
                root->children.push_back(current->split());
                current->parent = root;
                root->children[1]->parent = root;
                return;
            } else {
                Node<KeyType, ValueType>* parent = current->parent;
                parent->insert(current->keys[1], current->values[1]);
                int index = find(parent->keys.begin(), parent->keys.end(), current->keys[1]) - parent->keys.begin();
                parent->children.insert(parent->children.begin() + index + 1, current->split());
                current = parent;
            }
        }
    }


};

