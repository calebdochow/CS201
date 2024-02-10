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

    CircularDynamicArray(const CircularDynamicArray& other) : cap(other.cap), size(other.size), front(other.front) { //Copy Constructor
        array = new T[cap];
        for (int i = 0; i < size; ++i) {
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
            for (int i = 0; i < size; ++i) {
                array[i] = other.array[(other.front + i) % other.cap];
            }
        }
        return *this;
    }

    T& operator[](int index) {
        if (index < size) {
            int actualIndex = (front + index) % cap;
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

    void addEnd(int v) {
        if (size == cap) {
            resize(cap * 2);
        }
        array[(front + size) % cap] = v;
        size++;
    }

    void addFront(int v) {
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
            swapElements(indexToRemove, cap - 1);

            if (size <= cap / 4 && cap / 2 >= 2) {
                resize(cap / 2);
            }
        }
    }

    void delFront() {
        if (size > 0) {
            front = (front + 1) % cap;
            size--;
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
    
        for (int i = 0; i < size; i++) {
            newArray[i] = array[(front + i) % cap];
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
        T* normalizedArray = new T[size];
        for(int i = 0; i < size; i++){
            normalizedArray[i] = array[(front + i) % cap];
        }
        for (int i = 0; i < size; i++) {
            array[i] = normalizedArray[i];
        }
        front = 0;
        delete[] normalizedArray;
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

    int partition(int left, int right){
        if(left >= right){
            return left;
        }
        int pivotIndex = left + rand() % (right - left + 1);
        T pivot = array[pivotIndex]; //pivot selected at random
        int i = left - 1;

        for(int j = left; j <= right; j++){
            if(array[j] <= pivot){
                i++;
                swapElements(i, j);
            }
        }
        swapElements(i + 1, pivotIndex);
        return i + 1;
    }

    T kthSmallest(int left, int right, int k){
        if(k > 0 && k <= right - left + 1){
            int index = partition(left, right);

            if(index - left == k - 1){
                return array[index];

            }else if(index - left >= k - 1){
                return kthSmallest(left, index - 1, k); 

            }else{
                return kthSmallest(index + 1, right,  k - index + left - 1); 

            }
        }
        return -1;
    }

    T QSelect(int k) {
        normalize();
        return kthSmallest(0, size - 1, k);
    }

};