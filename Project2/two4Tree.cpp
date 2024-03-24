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
        Element<key, value> elements[3];

        Node *children[4];
        Node* parent;

        bool leaf;
        int kN;
        int kNS; 

        Node() { //Constructor
            children[0] = nullptr;
            children[1] = nullptr;
            children[2] = nullptr;
            children[3] = nullptr;
            kN = 0;
            kNS = 0;
        }

        Node(key k, value v) { //Constructor
            Element<key, value> element(k, v);
            elements[0] = element;
            children[0] = nullptr;
            children[1] = nullptr;
            children[2] = nullptr;
            children[3] = nullptr;
            kN = 1;
            kNS = 1;
        }
};

template <typename keytype, typename valuetype>
class two4Tree {
    public:

        Node<keytype, valuetype> *root; 
        
        two4Tree() {
            Node<keytype, valuetype> *x = new Node<keytype, valuetype>();
            x->leaf = true;
            x->kN = 0;
            x->kNS = 0;
            root = x;
        }

        two4Tree(keytype k[], valuetype V[], int s) {
            Node<keytype, valuetype> *x = new Node<keytype, valuetype>();
            root = x;
            x->kN = 0;
            x->kNS = 0;

            for(int i = 0; i < s; i++){
                insert(k[i], V[i]);
                cout << "Key: " << k[i] << " Value: " << V[i] << endl;
            }
        }

        two4Tree(const two4Tree& other){
            Node<keytype, valuetype> *x = new Node<keytype, valuetype>();
            x->leaf = true;
            x->kN = 0;
            x->kNS = 0;
            this->root;
            this->root = copy(other.root);
        }

        ~two4Tree() {
            deconstruct(root);
        }

        void deconstruct(Node<keytype, valuetype> *node){
            if(node){
                for(int i = 0; i < node->kN + 1; i++){
                    deconstruct(node->children[i]);
                }
                delete node;
            }
        }

        two4Tree& operator=(const two4Tree& other){
            if(this != &other){
                Node<keytype, valuetype> *x = new Node<keytype, valuetype>();
                x->leaf = true;
                x->kN = 0;
                x->kNS = 0;
                root = x;
                root = copy(other.root);
            }
            return *this;
        }

        Node<keytype, valuetype> * copy(Node<keytype, valuetype>* node){
            if(!node){
                return nullptr;
            }
            Node<keytype, valuetype>* newNode = new Node<keytype, valuetype>;
            newNode->elements = node->elements;
            newNode->leaf = node->leaf;
            newNode->kN = node->kN;
            newNode->kNS = node->kNS;

            for(int i = 0; i < node->kN+1; i++){
                newNode->children[i] = copy(node->children[i]);
            }
            return newNode;
        }

        valuetype * search(keytype k) { //merge down
            Node<keytype, valuetype> *x = root;
            while(x != nullptr){
                int i = 0;
                while(i < x->elements.length() && k > x->elements[i].key){
                    i = i + 1;
                }
                if(i <= x->elements.length() && k == x->elements[i].key){
                    return 0;
                }else if(x->leaf){
                    return NULL;
                }else{
                    x = x->children[i];
                }
            }
        }

        void insert(const keytype& key, const valuetype& value) {
            
        }


        void insertNonefull(Node<keytype, valuetype> *node, keytype k, valuetype v) {

        }

        void split(Node<keytype, valuetype> *node, int i) {
           
        }


};
