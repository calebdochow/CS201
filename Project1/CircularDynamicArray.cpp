//Caleb Dochow
//1-30-24
#include <iostream>
using namespace std;

template <typename T>
class CircularDynamicArray {
private:
    T* array;
    size_t capacity;
    size_t size;
    size_t front;

public:
    CircularDynamicArray() : capacity(2), size(0), front(0) { //Default Constructor
        array = new T[capacity];
    }

    CircularDynamicArray(size_t s) : capacity(s), size(s), front(0) { //Constructor
        array = new T[s];
    }

    ~CircularDynamicArray() { //Deconstructor
        delete[] array;
    }

    CircularDynamicArray(const CircularDynamicArray& other) : capacity(other.capacity), size(other.size), front(other.front) { //Copy Constructor
        array = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            array[i] = other.array[(other.front + i) % other.capacity];
        }
    }
    
    CircularDynamicArray& operator=(const CircularDynamicArray& other) { //Copy Assignment Contructor
        if (this != &other) {
            delete[] array;
            capacity = other.capacity;
            size = other.size;
            front = other.front;
            array = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                array[i] = other.array[(other.front + i) % other.capacity];
            }
        }
        return *this;
    }


    void addEnd(size_t v) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        array[(front + size) % capacity] = v;
        size++;
    }

    void addFront(size_t v) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        front = (front - 1 + capacity) % capacity;
        array[front] = v;
    }

    void delEnd() {
        if (size > 0) {
            size_t indexToRemove = (front + size - 1) % capacity;
            swapElements(indexToRemove, capacity - 1);
            size--;
            swapElements(indexToRemove, capacity - 1);

            if (size <= capacity / 4 && capacity / 2 >= 2) {
                resize(capacity / 2);
            }
        }
    }


    void delFront() {
        if (size > 0) {
            front = (front + 1) % capacity;
            size--;
        }
    }


    int length() {
        return size;
    }

    int getCapacity() {
        return capacity; 
    }

    void clear() {
        delete[] array;
        capacity = 2;
        size = 0;
        front = 0;
        array = new T[capacity];
    }

    void Sort() {
    if (size > 1) {
        T* tempArray = new T[size];
        mergeSort(0, size-1, tempArray);
        delete[] tempArray;
    }
    }

    void mergeSort(size_t left, size_t right, T* tempArray) {
        if (left < right) {
            size_t middle = left + (right - left) / 2;
            mergeSort(left, middle, tempArray);
            mergeSort(middle + 1, right, tempArray);
            merge(left, right, middle, tempArray);
        }
    }

    void merge(size_t left, size_t right, size_t middle, T* tempArray) {
        size_t leftSize = middle - left + 1;
        size_t rightSize = right - middle;

        T* leftArray = new T[leftSize];
        T* rightArray = new T[rightSize];

        // Populate leftArray and rightArray
        for (size_t i = 0; i < leftSize; i++) {
            leftArray[i] = array[(left + i) % capacity];
        }

        for (size_t i = 0; i < rightSize; i++) {
            rightArray[i] = array[(middle + 1 + i) % capacity];
        }

        size_t leftIndex = 0;
        size_t rightIndex = 0;
        size_t mergedIndex = left;

        // Merge leftArray and rightArray back into tempArray
        while (leftIndex < leftSize && rightIndex < rightSize) {
            if (leftArray[leftIndex] <= rightArray[rightIndex]) {
                tempArray[mergedIndex] = leftArray[leftIndex];
                leftIndex++;
            } else {
                tempArray[mergedIndex] = rightArray[rightIndex];
                rightIndex++;
            }
            mergedIndex++;
        }

        // Copy the remaining elements from leftArray, if any
        while (leftIndex < leftSize) {
            tempArray[mergedIndex] = leftArray[leftIndex];
            leftIndex++;
            mergedIndex++;
        }

        // Copy the remaining elements from rightArray, if any
        while (rightIndex < rightSize) {
            tempArray[mergedIndex] = rightArray[rightIndex];
            rightIndex++;
            mergedIndex++;
        }

        // Copy the sorted elements back to the original array
        for (size_t i = left; i <= right; i++) {
            array[i % capacity] = tempArray[i];
        }

        delete[] leftArray;
        delete[] rightArray;
    }


    int linearSearch(size_t e) {
        // Implementation here
        return 0;
    }

    int binSearch(size_t e){
        return 0;
    }

    size_t QSelect(int k) {
        // Implementation here
        return 0;
    }

    void resize(size_t newCapacity) {
        T* newArray = new T[newCapacity];
    
        for (size_t i = 0; i < size; i++) {
            newArray[i] = array[(front + i) % capacity];
        }
    
        delete[] array;
        array = newArray;
        capacity = newCapacity;
        front = 0;
    }


    void swapElements(size_t index1, size_t index2) {
        if (index1 < size && index2 < size && index1 != index2) {
            T temp = array[index1];
            array[index1] = array[index2];
            array[index2] = temp;
        }
    }

    T& operator[](size_t index) {
        if (index < size) {
            size_t actualIndex = (front + index) % capacity;
            return array[actualIndex];
        } else {
            throw out_of_range("Index out of bounds");
        }
    }
};

int main(int argc, char* argv[]) {
    CircularDynamicArray<int> C(10);
	for (int i=0; i< C.length();i++) C[i] = i;
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// C => "0 1 2 3 4 5 6 7 8 9"
	C.delFront();
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 9"
	C.addFront(12);
    C.addFront(19);
    C.addEnd(20);
    C.addEnd(13);
    for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
    C.Sort();
    for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;

    return 0;
}
