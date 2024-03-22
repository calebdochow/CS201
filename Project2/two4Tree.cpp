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
        CircularDynamicArray<Element<key, value>> elements;
        //Element<key, value> elements = [];

        Node* left;
        Node* middeLeft;
        Node* middleRight;
        Node* right;
        Node* parent;

        bool leaf;
        int size;

        Node() {
            left = nullptr;
            middeLeft = nullptr;
            middleRight = nullptr;
            right = nullptr;
            size = 0;
        }

        Node() {

        }
};

template <typename keytype, typename valuetype>

class two4Tree {
        
    public:

        Node<keytype, valuetype> *root; 
        int size;
        
        two4Tree() {
            root = new Node<keytype, valuetype>();
            int size = 0;
        }
        two4Tree(keytype k[], valuetype V[], int s) {
            
        }
        ~two4Tree() {

        }

        valuetype * search(keytype k) { //merge down

        }

        void insert(keytype k, valuetype v) { //implement counter

            Node<keytype, valuetype> *r = root;

            if (r->elements.size() == 3) {
                Node<keytype, valuetype> s = new Node<keytype, valuetype>;
                root = s;
                s.leaf = false;
                s.size = 0;
                s.left = r;
                split(s, 1);
                insertNonefull(s, k, v)
            } else {
                insertNonefull(root, k, v);
            }
        }

        void insertNonefull(Node<keytype, valuetype> *node, keytype k, valuetype v) {

            int i = node->elements.size();

            if ()
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

            for (int i = 0, i < 0; i++){

            }

            if (!y->leaf) {
                for (int i = 0, )
            }
        }

        int remove(keytype k) {

        }

        int rank(keytype k) { //return leftmost rank for duplicates

        }

        keytype select(int pos) {

        }

        int duplicates(keytype k) {

        }

        int size() {

        }

        void preorder() {

        }

        void inorder() {

        }

        void postorder() {

        }
};
