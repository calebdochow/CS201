#include <iostream>
#include <cmath>
using namespace std;

template <typename KeyType>
class Node {
public:
    KeyType key;
    Node *parent;
    Node* child;
    Node* prev;
    Node* next;
    int degree;

    Node(KeyType k) : key(k), parent(nullptr), child(nullptr), prev(nullptr), next(nullptr), degree(0) {}
};

template <typename KeyType>
class BHeap {
private:
    Node<KeyType>* minNode; //minimum element in the heap
    Node<KeyType>* rootList; // CDLL of tree roots
    int size;

    void consolidate();
    Node<KeyType>* copy(Node<KeyType>* node, Node<KeyType>* p);

public:
    BHeap();
    BHeap(KeyType k[], int s); 
    ~BHeap();
    BHeap(const BHeap<KeyType>& other); // Copy constructor
    BHeap<KeyType>& operator=(const BHeap<KeyType>& other); // Copy assignment operator

    KeyType peekKey() const;
    KeyType extractMin();
    void insert(const KeyType& k);
    void merge(BHeap<KeyType>& H2);
    void printKey() const;
    void printKey(Node<KeyType> * node) const;
    bool isEmpty() const;
    void linkNodes(Node<KeyType>* other, Node<KeyType>* current);
};

template <typename KeyType>
BHeap<KeyType>::BHeap() : minNode(nullptr), rootList(nullptr), size(0) {}

template <typename KeyType>
BHeap<KeyType>::BHeap(KeyType k[], int s) : minNode(nullptr), rootList(nullptr), size(0) {
    for (int i = 0; i < s; i++) {
        insert(k[i]);
    }
    consolidate();
}

template <typename KeyType>
BHeap<KeyType>::~BHeap() {

    Node<KeyType>* current = rootList;
    
    while (current != nullptr) {
        Node<KeyType>* next = current->next; 
        delete current; 
        if (next == rootList) break; 
        current = next; 
    }

    rootList = nullptr; 
    minNode = nullptr; 
}

template <typename KeyType>
bool BHeap<KeyType>::isEmpty() const {
    return minNode == nullptr;
}

template <typename KeyType>
KeyType BHeap<KeyType>::peekKey() const {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    return minNode->key;
}

template <typename KeyType>
KeyType BHeap<KeyType>::extractMin() {
    if (isEmpty()) {
        throw std::runtime_error("Heap is empty");
    }
    Node<KeyType>* x = minNode;

    if(x != nullptr){
        if(x->child != nullptr){
            Node<KeyType>* child = x->child;
            Node<KeyType>* nextChild = nullptr;
            minNode = child;

            while(child != nullptr){
                nextChild = child->next;
                child->prev = x->prev;
                child->next = x;
                x->prev->next = child;
                x->prev = child;
                child->parent = nullptr;
                child = nextChild;
            }
        }else if(x == x->next){
            minNode = nullptr;
        }else{
            minNode = x->next;
        }

        x->prev->next = x->next;
        x->next->prev = x->prev;

        consolidate();
        size--;
    }
    KeyType key = x->key;
    delete x;
    return key;
}

template <typename KeyType>
void BHeap<KeyType>::insert(const KeyType& k) {
    Node<KeyType>* newNode = new Node<KeyType>(k);
    if (minNode == nullptr) {
        minNode = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
        
    } else {
        newNode->prev = minNode->prev;
        newNode->next = minNode;
        minNode->prev->next = newNode;
        minNode->prev = newNode;

        if (newNode->key < minNode->key) {
            minNode = newNode;
        }
    }
    size++;
}

template <typename KeyType>
void BHeap<KeyType>::merge(BHeap<KeyType>& H2) {
    Node<KeyType>* otherMin = H2.minNode;
    Node<KeyType>* minPrev = minNode->prev;
    Node<KeyType>* otherMinPrev = H2.minNode->prev;

    otherMin->prev = minPrev;
    minPrev->next = otherMin;
    minNode->prev = otherMinPrev;
    otherMinPrev->next = minNode;

    if (minNode == nullptr || (H2.minNode != nullptr && H2.minNode->key < minNode->key)) {
        minNode = H2.minNode;
    }

    size += H2.size;
    H2.minNode = nullptr;
    H2.size = 0;
}

template <typename KeyType>
void BHeap<KeyType>::printKey() const {
    if (isEmpty()) {
        cout << "Heap is empty" << endl;
        return;
    }

    Node<KeyType>* current = minNode;

    while(current != nullptr){
        Node<KeyType> *nextNode = current->next;
        cout << "B" << current->degree << ":" << endl;
        printTree(current);
        cout << endl;
        current = nextNode;

        if (current == minNode) break;
    }
}

template <typename KeyType>
void printTree(Node<KeyType> *node) {
    cout << node->key << " ";

    Node<KeyType> *child = node->child;

    while (child != nullptr) {
        Node<KeyType> *nextChild = child->next;
        printTree(child);
        child = nextChild;
    }
}

template <typename KeyType>
void BHeap<KeyType>::consolidate() {
    if (isEmpty()) {
        return;
    }

    int maxDegree = (int)(log2(size)) + 1;
    
    Node<KeyType>* rootArray[maxDegree];
    for (int i = 0; i < maxDegree; i++) {
        rootArray[i] = nullptr;
    }


    Node<KeyType>* current = minNode;

    do {
        Node<KeyType>* nextNode = current->next;
        int degree = current->degree;
        while (rootArray[degree] != nullptr) {
            Node<KeyType>* other = rootArray[degree];
            if (current->key > other->key) {
                swap(current, other);
            }
            
            linkNodes(other, current);
            rootArray[degree] = nullptr; 
            degree++;
        }
        rootArray[degree] = current;
        current = nextNode;
    } while(current != minNode);

    minNode = nullptr;
    
    for (int i = 0; i < maxDegree; i++) {
        if (rootArray[i] != nullptr) {
            if (minNode == nullptr) {
                rootArray[i]->next = rootArray[i];
                rootArray[i]->prev = rootArray[i];
                minNode = rootArray[i];
            }else{
                rootArray[i]->prev = minNode->prev;
                rootArray[i]->next = minNode;
                minNode->prev->next = rootArray[i];
                minNode->prev = rootArray[i];
                
                if(rootArray[i]->key < minNode->key){
                    minNode = rootArray[i];
                }
            } 
        }
    }
}

template <typename KeyType>
void BHeap<KeyType>::linkNodes(Node<KeyType>* other, Node<KeyType>* current) {
    other->next->prev = other->prev;
    other->prev->next = other->next;

    other->next = nullptr;
    other->prev = nullptr;

    if (current->child != nullptr) {
        Node<KeyType>* child = current->child;

        while (child->next != nullptr) {
            child = child->next;
        }

        child->next = other;
        other->prev = child;
    }
    else {
        current->child = other;
    }

    other->parent = current;
    current->degree++;
}

template <typename KeyType>
Node<KeyType>* BHeap<KeyType>::copy(Node<KeyType>* node, Node<KeyType>* p) {
    if (!node) {
        return nullptr;
    }

    Node<KeyType>* newNode = new Node<KeyType>(node->key);
    newNode->degree = node->degree;
    newNode->parent = p;

    Node<KeyType>* child = node->child;
    Node<KeyType>* copyChild = newNode->child;

    while (child != nullptr) {
        Node<KeyType>* x = copy(child, newNode);

        if (copyChild == nullptr) {
            copyChild = x;
            newNode->child = x;
        } else {
            while (copyChild->next != nullptr) {
                copyChild = copyChild->next;
            }

            copyChild->next = x;
        }

        child = child->next;
    }

    return newNode;
}