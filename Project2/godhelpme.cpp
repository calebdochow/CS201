/*
        int deleteKey(Node<keytype, valuetype>* node, keytype k) {
            if (node == nullptr) {
                return 0; // Key not found
            }

            // Find the index of the key in the node's elements
            int i = 0;
            while (i < node->kN && k > node->elements[i].key) {
                i++;
            }
            //node->elements[i].key is node to be deleted

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
                    } else {
                        // Merge with siblings if possible
                        mergeWithSibling(node); //HERHEEHREHRHEHREHRE
                        return 1; // Key removed successfully
                    }
                } else { // Case 2: Internal node
                    // Find predecessor
                    Node<keytype, valuetype>* predNode = node->children[i];
                    while (!predNode->leaf) {
                        predNode = predNode->children[predNode->kN];
                    }

                    // Replace the key with predecessor
                    keytype predecessorKey = predNode->elements[predNode->kN - 1].key;
                    node->elements[i].key = predecessorKey;

                    // Recursively delete the predecessor key
                    return deleteKey(predNode, predecessorKey);
                }
            } else { // Key may be in child node
                // Determine the child to search recursively
                Node<keytype, valuetype>* child = nullptr;
                if (i < node->kN) {
                    child = node->children[i];
                }

                // Recursively delete from the appropriate child
                return deleteKey(child, k);
            }
        }


        void rotateRight(Node<keytype, valuetype>* parent, int index) {
            // Ensure the parent and its child at the specified index exist
            if (!parent || index < 0 || index >= parent->kN || !parent->children[index] || !parent->children[index + 1])
                return;

            Node<keytype, valuetype>* child = parent->children[index];
            Node<keytype, valuetype>* sibling = parent->children[index + 1];

            // Move the parent's key down to the child
            child->elements[child->kN] = parent->elements[index];
            child->kN++;

            // Move the sibling's first key up to the parent
            parent->elements[index] = sibling->elements[0];

            // Shift the sibling's keys to the left
            for (int i = 0; i < sibling->kN - 1; i++) {
                sibling->elements[i] = sibling->elements[i + 1];
            }
            sibling->kN--;

            // If the child is not a leaf, adjust child pointers
            if (!child->leaf) {
                child->children[child->kN] = sibling->children[0];

                for (int i = 0; i < sibling->kN + 1; i++) {
                    sibling->children[i] = sibling->children[i + 1];
                }
            }
        }
        */





       int deleteKey(Node<keytype, valuetype>* node, keytype k){
            if(node == nullptr){return 0;}

            int i = 0;
            while (i < node->kN && k > node->elements[i].key) { //FINDS NODE IN ROOT TO TRAVERSAL DOWN
                i++;
            }
            cout << "TESTING:" << node->elements[0].key << endl;
            if (i < node->kN && k == node->elements[i].key) {
            if (node->leaf) {
                    if (node->kN > 1) {
                        // Remove the key from the node
                        for (int j = i; j < node->kN - 1; j++) {
                            node->elements[j] = node->elements[j + 1];
                        }
                        node->kN--;
                        return 1; // Key removed successfully
                    } else {
                        // Merge with siblings if possible
                        mergeChild(node, i); //HERHEEHREHRHEHREHRE
                        return 1; // Key removed successfully
                    }
                } else { // Case 2: Internal node
                    // Find predecessor
                    Node<keytype, valuetype>* predNode = node->children[i];
                    while (!predNode->leaf) {
                        predNode = predNode->children[predNode->kN];
                    }

                    // Replace the key with predecessor
                    keytype predecessorKey = predNode->elements[predNode->kN - 1].key;
                    node->elements[i].key = predecessorKey;

                    // Recursively delete the predecessor key
                    return deleteKey(predNode, predecessorKey);
                }
            } else { // Key may be in child node
                // Determine the child to search recursively
                Node<keytype, valuetype>* child = nullptr;
                if (i < node->kN) {
                    child = node->children[i];
                }

                // Recursively delete from the appropriate child
                return deleteKey(child, k);
            }

            /*
            if(node->elements[0].key > k){ //look to left, since k < root[0]
                Node<keytype, valuetype>* current = node->children[0];
                if(current->kN < 2){

                    rotateLeft(node, 0);

                    Node<keytype, valuetype>* leftChild = node->children[0];

                    mergeLeft(leftChild, 0);

                    Node<keytype, valuetype>* toBeDeleted = leftChild->children[0];

                    int index = -1;
                    for (int i = 0; i < toBeDeleted->kN; ++i) {
                        if (toBeDeleted->elements[i].key == k) {
                            index = i;
                            break;
                        }
                    }

                    if (index != -1) {
                        // Shift elements to the left to remove the key
                        for (int i = index; i < toBeDeleted->kN - 1; ++i) {
                        toBeDeleted->elements[i] = toBeDeleted->elements[i + 1];
                        }
                    }
                    toBeDeleted->kN--;
                }
            }else if(node->elements[0].key < k){ //look  to right
            }
            return 1;
            */
        }
        void mergeChild(Node<keytype, valuetype>* parent, int index) {
            if (!parent || index < 0 || index >= parent->kN || !parent->children[index] || !parent->children[index + 1])
                return;

            Node<keytype, valuetype>* leftChild = parent->children[index];
            Node<keytype, valuetype>* rightChild = parent->children[index + 1];

            // Move the key from the parent down to the left child
            leftChild->elements[leftChild->kN] = parent->elements[index];
            leftChild->kN++;

            // Move the keys and child pointers from the right child to the left child
            for (int i = 0; i < rightChild->kN; i++) {
                leftChild->elements[leftChild->kN] = rightChild->elements[i];
                leftChild->kN++;
                leftChild->children[leftChild->kN] = rightChild->children[i];
                if (!rightChild->leaf)
                    rightChild->children[i] = nullptr; // Avoid dangling pointers
            }
            leftChild->children[leftChild->kN] = rightChild->children[rightChild->kN]; // Move the last child pointer
            if (!rightChild->leaf)
                rightChild->children[rightChild->kN] = nullptr; // Avoid dangling pointers

            // Remove the key from the parent
            for (int i = index; i < parent->kN - 1; i++) {
                parent->elements[i] = parent->elements[i + 1];
                parent->children[i + 1] = parent->children[i + 2];
            }
            parent->kN--;

            // Free memory of the right child
            delete rightChild;
        }


        void rotateLeft(Node<keytype, valuetype>* parent, int index){
            if(!parent || index < 0 || index >=parent->kN || !parent->children[index] || !parent->children[index+1]){return;}

            Node<keytype, valuetype>* current = parent->children[index];
            Node<keytype, valuetype>* rightSibling = parent->children[index + 1];

            //cout << "Left Child: " << current->elements[0].key << endl; //B, needs to be B
            //cout << "Right Sibling: "<< rightSibling->elements[0].key <<endl; //B, needs to be F

            //move parents key down to current node
            current->elements[current->kN] = parent->elements[index];
           //cout << "SHOULD BE D: " << current->elements[current->kN].key <<endl;
            current->kN++;

            //move the leftmost key from current node up to parent
            parent->elements[index] = rightSibling->elements[0]; //CARE
            //cout << "SHOULD BE F: " << parent->elements[index].key <<endl;

            //adjust child points if current is not a leaf
            if(!current->leaf){
                current->children[current->kN] = rightSibling->children[0];
                rightSibling->children[0] = nullptr;
            }
            
            //shift keys and child pointers in right child to the left
            for(int i = 0; i < rightSibling->kN - 1; i++){
                rightSibling->elements[i] = rightSibling->elements[i+1];
                //cout << "rightChild: " << rightSibling->elements[i].key << endl;
                rightSibling->children[i] = rightSibling->children[i+1];
            }
           // cout << "SHOULD BE H: " << rightSibling->elements[0].key <<endl;
            //cout << "SHOULD BE K: " << rightSibling->elements[1].key <<endl;

            rightSibling->children[rightSibling->kN - 1] = rightSibling->children[rightSibling->kN];
            rightSibling->children[rightSibling->kN] = nullptr;
            
            rightSibling->kN--;
        }

        void mergeLeft(Node<keytype, valuetype>* parent, int index) {
            if (!parent || index < 0 || index >= parent->kN || !parent->children[index] || !parent->children[index + 1])
                return;

            Node<keytype, valuetype>* leftChild = parent->children[index];
            Node<keytype, valuetype>* rightChild = parent->children[index + 1];

            // Move the key from the parent down to the left child
            leftChild->elements[leftChild->kN] = parent->elements[index];
            leftChild->kN++;

            // Move the keys and child pointers from the right child to the left child
            for (int i = 0; i < rightChild->kN; i++) {
                leftChild->elements[leftChild->kN] = rightChild->elements[i];
                leftChild->kN++;
                leftChild->children[leftChild->kN] = rightChild->children[i];
                if (!rightChild->leaf)
                    rightChild->children[i] = nullptr; // Avoid dangling pointers
            }
            leftChild->children[leftChild->kN] = rightChild->children[rightChild->kN]; // Move the last child pointer
            if (!rightChild->leaf)
                rightChild->children[rightChild->kN] = nullptr; // Avoid dangling pointers

            // Remove the key from the parent
            for (int i = index; i < parent->kN - 1; i++) {
                parent->elements[i] = parent->elements[i + 1];
                parent->children[i + 1] = parent->children[i + 2];
            }
            parent->kN--;

            // Free memory of the right child
            delete rightChild;
        }


        void mergeRight(Node<keytype, valuetype>* parent, int index){
            if (!parent || index < 0 || index >= parent->kN || !parent->children[index] || !parent->children[index + 1])
                return;

            Node<keytype, valuetype>* leftChild = parent->children[index];
            Node<keytype, valuetype>* rightChild = parent->children[index+1];
        }