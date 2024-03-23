#include <iostream>
#include "CircularDynamicArray.cpp"
using namespace std;

template <typename K, typename V>
class Element {
    public:
        K key;
        CircularDynamicArray<V> values;
        bool isEmpty = true;

        Element() {
            isEmpty = true;
        }

        void setKey(K k, V value) {
            isEmpty = false;
            key = k;
            values.addEnd(value);
        }

        void addValue (V value) {
            values.addEnd(value);
        }

};

template <typename key, typename value>
class Node {
    public:
        CircularDynamicArray<Element<key, value>> elements; //DATA

        Node* children[4];
        Node* parent;

        bool leaf; 

        Node() { //Constructor
            children[0] = nullptr;
            children[1] = nullptr;
            children[2] = nullptr;
            children[3] = nullptr;
        }
};

template <typename keytype, typename valuetype>
class two4Tree {
    public:

        Node<keytype, valuetype> *root; 
        
        two4Tree() {
            root = new Node<keytype, valuetype>();
        }

        two4Tree(keytype k[], valuetype V[], int s) {
            root = new Node<keytype, valuetype>();

            for(int i = 0; i < s; i++){
                insert(k[i], V[i]);
            }
        }

        ~two4Tree() {
            deconstructTree();
        }

        valuetype * search(keytype k) { //merge down
            Node<keytype, valuetype> *x = root;
            while(x != nullptr){
                int i = 0;
                while(i < x->elements.length() && k > x->elements[i].key){
                    i = i + 1;
                }
                if(i <= x->elements.length() && k == x->elements[i].key){
                    return ()
                }else if(x.leaf){
                    return NULL;
                }else{
                    x = x->children[i];
                }
            }
        }

        void insert(const keytype& key, const valuetype& value) {
            // Call a helper function to recursively insert the key-value pair
            insertRecursive(root, key, value);
            size++; // Increment the size of the tree
        }

        void insertRecursive(Node<keytype, valuetype>* node, const keytype& key, const valuetype& value) {
            // Check if the current node is a leaf node
            if (node->leaf) {
                // Insert the key-value pair into the current node
                if (node->size < 3) {
                    // If there is space in the node, simply insert the pair
                    Element<keytype, valuetype> element;
                    element.setKey(key, value);
                    node->elements.addEnd(element);
                    node->size++;
                } else {
                    // Otherwise, split the node and recursively insert into the appropriate child
                    // (you'll need to implement the splitting logic)
                }
            } else {
                // Find the appropriate child to recursively insert into
                // (you'll need to implement the search logic)
            }
        }

        void insertNonefull(Node<keytype, valuetype> *node, keytype k, valuetype v) {

            int i = node->elements.size();

        }

        void split(Node<keytype, valuetype> *node, int i) {
            Node<keytype, valuetype> *z = new Node<keytype, valuetype>;
            Node<keytype, valuetype> *y;

            if (i == 0){
                y = node->left;
            } else if (i == 1) {
                y = node->middeLeft;
            } else if (i == 2) {
                y = node->middleRight;
            } else if (i == 3) {
                y = node->right;
            }

            z->leaf = y->leaf;

            z->size = 1;

        }

        void deconstructTree(Node<keytype, valuetype>* node){
            if(node){
                for(int i = 0; i < node->size + 1; i++){
                    deconstructTree(node->children[i]);
                }

                delete node;
            }
        }

};
