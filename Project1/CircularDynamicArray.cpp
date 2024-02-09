//Caleb Dochow
//1-30-24
#include <iostream>
#include <cstdlib>
using namespace std;

template <typename T>
class CircularDynamicArray {
private:
    T* array;
    size_t cap;
    size_t size;
    size_t front;

public:
    CircularDynamicArray() : cap(2), size(0), front(0) { //Default Constructor
        array = new T[cap];
    }

    CircularDynamicArray(size_t s) : cap(s), size(s), front(0) { //Constructor
        array = new T[s];
    }

    ~CircularDynamicArray() { //Deconstructor
        delete[] array;
    }

    CircularDynamicArray(const CircularDynamicArray& other) : cap(other.cap), size(other.size), front(other.front) { //Copy Constructor
        array = new T[cap];
        for (size_t i = 0; i < size; ++i) {
            array[i] = other.array[(other.front + i) % other.cap];
        }
    }
    
    CircularDynamicArray& operator=(const CircularDynamicArray& other) { //Copy Assignment Contructor
        if (this != &other) {
            delete[] array;
            cap = other.cap;
            size = other.size;
            front = other.front;
            array = new T[cap];
            for (size_t i = 0; i < size; ++i) {
                array[i] = other.array[(other.front + i) % other.cap];
            }
        }
        return *this;
    }


    void addEnd(size_t v) {
        if (size == cap) {
            resize(cap * 2);
        }
        array[(front + size) % cap] = v;
        size++;
    }

    void addFront(size_t v) {
        if (size == cap) {
            resize(cap * 2);
        }
        front = (front - 1 + cap) % cap;
        array[front] = v;
        size++;
    }

    void delEnd() {
        if (size > 0) {
            size_t indexToRemove = (front + size - 1) % cap;
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


    int length() {
        return size;
    }

    int capacity() {
        return cap; 
    }

    int getFront(){
        return front;
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
        for (size_t i = 0; i < size; i++) {
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

    void mergeSort(T* tempArray, size_t left, size_t right) {
        if(left < right){
            size_t middle = (left + right) / 2;
            mergeSort(tempArray, left, middle);
            mergeSort(tempArray, middle + 1, right);
            merge(tempArray, left, middle, right);
        } 
    }

    void merge(T* tempArray, size_t left, size_t middle, size_t right) {
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
        for(size_t i = 0; i < size; i++){
            if(array[i] == e){
                return i;
            }
        }
        return -1;
    }

    int binSearch(T e){
        int tempLeft = 0;
        int tempRight = size - 1;
        while (tempLeft <= tempRight) {
            int mid = tempLeft + (tempRight - tempLeft) / 2;
            if (array[mid] == e) {
                return mid;
            } else if (array[mid] < e) {
                tempLeft = mid + 1;
            } else {
                tempRight = mid - 1; 
            }
        }
        return -1;
    }

    int partition(int left, int right){
        int pivot = array[rand() % (size - 1)]; //pivot selected at random
        int i = left;

        for(int j = left; j <= right - 1; j++){
            if(array[j] <= pivot){
                swapElements(i, j);
                i++;
            }
        }
        swapElements(i, right);
        return i;
    }
    
    T QSelect(int k) {
        normalize();
        if(k > 0 && k <= right - left + 1){
            size_t index = partition(front, size - 1);

            if(index - left == k - 1){
                return array[index];
            }

            if(index - left > k - 1){
                
                //return QSelect() //return kthSmallest(arr, l, index - 1, k); 
            }

            //return kthSmallest(arr, index + 1, r,  k - index + l - 1); 
        }
        return -1;
    }

    void resize(size_t newCapacity) {
        T* newArray = new T[newCapacity];
    
        for (size_t i = 0; i < size; i++) {
            newArray[i] = array[(front + i) % cap];
        }
    
        delete[] array;
        array = newArray;
        cap = newCapacity;
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
            size_t actualIndex = (front + index) % cap;
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

    // C => "19 12 1 2 3 4 5 6 7 8 9 20 13"
    for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
    cout << "13 is found at: " << C.binSearch(13) << endl;
    cout << "-----------------------"<<endl;
    cout << "Capacity: " << C.capacity() << endl;
    cout << "Size: " << C.length() << endl;
    cout << "Front: " << C.getFront() << endl;
    cout << "-----------------------"<<endl;
    cout << endl << endl;
    C.Sort();
    for (int i=0; i< C.length();i++) cout << C[i] << " ";  cout << endl;
    cout << "13 is found at: " << C.binSearch(13) << endl;
    cout << "-----------------------"<<endl;
    cout << "Capacity: " << C.capacity() << endl;
    cout << "Size: " << C.length() << endl;
    cout << "Front: " << C.getFront() << endl;
    cout << "-----------------------"<<endl;


    return 0;
}