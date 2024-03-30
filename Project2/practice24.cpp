#include <iostream>
#include <cstddef>
#include <cstdlib>
#include "CircularDynamicArray.cpp"
using namespace std;

template <typename keytype, typename valuetype>
class Element{
    public:
    keytype key;
    CircularDynamicArray<valuetype> values;
    bool isEmpty = true;
    Element(){
        isEmpty = true;
        values = CircularDynamicArray<valuetype>();
    }
    Element(keytype k, valuetype v){
        isEmpty = true;
        key = k;
        values = CircularDynamicArray<valuetype>();
    }
    void SetKey(keytype k, valuetype v){
        isEmpty = false;
        key = k;
        values.addEnd(v);

    }
    void addValue(valuetype v){
        values.addEnd(v);
    }
};

template <typename keytype, typename valuetype>
class two4Tree{
    public:
    struct Node{
        Element<keytype, valuetype> elms[3];
        Node* parent;
        Node* child[4];
        int numKeys;
        int numSubKeys;
        bool leaf = true;
        //int duplicates[3];
        Node(){
            parent = nullptr;
            for (int i = 0; i < 4; i++){
                child[i] = nullptr;
            }
            for (int j = 0; j < 3; j++){
                elms[j] = Element<keytype, valuetype>();
            }
            numKeys = 0;
            numSubKeys = 0;
        }
        Node(keytype k, valuetype v, int numberOfKeys){ //wip
            parent = nullptr;
            Element element(k, v);
            elms[0] = element;
            for(int i = 0; i < numberOfKeys; i++){
                elms[i] = Element<keytype, valuetype>(k, v);
                addValue(v);
            }
            numKeys = 1;
            numSubKeys = 1;
        }
    };
    Node* root;
    int treeSize;

    two4Tree(){ //Default (empty tree) //done
        treeSize = 0;
        createTree();
    }
    two4Tree(keytype k[], valuetype v[], int s){ //Tree Constructor
        createTree(k[0], v[0]);
        for (int i = 1; i < s; i++){
            insert(k[i], v[i]);
            treeSize++;
        }
        /*
        For this constructor the tree should be built 
        using the arrays K and V containing s items of 
        keytype and valuetype.  The tree should be 
        built using repeated insertion. 
        */
    }
    void createTree(){
        root = new Node();
    }
    void createTree(keytype k, valuetype v){
        Node* node = new Node(k, v, 1);
        node->leaf = true;
        node->numKeys = 0;
        root = node;
    }

    //copy
    two4Tree(const two4Tree &old){ //test
        cout << "in copy constructor" << endl;
        root = copyTree(old.root, nullptr);
    }
    Node* copyTree(Node* oldNode, Node* parent){
        cout << "in copyTree" << endl;
        if (oldNode == nullptr){
            return nullptr;
        }
        Node* newNode = new Node;
        newNode->parent = parent;
        newNode->numKeys = oldNode->numKeys;
        newNode->numSubKeys = oldNode->numSubKeys;
        newNode->leaf = oldNode->leaf;
        for(int i = 0; i < oldNode->numKeys; i++){
            newNode->elms[i].key = oldNode->elms[i].key;
        }
        for(int i = 0; i < oldNode->numSubKeys; i++){
            newNode->child[i] = copyTree(oldNode->child[i], newNode);
        }
        return newNode;
    }

    two4Tree &operator=(const two4Tree &obj) {
        if (this != &obj) {
            treeDelete(root);
            root = copyTree(obj.root, nullptr);
        }
        return *this;
    }
    // assignment
    /*two4Tree &operator=(const two4Tree &obj){ //test
        if (this != &obj){
            treeDelete(root);
            Node* root = obj->root;
            root.numKeys = obj.numKeys;
            root.leaf = obj.leaf;
            root.parent = obj.parent;
            //copy
            for(int i = 0; i < ; i++){

            }
            //size
        }
        return *this;
    }*/

    ~two4Tree(){ //Destructor
        treeDelete(root);
    }
    void treeDelete(Node *r){ //test
        if (r){
            for (int i = 0; i < r->numKeys +1; i++){
                treeDelete(r->child[i]);
            }
            delete r;
        }
    }

    void insert(keytype k, valuetype v){ //wip
        //Node* newNode = new Node(k, v, 1);
        cout << endl;
        cout << "Starting Insertion: " << k << endl;
        Node* r = root;
        cout << "ROOT KEYS: " << r->numKeys << endl;
        if (r->numKeys == 3){ //4 node
            cout << "numKeys = 3, splitting" << endl;
            Node* s = new Node;
            root = s;
            s->leaf = false;
            s->numKeys = 0;
            s->child[0] = r;
            splitChild(s, 1);
            //cout << "finished splitChild, entering insertNonFull" << endl;
            insertNonFull(s, k);
        }
        else { //not 4 node
            insertNonFull(r, k);
        }
        cout << "PRE: ";
        preorder();
    }
    void insertNonFull(Node* x, keytype insertKey){
        int i = x->numKeys;
        if (x->leaf){ //is a leaf
            while(i >= 1 && insertKey < x->elms[i-1].key){
                x->elms[i].key = x->elms[i-1].key;
                i--;
            }
            x->elms[i].key = insertKey;
            x->numKeys++;
        }
        else{//is not a leaf
            while (i >= 1 && insertKey < x->elms[i-1].key){
                i--;
            }
            i++;
            if (x->child[i-1]->numKeys == 3){
                splitChild(x, i);
                if (insertKey > x->elms[i-1].key){
                    i++;
                }
            }
            insertNonFull(x->child[i-1], insertKey);
        }
    }
    void splitChild(Node* x, int index){
        Node* y = x->child[index-1];
        Node* z = new Node;
        z->leaf = y->leaf;
        //set parent
        z->numKeys = 1;
        z->elms[0].key = y->elms[2].key;
        if (!y->leaf){
            for (int j = 0; j < 2; j++){
                z->child[j] = y->child[j+2];
            }
        }
        y->numKeys = 1;//adjust key count for y        
        for (int j = x->numKeys; j > index; j--){//insert z as a child of x, shift childs left and put z at end (child[3])
            x->child[j+1] = x->child[j]; //fix
        }
        x->child[index] = z; 
        for (int j = x->numKeys-1; j > index-1; j--){
            x->elms[j+1].key = x->elms[j].key;
        }
        x->elms[index-1].key = y->elms[1].key; //move median from y up to x
        x->numKeys++; //adjust x key count
        //*/
        // test //

        //int t = 2;
        /*
        Node* y = x->child[index-1];
        Node* z = new Node;
        z->leaf = y->leaf;
        z->numKeys = 1;
        //z->elms[0].key = y->elms[2].key;//hard code
        for(int j = 0; j <= 1; j++){ //
            z->elms[j].key = y->elms[j+2].key;
            //cout << z->elms[j].key << "z " << j << endl;
        }
        if (!y->leaf){
            for (int j = 0; j < 2; j++){
                z->child[j] = y->child[j+2];
            }
        }
        y->numKeys = 1;//adjust key count for y        
        for (int j = x->numKeys; j > index; j--){//insert z as a child of x, shift childs left and put z at end (child[3])
            x->child[j+1] = x->child[j]; //fix
        }
        x->child[index] = z; //insert happens here
        
        for (int j = x->numKeys-1; j >= index-1; j--){
            x->elms[j+1].key = x->elms[j].key;
        }
        x->elms[index-1].key = y->elms[1].key; //move median from y up to x
        x->numKeys++; //adjust x key count
     */
    }

    void preorder(){
        if(root == nullptr) return;
        preorderHelper(root);
        cout << endl;
    }
    void preorderHelper(Node* node){
        if(node != nullptr){
            for(int i = 0; i < node->numKeys; i++){
                cout << node->elms[i].key << " ";
            }
            for(int i = 0; i <= node->numKeys; i++){
                preorderHelper(node->child[i]);
            }
        }
    }
};