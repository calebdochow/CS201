#include <iostream>
#include <cmath>
using namespace std;

template <typename K>
class Node {
    public:
        K key;
        int degree;
        Node *child;
        Node *parent;
        Node *next;
        Node *prev;

        Node() {
            child = nullptr;
            parent = nullptr;
            next = nullptr;
            prev = nullptr;
        }

        Node(K key) {
            this->key = key;
            degree = 0;
            child = nullptr;
            parent = nullptr;
            next = nullptr;
            prev = nullptr;
        }
};

template <typename keytype>
class BHeap {
    public:
        Node<keytype> *minimum;
        int size;

        BHeap() {
            minimum = nullptr;
            size = 0;
        }

        BHeap(keytype k[], int s) {
            minimum = nullptr;
            size = 0;

            for (int i = 0; i < s; i++) {
                insert(k[i]);
            }

            consolidate();
        }

        BHeap(const BHeap& other) {
            this->minimum = nullptr;

            Node<keytype> *cur = other.minimum;
            do  {
                Node<keytype> *next = cur->next;
                Node<keytype> *newNode = copy(cur, nullptr);

                if (minimum == nullptr) {
                    minimum = newNode;
                    newNode->next = newNode;
                    newNode->prev = newNode;
                } 
                else {
                    newNode->prev = minimum->prev;
                    newNode->next = minimum;
                    minimum->prev->next = newNode;
                    minimum->prev = newNode;
                }

                cur = next;
            } while (cur != other.minimum);
            
            this->size = other.size;
        }

        BHeap& operator=(const BHeap& other) {
            if (this != &other) {
                Node<keytype> *current = minimum;
                while (current != nullptr) {
                    Node<keytype> *next = current->next;
                    deleteNode(current);
                    current = next;

                    if (current == minimum) break;
                }

                this->minimum = nullptr;
                this->size = 0;
                
                Node<keytype> *cur = other.minimum;
                do  {   
                    Node<keytype> *next = cur->next;
                    Node<keytype> *newNode = copy(cur, nullptr);

                    if (minimum == nullptr) {
                        minimum = newNode;
                        newNode->next = newNode;
                        newNode->prev = newNode;
                    } 
                    else {
                        newNode->prev = minimum->prev;
                        newNode->next = minimum;
                        minimum->prev->next = newNode;
                        minimum->prev = newNode;
                    }

                    cur = next;
                    
                } while (cur != other.minimum);
                
                this->size = other.size;
            }
    
            return *this;
        }
        
        Node<keytype> *copy(Node<keytype>* node, Node<keytype>* p) {
            if (!node) {
                return nullptr;
            }

            Node<keytype> *newNode = new Node<keytype>(node->key);
            newNode->degree = node->degree;
            newNode->parent = p;
            
            Node<keytype> *child = node->child;
            Node<keytype> *copyChild = newNode->child;

            while (child != nullptr) {
                Node<keytype> *x = copy(child, newNode);

                if (copyChild == nullptr) {
                    copyChild = x;
                    newNode->child = x;
                }
                else {
                    while(copyChild->next != nullptr) {
                        copyChild = copyChild->next;
                    }

                    copyChild->next = x;
                }

                child = child->next;
            }

            return newNode;
        }

        ~BHeap() {
            Node<keytype> *cur = minimum;

            while (cur != nullptr) {
                Node<keytype> *next = cur->next;
                deleteNode(cur);
                cur = next;

                if (cur == minimum) break;
            }
        }

        void deleteNode(Node<keytype> *node) {
            if (!node) {
                return;
            }

            Node<keytype> *child = node->child;
            
            while (child != nullptr) {
                Node<keytype> *nextChild = child->next;
                deleteNode(child);
                child = nextChild;
            }

            delete node;
        }

        keytype peekKey() {
            return minimum->key;
        }

        keytype extractMin() {
            Node<keytype> *z = minimum;
            
            if (z != nullptr) {
                if (z->child != nullptr) {
                    Node<keytype> *child = z->child;
                    Node<keytype> *nextChild = nullptr;
                    minimum = child;
                    
                    while (child != nullptr) {
                        nextChild = child->next;

                        child->prev = z->prev;
                        child->next = z;
                        z->prev->next = child;
                        z->prev = child;
                        child->parent = nullptr;

                        child = nextChild;
                    } 
                    
                } 
                else if (z == z->next){
                    minimum = nullptr;
                } 
                else {
                    minimum = z->next;
                }
                
                z->prev->next = z->next;
                z->next->prev = z->prev;

                consolidate();
                size--;
            }

            keytype key = z->key;
            delete z;
            return key;
        }

        void insert(keytype k) {
            Node<keytype> *x = new Node<keytype>(k);

            if (minimum == nullptr) {
                minimum = x;
                x->next = x;
                x->prev = x;
            } 
            else {
                x->prev = minimum->prev;
                x->next = minimum;
                minimum->prev->next = x;
                minimum->prev = x;

                if (x->key < minimum->key) {
                    minimum = x;
                }
            }

            size++;
        }

        void merge(BHeap<keytype> &H2) {
            Node<keytype> *otherMin = H2.minimum;
            Node<keytype> *minPrev = minimum->prev;
            Node<keytype> *otherMinPrev = H2.minimum->prev;

            otherMin->prev = minPrev;
            minPrev->next = otherMin;

            minimum->prev = otherMinPrev;
            otherMinPrev->next = minimum;

            if (minimum == nullptr || (H2.minimum != nullptr && H2.minimum->key < minimum->key)) {
                minimum = H2.minimum;
            }

            size += H2.size;

            H2.minimum = nullptr;
            H2.size = 0;
        }

        void printKey() {
            Node<keytype> *cur = minimum;

            while (cur != nullptr) {
                Node<keytype> *next = cur->next;
                cout << "B" << cur->degree << ":" << endl;
                printTree(cur);
                cout << endl;
                cur = next;

                if (cur == minimum) break;
            }
        }

        void printTree(Node<keytype> *node) {
            cout << node->key << " ";

            Node<keytype> *child = node->child;

            while (child != nullptr) {
                Node<keytype> *nextChild = child->next;
                printTree(child);
                child = nextChild;
            }
        }

    private:
        void consolidate() {
            int maxDegree = (int)(log2(size)) + 1;
            cout << "MAX DEGREE: " << maxDegree << endl;
            Node<keytype> *array[maxDegree];

            for (int i = 0; i < maxDegree; i++) {
                array[i] = nullptr;
            }

            Node<keytype> *x = minimum;

            do {
                Node<keytype> *nextNode = x->next;
                int d = x->degree;

                while (array[d] != nullptr) {
                    Node<keytype> *y = array[d];
                    if (x->key > y->key) {
                        //swap
                        Node<keytype> *temp = x;
                        x = y;
                        y = temp;
                    }
                    link(y, x);
                    array[d] = nullptr;
                    d++;
                }

                array[d] = x;

                x = nextNode;
            } while (x != minimum);
            
            minimum = nullptr;

            for (int i = 0; i < maxDegree; i++) {
                if (array[i] != nullptr) {
                    if (minimum == nullptr) {
                        array[i]->next = array[i];
                        array[i]->prev = array[i];
                        minimum = array[i];
                    }
                    else {
                        array[i]->prev = minimum->prev;
                        array[i]->next = minimum;
                        minimum->prev->next = array[i];
                        minimum->prev = array[i];

                        if (array[i]->key < minimum->key) {
                            minimum = array[i];
                        }
                    }
                }
            }
        }

        void link(Node<keytype> *y, Node<keytype> *x) {

            y->next->prev = y->prev;
            y->prev->next = y->next;

            y->next = nullptr;
            y->prev = nullptr;

            if (x->child != nullptr) {
                Node<keytype> *child = x->child;

                while (child->next != nullptr) {
                    child = child->next;
                }

                child->next = y;
                y->prev = child;
            }
            else {
                x->child = y;
            }

            y->parent = x;
            x->degree++;
        }
};