#include <iostream>

using namespace std;

template <typename KeyType>
class BHeap {
private:
    class Node {
    public:
        KeyType key;
        Node* parent;
        Node* child;
        Node* prev;
        Node* next;

        Node(const KeyType& k) : key(k), parent(nullptr), child(nullptr) {}
    };

    Node* minNode; // Pointer to the minimum element in the heap
    Node* rootList; // Circular doubly linked list of tree roots

    void consolidate();

public:
    BHeap();
    BHeap(KeyType k[], int s); // Constructor from array
    ~BHeap();

    KeyType peekKey() const;
    KeyType extractMin();
    void insert(const KeyType& k);
    void merge(BHeap<KeyType>& H2);
    void printKey() const;
    bool isEmpty() const;

};

template <typename KeyType>
BHeap<KeyType>::BHeap() : minNode(nullptr), rootList(nullptr) {}

template <typename KeyType>
BHeap<KeyType>::BHeap(KeyType k[], int s) : minNode(nullptr), rootList(nullptr) {
    for (int i = 0; i < s; ++i) {
        insert(k[i]);
    }
    consolidate();
}

template <typename KeyType>
BHeap<KeyType>::~BHeap() {
    // Free memory for nodes
    while (rootList != nullptr) {
        Node* next = rootList->sibling;
        delete rootList;
        rootList = next;
        if (rootList == minNode) break; // Avoid infinite loop
    }
}

template <typename KeyType>
bool BHeap<KeyType>::isEmpty() const {
    return minNode == nullptr;
}

template <typename KeyType>
KeyType BHeap<KeyType>::peekKey() const {
    if (isEmpty()) {
        throw runtime_error("Heap is empty");
    }
    return minNode->key;
}

template <typename KeyType>
KeyType BHeap<KeyType>::extractMin() {
    if (isEmpty()) {
        throw runtime_error("Heap is empty");
    }
    KeyType minKey = minNode->key;
    // Extract min logic
    return minKey;
}

template <typename KeyType>
void BHeap<KeyType>::insert(const KeyType& k) {
    Node* newNode = new Node(k);
    if (rootList == nullptr) {
        rootList = newNode;
        newNode->prev = newNode;
        newNode->next = newNode;
        newNode->parent = nullptr;
        newNode->child = nullptr;
    } else {
        newNode->next = rootList;
        newNode->prev = rootList->prev;
        rootList->prev->next = newNode;
        rootList->prev = newNode;
        newNode->parent = nullptr;
        if (minNode == nullptr || k < minNode->key) {
            minNode = newNode;
        }
    }
}

template <typename KeyType>
void BHeap<KeyType>::merge(BHeap<KeyType>& H2) {
    // Merge logic
}

template <typename KeyType>
void BHeap<KeyType>::printKey() const {
    if (isEmpty()) {
        cout << "Heap is empty" << endl;
        return;
    }

    cout << "Min Heap: " << endl;
    Node* current = minNode;
    while (true) {
        cout << "KEY: " << current->key << endl;
        Node* child = current->child;
        if (child != nullptr) {
            cout << "(";
            while (child != nullptr) {
                cout << child->key << " ";
                child = child->sibling;
            }
            cout << ")";
        }
        cout << endl;

        // Move to the next node in the root list
        current = current->sibling;
        // If we have iterated through all nodes in the root list, exit the loop
        if (current == minNode) {
            break;
        }
    }

    cout << endl;
}

template <typename KeyType>
void BHeap<KeyType>::consolidate() {
    // Consolidate logic
}

