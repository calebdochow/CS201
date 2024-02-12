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
                array[i] = other.array[i];
            }
        }
        return *this;
    }

    T& operator[](int i) {
        if (i < size) {
            int actualIndex = (i + front) % cap;
            return array[actualIndex];
        } else {
            throw out_of_range("Index out of bounds");
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
        if (size > 1) {
            normalize();
            T* tempArray = new T[size];
            mergeSort(tempArray, front, size - 1);
            delete[] tempArray;
        }
    }

    void mergeSort(T* tempArray, int left, int right) {
        if(left < right){
            int middle = (left + right) / 2;
            mergeSort(tempArray, left, middle);
            mergeSort(tempArray, middle + 1, right);
            merge(tempArray, left, middle, right);
        } 
    }

    void merge(T* tempArray, int left, int middle, int right) {
        int i = left;
        int j = middle + 1;
        int k = left;

        while(i <= middle && j <= right){
            if(array[i] <= array[j]){
                tempArray[k] = array[i];
                i++;
                k++;
            }else{
                tempArray[k] = array[j];
                j++;
                k++;
            }
        }

        while(i <= middle){
            tempArray[k] = array[i];
            i++;
            k++;
        }

        while(j <= right){
            tempArray[k] = array[j];
            j++;
            k++;
        }

        for(int s = 0; s <= right; s++){
            array[s] = tempArray[s];
        }
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

    T Select(T qsArray[], int k, int qsSize) {
        if (qsSize == 0 || k == 0) {
            return -1;
        }

        size_t pivotIndex = rand() % qsSize;
        T pivot = qsArray[pivotIndex];

        T *L = new T[qsSize];
        T *E = new T[qsSize];
        T *G = new T[qsSize];

        int lSize = 0, eSize = 0, gSize = 0;

        for (int i = 0; i < qsSize; i++) {
            if (qsArray[i] < pivot) {
                L[lSize++] = qsArray[i];
            } else if (qsArray[i] == pivot) {
                E[eSize++] = qsArray[i];
            } else {
                G[gSize++] = qsArray[i];
            }
        }

        if (k < lSize) {
            T result = Select(L, k, lSize);
            delete[] L;
            delete[] E;
            delete[] G;
            return result;
        } else if (k < lSize + eSize) {
            delete[] L;
            delete[] E;
            delete[] G;
            return pivot;
        } else {
            T result = Select(G, k - lSize - eSize, gSize);
            delete[] L;
            delete[] E;
            delete[] G;
            return result;
        }
    }

    T QSelect(int k) {
        return Select(array, k, size);
    }


};