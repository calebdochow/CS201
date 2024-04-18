#include <iostream>
using namespace std;

template <typename keytype>
class Heap{
    public:
};

template <typename keytype>
class Node {
    public:
        keytype key;
        Node *prev;
        Node* next;

        Node() { //Constructor
            key = NULL;
            prev = nullptr;
            next = nullptr;
        }

        Node(keytype k[], int s) { //Constructor
            
        }
};