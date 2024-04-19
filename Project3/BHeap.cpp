template <typename KeyType>
class BHeap {
private:
    class Node {
    public:
        KeyType key;
        Node* parent;
        Node* child;
        Node* prev; // Pointer to the previous sibling
        Node* next; // Pointer to the next sibling
        Node* sibling;

        Node(const KeyType& k);
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
BHeap<KeyType>::Node::Node(const KeyType& k) : key(k), parent(nullptr), child(nullptr), prev(nullptr), next(nullptr), sibling(nullptr) {}

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
    Node* current = rootList;
    while (current != nullptr) {
        Node* next = current->next; // Store the next node using next pointer
        delete current; // Delete the current node
        if (next == rootList) break; // Exit if we have traversed the entire list
        current = next; // Move to the next node
    }
    rootList = nullptr; // Ensure rootList is set to nullptr after deletion
    minNode = nullptr; // Ensure minNode is set to nullptr after deletion
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
    
    KeyType minKey = minNode->key; // Save the minimum key
    
    // Remove the minimum node from the root list
    if (minNode == minNode->next) { // Only one node in the heap
        delete minNode;
        minNode = nullptr;
        rootList = nullptr;
    } else {
        Node* minNext = minNode->next;
        Node* minPrev = minNode->prev;
        
        minPrev->next = minNext;
        minNext->prev = minPrev;
        
        // Adjust the minNode if it's the one we're removing
        if (minNode == rootList) {
            rootList = minNext;
        }
        
        delete minNode;
        minNode = nullptr;
    }
    
    // Merge the children of the removed node with the root list
    Node* child = rootList->child;
    while (child != nullptr) {
        Node* nextSibling = child->next;
        child->prev = rootList->prev;
        child->next = rootList;
        rootList->prev->next = child;
        rootList->prev = child;
        child->parent = nullptr;
        child = nextSibling;
    }
    
    // Consolidate the heap
    consolidate();
    
    return minKey;
}

template <typename KeyType>
void BHeap<KeyType>::insert(const KeyType& k) {
    Node* newNode = new Node(k);
    if (rootList == nullptr) {
        rootList = newNode;
        newNode->prev = newNode; // Circular list, so point to itself
        newNode->next = newNode; // Circular list, so point to itself
        newNode->parent = nullptr;
        newNode->child = nullptr;
        minNode = newNode;
    } else {
        newNode->next = minNode;
        newNode->prev = minNode->prev;
        minNode->prev->next = newNode;
        minNode->prev = newNode;

        newNode->parent = nullptr;

        if (k < minNode->key) {
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

    Node* current = minNode;
    Node* start = minNode; // Store the starting point to detect circularity

    do {
        int degree = 0;
        Node* child = current->child;

        // Print the degree of the current tree
        cout << "B" << degree << ": ";

        // Print the keys of the current tree
        cout << current->key;

        while (child != nullptr) {
            cout << " " << child->key;
            child = child->next;
        }

        cout << endl;

        // Move to the next tree
        current = current->next;
    } while (current != start);
}

template <typename KeyType>
void BHeap<KeyType>::consolidate() {
    if (isEmpty()) {
        return;
    }

    // Find the maximum degree possible
    int maxDegree = 0;
    Node* temp = rootList;
    do {
        maxDegree++;
        temp = temp->next;
    } while (temp != rootList);

    // Initialize an array to hold roots of trees with the same degree
    Node** rootArray = new Node*[maxDegree + 1];
    for (int i = 0; i <= maxDegree; ++i) {
        rootArray[i] = nullptr;
    }

    // Traverse the root list and merge trees with the same degree
    Node* current = rootList;
    while (current != nullptr) {
        Node* nextNode = current->next;
        int degree = 0;
        Node* temp = current;
        while (rootArray[degree] != nullptr) {
            Node* other = rootArray[degree];
            if (current->key > other->key) {
                swap(current, other);
            }
            // Link the other tree as a child of the current node
            other->prev->next = other->next;
            other->next->prev = other->prev;
            other->next = current->child;
            other->prev = current->child->prev;
            current->child->prev->next = other;
            current->child->prev = other;
            other->parent = current;
            other->prev->parent = current;
            other->next->parent = current;
            other->sibling = nullptr;
            rootArray[degree] = nullptr; // Clear the slot in the array after merging
            degree++;
        }
        rootArray[degree] = current;
        current = nextNode;
    }

    // Reconstruct the root list from the rootArray
    minNode = nullptr;
    rootList = nullptr;
    for (int i = 0; i <= maxDegree; ++i) {
        if (rootArray[i] != nullptr) {
            if (minNode == nullptr || rootArray[i]->key < minNode->key) {
                minNode = rootArray[i];
            }
            if (rootList == nullptr) {
                rootList = rootArray[i];
                rootList->prev = rootList;
                rootList->next = rootList;
            } else {
                rootArray[i]->prev = rootList->prev;
                rootArray[i]->next = rootList;
                rootList->prev->next = rootArray[i];
                rootList->prev = rootArray[i];
            }
        }
    }

    delete[] rootArray;
}