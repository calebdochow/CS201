#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

template <typename T>
class Tree24 {
private:
    struct Node {
        vector<T> keys;
        vector<Node*> children;
        bool leaf;
        
        Node(bool isLeaf = false) : leaf(isLeaf) {}
    };

    Node* root;


public:
    Tree24() : root(nullptr) {}

    ~Tree24() {
    }

};