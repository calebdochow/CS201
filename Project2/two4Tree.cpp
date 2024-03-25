#include <iostream>
#include <stack>
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

        Element(K k, V value) {
            isEmpty = false;
            key = k;
            values.addEnd(value);
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
        int treeSize;
        
        two4Tree() {
            Node<keytype, valuetype> *x = new Node<keytype, valuetype>();
            x->leaf = true;
            x->kN = 0;
            x->kNS = 0;
            root = x;
            treeSize = 0;
        }

        two4Tree(keytype k[], valuetype V[], int s) {
            Node<keytype, valuetype> *x = new Node<keytype, valuetype>();
            root = x;
            x->kN = 0;
            x->kNS = 0;
            treeSize = s;

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

        /*
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
        */

        void insert(const keytype& key, const valuetype& value) {
            Node<keytype, valuetype>* r = root;
            treeSize++;
            if(r->kN == 3){
             
                Node<keytype, valuetype>* s = new Node<keytype, valuetype>();
                root = s;
                s->leaf = false;
                s->kN = 0;
                s->children[0] = r;
                split(s, 1);
                insertNonefull(s, key, value);
            }else{
                insertNonefull(r, key, value);
            }
        }


        void insertNonefull(Node<keytype, valuetype> *x, keytype k, valuetype v) {
            int i = x->kN;
            
            if(x->leaf){
               
                while(i > 0 && k< x->elements[i-1].key){
                    x->elements[i] = x->elements[i-1];
                    i--;
                }
                cout << " IMPORTANT i: " << i << endl;
                Element<keytype, valuetype> newElement(k, v);
                x->elements[i] = newElement;
                x->kN++;
            }else{
                
                while(i > 0 && k < x->elements[i-1].key){
                    i--;
                }
                i++;
                
                if(x->children[i-1]->kN == 3){
                    split(x, i);
                    if(k > x->elements[i-1].key){
                        i++;
                    }
                    
                }
                insertNonefull(x->children[i-1], k, v);
            }
        }

        void split(Node<keytype, valuetype> *x, int i) {
            Node<keytype, valuetype>* z = new Node<keytype, valuetype>();
            Node<keytype, valuetype>* y = x->children[i-1];
            //y = x->children[i-1];
            z->leaf = y->leaf;
            
            z->kN = 1;
            z->elements[0] = y->elements[2];
            
            if (!y->leaf) {
                for (int j = 0; j < 2; j++) {
                    z->children[j] = y->children[j + 2];
                }
            }

            y->kN = 1;

            for (int j = x->kN; j > i; j--) {
                x->children[j + 1] = x->children[j];
            }

            x->children[i] = z;

            for (int j = x->kN - 1; j > i - 1; j--) {
                x->elements[j + 1] = x->elements[j];
            }

            x->elements[i-1] = y->elements[1];
            x->kN++;
        }

        void preorder(){
            if (root == nullptr){return;}

            stack<Node<keytype, valuetype>*> nodeStack;
            nodeStack.push(root);

            while (!nodeStack.empty()) {
                Node<keytype, valuetype>* current = nodeStack.top();
                nodeStack.pop();

                for (int i = 0; i < current->kN; i++) {
                    cout << current->elements[i].key << " ";
                }

                for (int i = current->kN; i >= 0; i--) {
                    if (current->children[i] != nullptr) {
                        nodeStack.push(current->children[i]);
                    }
                }
            }
        }

        void inorder() {
            
        }

        void postorder() {
            if (root == nullptr){return;}

            stack<Node<keytype, valuetype>*> nodeStack;
            stack<Node<keytype, valuetype>*> outputStack; // To reverse the postorder result

            nodeStack.push(root);

            while (!nodeStack.empty()) {
                Node<keytype, valuetype>* current = nodeStack.top();
                nodeStack.pop();

                // Push the current node to the output stack
                outputStack.push(current);

                // Push left child first
                for (int i = current->kN; i >= 0; --i) {
                    if (current->children[i] != nullptr) {
                        nodeStack.push(current->children[i]);
                    }
                }
            }

            // Print the keys from the output stack to get the postorder traversal result
            while (!outputStack.empty()) {
                Node<keytype, valuetype>* current = outputStack.top();
                outputStack.pop();

                for (int i = 0; i < current->kN; ++i) {
                    cout << current->elements[i].key << " ";
                }
            }
        }

        int size() {
            return treeSize/2;
        }
};