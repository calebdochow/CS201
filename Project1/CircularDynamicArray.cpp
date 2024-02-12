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

    T& operator[](int i) {
        if (i < size) {
            int actualIndex = (i + front) % cap;
            return array[actualIndex];
        } else {
            cout << "Index out of bounds" << endl;
            return safe;
        }
    }


    int length() {
        return size;
    }

    int capacity() {
        return cap; 
    }

    int getFront(){
        return front;
    }

    void addEnd(T v) {
        if (size == cap) {
            resize(cap * 2);
        }
        array[(front + size) % cap] = v;
        size++;
    }

    void addFront(T v) {
        if (size == cap) {
            resize(cap * 2);
        }
        front = (front - 1 + cap) % cap;
        array[front] = v;
        size++;
    }

    void delEnd() {
        if (size > 0) {
            int indexToRemove = (front + size - 1) % cap;
            swapElements(indexToRemove, cap - 1);
            size--;

            if (size <= cap / 4 && cap / 2 >= 2) {
                resize(cap / 2);
            }
        }
    }

    void delFront() {
        if (size > 0) {
            front = (front + 1) % cap;
            size--;

            if (size <= cap / 4 && cap / 2 >= 2) {
                resize(cap / 2);
            }
        }
    }

    void swapElements(int index1, int index2) {
        if (index1 < size && index2 < size && index1 != index2) {
            T temp = array[index1];
            array[index1] = array[index2];
            array[index2] = temp;
        }
    }

    void resize(int newCapacity) {
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

    void clear() {
        delete[] array;
        cap = 2;
        size = 0;
        front = 0;
        array = new T[cap];
    }

    void normalize(){
        T *normalizedArray = new T[cap];
        for(int i = 0, j = front; i < size; i++){
            normalizedArray[i] = array[j];
            j = (j + 1) % cap;
        }
        
        front = 0;
        delete[] array;
        array = normalizedArray;
    }

    void Sort() {
        normalize();
        mergeSort(array, 0, size - 1);
    }

    void merge(T *mArray, int const left, int const mid,int const right) {
        int const subArrayOne = mid - left + 1;
        int const subArrayTwo = right - mid;
    
        // Create temp arrays
        auto *leftArray = new T[subArrayOne],
            *rightArray = new T[subArrayTwo];
    
        // Copy data to temp arrays leftArray[] and rightArray[]
        for (auto i = 0; i < subArrayOne; i++)
            leftArray[i] = mArray[left + i];
        for (auto j = 0; j < subArrayTwo; j++)
            rightArray[j] = mArray[mid + 1 + j];
    
        auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
        int indexOfMergedArray = left;
    
        // Merge the temp arrays back into array[left..right]
        while (indexOfSubArrayOne < subArrayOne
            && indexOfSubArrayTwo < subArrayTwo) {
            if (leftArray[indexOfSubArrayOne]
                <= rightArray[indexOfSubArrayTwo]) {
                mArray[indexOfMergedArray]
                    = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else {
                mArray[indexOfMergedArray]
                    = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;
        }
    
        // Copy the remaining elements of
        // left[], if there are any
        while (indexOfSubArrayOne < subArrayOne) {
            mArray[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }
    
        // Copy the remaining elements of
        // right[], if there are any
        while (indexOfSubArrayTwo < subArrayTwo) {
            mArray[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }
        delete[] leftArray;
        delete[] rightArray;
    }
 
// begin is for left index and end is right index
// of the sub-array of arr to be sorted
    void mergeSort(T *mArray, int const begin, int const end) {
        if (begin >= end)
            return;
    
        int mid = begin + (end - begin) / 2;
        mergeSort(mArray, begin, mid);
        mergeSort(mArray, mid + 1, end);
        merge(mArray, begin, mid, end);
    }


    int linearSearch(T e) {
        for(int i = 0; i <= size; i++){
            if(array[(front + i) % cap] == e){
                return i;
            }
        }
        return -1;
    }

    int binSearch(T e){
        int tempLeft = front;
        int tempRight = size - 1;
        while (tempLeft <= tempRight) {
            int mid = tempLeft + (tempRight - tempLeft) / 2;

            if (array[(mid + front) % cap] == e) {
                return mid;
            } else if (array[(mid + front) % cap] < e) {
                tempLeft = mid + 1;
            } else {
                tempRight = mid - 1; 
            }
        }
        return -1;
    }

    T Select(T *qsArray, int k, int qsSize) {
      
        T pivot = qsArray[rand() % qsSize];

        T *L = new T[qsSize];
        T *E = new T[qsSize];
        T *G = new T[qsSize];

        int lSize = 0, eSize = 0, gSize = 0;
       
        for (int i = 0; i < qsSize; i++) {
            if (qsArray[i] < pivot) {
                L[lSize] = qsArray[i];
                lSize++;
            } else if (qsArray[i] == pivot) {
                E[eSize] = qsArray[i];
                eSize++;
            } else {
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

    T QSelect(int k) {
        normalize();
        return Select(array, k, size);
    }


};