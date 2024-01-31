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
    CircularDynamicArray() : capacity(2), size(0), front(0) {
        array = new T[capacity];
    }

    CircularDynamicArray(size_t s) : capacity(s), size(s), front(0) {
        array = new T[s];
    }

    ~CircularDynamicArray() {
        delete[] array;
    }

    //ADD COPY CONSTRUCTOR

    void addEnd(size_t v) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        array[(front + size) % capacity] = v;
        size++;
    }

    void addFront(size_t v) {
        if (size == capacity) {
            resize();
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

    size_t QSelect(int k) {
        // Implementation here
        return 0;
    }

    void Sort() {
        // Implementation here
    }

    int linearSearch(size_t e) {
        // Implementation here
        return 0;
    }

    int binSearch(size_t e){
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
    CircularDynamicArray<float> C(10);
	for (int i=0; i< C.length();i++) C[i] = i;
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// C => "0 1 2 3 4 5 6 7 8 9"
	C.delFront();
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 9"
	C.delEnd();
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8"
	C.addEnd(100.0);
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// C => "1 2 3 4 5 6 7 8 100"
	C.delFront();
	C.addEnd(200.0);
    for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// C => "2 3 4 5 6 7 8 100 200"	

	C.addEnd(300.0);
	C.addEnd(400.0);
    for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// C => "2 3 4 5 6 7 8 100 200 300 400"	
	
	C.delEnd(); C.delFront();C.delEnd();
	for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
	// C => "3 4 5 6 7 8 100 200"	
    return 0;
}
