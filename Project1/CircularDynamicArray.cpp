//Caleb Dochow
//1-30-24
#include <iostream>
#include <cstdlib>
using namespace std;

template <typename T>
class CircularDynamicArray {
private:
    T* array;
    int cap;
    int size;
    int front;
    T safe;

public:
    CircularDynamicArray() : cap(2), size(0), front(0) { //Default Constructor
        array = new T[cap];
    }

    CircularDynamicArray(int s) : cap(s), size(s), front(0) { //Constructor
        array = new T[s];
    }

    ~CircularDynamicArray() { //Deconstructor
        delete[] array;
    }

    CircularDynamicArray(const CircularDynamicArray& other){ //Copy Constructor
        cap = other.cap;
        size = other.size;
        front = 0;
        array = new T[cap];
        for (int i = 0; i < size; i++) {
            array[i] = other.array[(other.front + i) % other.cap];
        }
    }
    
    CircularDynamicArray<T>& operator=(const CircularDynamicArray& other) { //Copy Assignment Contructor
        if (this != &other) {
            delete[] array;
            cap = other.cap;
            size = other.size;
            front = other.front;
            array = new T[cap];
            for (int i = 0; i < size; i++) {
                array[i] = other.array[(i + other.front) % other.cap];
            }
        }
        return *this;
    }

    T& operator[](int i) { // [] Operator
        if (i < size) {
            int actualIndex = (i + front) % cap;
            return array[actualIndex];
        } else {
            cout << "Index out of bounds" << endl;
            return safe;
        }
    }


    int length() { //gets size of array; O(1)
        return size;
    }

    int capacity() { //gets capacity of array; O(1)
        return cap; 
    }

    int getFront(){ //gets front index of array; O(1)
        return front;
    }

    void addEnd(T v) { //adds element of type T to end of array; O(1) amortized
        if (size == cap) {
            resize(cap * 2);
        }
        array[(front + size) % cap] = v;
        size++;
    }

    void addFront(T v) { //adds element of type T to front of array; O(1) amortized
        if (size == cap) {
            resize(cap * 2);
        }
        front = (front - 1 + cap) % cap;
        array[front] = v;
        size++;
    }

    void delEnd() { //removes element from end of array; O(1) amortized
        if (size > 0) {
            int indexToRemove = (front + size - 1) % cap;
            swapElements(indexToRemove, cap - 1);
            size--;

            if (size <= cap / 4 && cap / 2 >= 2) {
                resize(cap / 2);
            }
        }
    }

    void delFront() { //removes element from front of array; O(1) amortized
        if (size > 0) {
            front = (front + 1) % cap;
            size--;

            if (size <= cap / 4 && cap / 2 >= 2) {
                resize(cap / 2);
            }
        }
    }

    void swapElements(int index1, int index2) { //swaps index of two elements. Used in delEnd to maintain amortized O(1)
        if (index1 < size && index2 < size && index1 != index2) {
            T temp = array[index1];
            array[index1] = array[index2];
            array[index2] = temp;
        }
    }

    void resize(int newCapacity) { //resizes array with new capacity; O(n) n = size
        T* newArray = new T[newCapacity];
    
        for(int i = 0, j = front; i < size; i++){
            newArray[i] = array[j];
            j = (j + 1) % cap;
        }
    
        delete[] array;
        array = newArray;
        cap = newCapacity;
        front = 0;
    }

    void clear() { //Clears array O(1)
        delete[] array;
        cap = 2;
        size = 0;
        front = 0;
        array = new T[cap];
    }

    void normalize(){ //fixes the indexes of the array, sets front to index[0]; O(n) n = size
        T *normalizedArray = new T[cap];

        for(int i = 0, j = front; i < size; i++){
            normalizedArray[i] = array[j];
            j = (j + 1) % cap;
        }

        front = 0;
        delete[] array;
        array = normalizedArray;
    }

    void Sort() { //Uses the mergesort algorithm; O(nLogn) n = size
        normalize();
        mergeSort(array, 0, size - 1);
    }

    void merge(T *mArray, int const left, int const mid, int const right) { //Merge portion of mergesort, merges two arrays together for final result
        int const temp1 = mid - left + 1;
        int const temp2 = right - mid;
    
        //Creates two temp arrays
        T *leftArray = new T[temp1];
        T *rightArray = new T[temp2];
    
        // Copy data to arrays
        for (int i = 0; i < temp1; i++){
            leftArray[i] = mArray[left + i];
        }
        for (int j = 0; j < temp2; j++){
            rightArray[j] = mArray[mid + 1 + j];
        }
        int indexOftemp1 = 0;
        int indexOftemp2 = 0;
        int mergedIndex = left;
    
        // Merge the temp arrays together back into array
        while (indexOftemp1 < temp1 && indexOftemp2 < temp2) {
            if (leftArray[indexOftemp1] <= rightArray[indexOftemp2]) {
                mArray[mergedIndex] = leftArray[indexOftemp1];
                indexOftemp1++;
            }
            else {
                mArray[mergedIndex] = rightArray[indexOftemp2];
                indexOftemp2++;
            }
            mergedIndex++;
        }
    
        // Copy the remaining elements of left
        while (indexOftemp1 < temp1) {
            mArray[mergedIndex] = leftArray[indexOftemp1];
            indexOftemp1++;
            mergedIndex++;
        }
    
        // Copy the remaining elements of right
        while (indexOftemp2 < temp2) {
            mArray[mergedIndex] = rightArray[indexOftemp2];
            indexOftemp2++;
            mergedIndex++;
        }
        //frees memory
        delete[] leftArray;
        delete[] rightArray;
    }
 
    
    void mergeSort(T *mArray, int const left, int const right) { //array, (left, right) / (front, back)
        if (left >= right){return;}

        int mid = left + (right - left) / 2;

        mergeSort(mArray, left, mid);
        mergeSort(mArray, mid + 1, right);
        merge(mArray, left, mid, right);
    }


    int linearSearch(T e) { //linear search looking for item e; O(n) n = size
        for(int i = 0; i <= size; i++){
            if(array[(front + i) % cap] == e){
                return i; //returns elements index
            }
        }
        return -1;
    }

    int binSearch(T e){ //binary search looking for item e; O(log n) n = size
        int tempLeft = 0;
        int tempRight = size - 1;
        while (tempLeft <= tempRight) {
            int mid = tempLeft + (tempRight - tempLeft) / 2;

            if (array[(mid + front) % cap] == e) {
                return mid; //Returns index of item
            } else if (array[(mid + front) % cap] < e) {
                tempLeft = mid + 1;
            } else {
                tempRight = mid - 1; 
            }
        }
        return -1; //item not in list
    }

    T Select(T *qsArray, int k, int qsSize) { //recursive select function used for QSelect method
      
        T pivot = qsArray[rand() % qsSize]; //random pivot

        T *L = new T[qsSize];
        T *E = new T[qsSize];
        T *G = new T[qsSize];

        int lSize = 0, eSize = 0, gSize = 0; //track size of three new arrays
       
        for (int i = 0; i < qsSize; i++) {
            if (qsArray[i] < pivot) { //less than pivot, add to L
                L[lSize] = qsArray[i];
                lSize++;
            } else if (qsArray[i] == pivot) { //equal than pivot, add to E
                E[eSize] = qsArray[i];
                eSize++;
            } else { //greater than pivot, add to G
                G[gSize] = qsArray[i];
                gSize++;
            }
        }

        if (k <= lSize) {
            return Select(L, k, lSize);
        } else if (k <= lSize + eSize) {
            return pivot;
        } else {
            return Select(G, k - lSize - eSize, gSize);
        }
    }

    T QSelect(int k) {//finds and returns kth smallest element; O(n) n = size
        normalize();
        return Select(array, k, size);
    }


};