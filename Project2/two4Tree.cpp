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
            newNode->leaf = node->leaf;
            newNode->kN = node->kN;
            newNode->kNS = node->kNS;

            for (int i = 0; i < node->kN; ++i) {
                newNode->elements[i] = node->elements[i];
            }   

            for(int i = 0; i < node->kN+1; i++){
                newNode->children[i] = copy(node->children[i]);
            }
            return newNode;
        }

        
        valuetype * search(keytype k) { //merge down
            Node<keytype, valuetype> *x = root;
            while(x != nullptr){
                int i = 0;
                while(i < x->kN && k > x->elements[i].key){
                    i++;
                }
                if(i < x->kN && k == x->elements[i].key){
                    return &(x->elements[i].values[0]);
                }else if(x->leaf){
                    return nullptr;
                }else{
                    x = x->children[i];
                }
            }
            return nullptr;
        }
        

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
            
            z->leaf = y->leaf;
            
            z->kN = 1;
            z->elements[0] = y->elements[2];
            
            if (!y->leaf) {
                for (int j = 0; j < 2; j++) {
                    z->children[j] = y->children[j + 2];
                }
            }
            y->kN = 1;

            for (int j = x->kN; j > i - 1; j--) {
                x->children[j + 1] = x->children[j];
            }

            x->children[i] = z;

            for (int j = x->kN - 1; j > i - 2; j--) {
                x->elements[j + 1] = x->elements[j];
            }

            x->elements[i-1] = y->elements[1];
            x->kN++;
        }

        int remove(keytype k) {
            treeSize--;
            return deleteKey(root, k);
        }

        int deleteKey(Node<keytype, valuetype>* node, keytype k) {
            if (node == nullptr) {
                return 0; // Key not found
            }

            if((search(k)) != nullptr){

                // Find the index of the key in the node's elements
                int i = 0;
                while (i < node->kN && k > node->elements[i].key) {
                    i++;
                }

                Node<keytype, valuetype>* leftSibling = node->children[i];
                Node<keytype, valuetype>* rightSibling = node->children[i + 1];
                Node<keytype, valuetype>* child = node->children[i];

                // Key found in the current node
                if (i < node->kN && k == node->elements[i].key) {
                    // Case 1: Leaf node
                    if (node->leaf) {
                        if (node->kN > 1) {
                            // Remove the key from the node
                            for (int j = i; j < node->kN - 1; j++) {
                                node->elements[j] = node->elements[j + 1];
                            }
                            node->kN--;
                            return 1; // Key removed successfully
                        }
                    }
                    // Case 2: Root
                    //DO THE ROTATIONS AND SHIT TO REMOVE ROOT

                } else { // Key may be in child node

                    if(node->children[i]->kN == 1 && node->children[i+1]->kN == 1){ //MERGE CAUSE BOTH SIBLING kN == 1
                
                        // Move the key from the node down to the left Sibling
                        leftSibling->elements[leftSibling->kN] = node->elements[i];
                        leftSibling->kN++;

                        // Move the keys and sibling pointers from the right sibling to the left sibling
                        for (int i = 0; i < rightSibling->kN; i++) {
                            leftSibling->elements[leftSibling->kN] = rightSibling->elements[i];
                            leftSibling->kN++;
                            leftSibling->children[leftSibling->kN] = rightSibling->children[i];
                            if (!rightSibling->leaf)
                                rightSibling->children[i] = nullptr;
                        }

                        // Move the last sibling pointer
                        leftSibling->children[leftSibling->kN] = rightSibling->children[rightSibling->kN];

                        if (!rightSibling->leaf)
                            rightSibling->children[rightSibling->kN] = nullptr;

                        // Remove the key from the node
                        for (int i = i; i < node->kN - 1; i++) {
                            node->elements[i] = node->elements[i + 1];
                            node->children[i + 1] = node->children[i + 2];
                        }
                        node->kN--;

                        // Free memory of the right child
                        delete rightSibling;

                    }else if(node->children[i]->kN == 1 && node->children[i+1]->kN > 1){ //Rotate Left CAUSE EXTRA kN ON RIGHT
                        //move node key down to leftsibling node
                        leftSibling->elements[leftSibling->kN] = node->elements[i];
                        leftSibling->kN++;

                        //move the leftmost key from leftSibling node up to parent
                        node->elements[i] = rightSibling->elements[0];
                        
                        //adjust child points if leftSibling is not a leaf
                        if(!leftSibling->leaf){
                            leftSibling->children[leftSibling->kN] = rightSibling->children[0];
                            rightSibling->children[0] = nullptr;
                        }

                        //shift keys and child pointers in right sibling to the left
                        for(int i = 0; i < rightSibling->kN - 1; i++){
                            rightSibling->elements[i] = rightSibling->elements[i+1];
                            rightSibling->children[i] = rightSibling->children[i+1];
                        }

                        rightSibling->children[rightSibling->kN - 1] = rightSibling->children[rightSibling->kN];
                        rightSibling->children[rightSibling->kN] = nullptr;
                        rightSibling->kN--;

                    }else if(node->children[i]->kN == 1 && node->children[i - 1]->kN > 1){ //ROTATE RIGHT CAUSE EXTRA kN ON LEFT
                        //
                    }


                    return deleteKey(child, k);
                    return 0;
                }
            }
            return 0;
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
