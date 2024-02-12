#include <iostream>
using namespace std;

template <typename elmtype>

class CircularDynamicArray{

    public:
        int capacityVar;
        int size;
        int front;
        int back;
        elmtype *dynamicArray;
        elmtype safe;

        CircularDynamicArray();
        CircularDynamicArray(int s);
        ~CircularDynamicArray();
        CircularDynamicArray(const CircularDynamicArray &old);
        CircularDynamicArray& operator=(const CircularDynamicArray& rhs);
        elmtype& operator[](int i);
        void addEnd(elmtype v); 
        void addFront(elmtype v);
        void delEnd(); 
        void delFront(); 
        int length(); 
        int capacity();
        void clear();
        elmtype QSelect(int k);
        void Sort();
        int linearSearch(elmtype e);
        int binSearch(elmtype e);

        void fixIndexes();
        void merge(elmtype *array, int const left, int const mid,int const right);
        void mergeSort(elmtype *array, int const begin, int const end);
        elmtype select(elmtype *array, int k, int arraySize);
        
};

//Default Constructor
template <typename elmtype> CircularDynamicArray<elmtype>::CircularDynamicArray() {
    dynamicArray = new elmtype[capacityVar = 2];
    size = front = back = 0;
}

//Constructor for capacity and size s
template <typename elmtype> CircularDynamicArray<elmtype>::CircularDynamicArray(int s) {
    dynamicArray = new elmtype[capacityVar = s];
    size = s;
    front = 0;
    back = s - 1;
}

//Destructor
template <typename elmtype> CircularDynamicArray<elmtype>::~CircularDynamicArray() {
    delete[] dynamicArray;
}

//Copy Constructor
template <typename elmtype> CircularDynamicArray<elmtype>::CircularDynamicArray(const CircularDynamicArray &old) {
    capacityVar = old.capacityVar;
    size = old.size;
    front = old.front;
    back = old.back;
    dynamicArray = old.dynamicArray;
}

//Assignment Operator Overloarder
template <typename elmtype> CircularDynamicArray<elmtype>& CircularDynamicArray<elmtype>::operator=(const CircularDynamicArray& rhs) {
    if(this != &rhs){
        delete[] dynamicArray;

        capacityVar = rhs.capacityVar;
        size = rhs.size;
        front = rhs.front;
        back = rhs.back;
        dynamicArray = new elmtype[capacityVar];

        for (size_t i = 0; i < size; i++){
            dynamicArray[i] = rhs.dynamicArray[i];
        }
    }

    return *this;    
}

template <typename elmtype> elmtype& CircularDynamicArray<elmtype>::operator[](int i) {
    if (i > size - 1) {
       cout << "i is out of bounds";  
       return safe;
    } 
    else return dynamicArray[(i + front) % capacityVar];
}

template <typename elmtype> void CircularDynamicArray<elmtype>::addEnd(elmtype v) {
    if (size == capacityVar) {
        capacityVar *= 2;
        elmtype *temp = new elmtype[capacityVar];

        for (int i = 0, j = front; i < size; i++) {
            temp[i] = dynamicArray[j];
            j = (j + 1) % size;
        }

        front = 0;
        back = size - 1;

        delete[] dynamicArray;
        dynamicArray = temp;

        delete[] temp;
    }

    dynamicArray[(front + size) % capacityVar] = v;
    size++;

    return;
}

template <typename elmtype> void CircularDynamicArray<elmtype>::addFront(elmtype v) {
    if (size == capacityVar) {
        capacityVar *= 2;
        elmtype *temp = new elmtype[capacityVar];   

        for (int i = 0, j = front; i < size; i++) {
            temp[i] = dynamicArray[j];
            j = (j + 1) % size;
        }

        front = 0;
        back = size - 1;

        delete[] dynamicArray;
        dynamicArray = temp;

        delete[] temp;
    }
    
    /*
    if (size == 0) {

    }
    if (front == 0) {
        front = (capacityVar - 1) % capacityVar;
    } else {
        front--;
    }*/

    front = (front - 1 + capacityVar) % capacityVar;
    dynamicArray[front] = v;
    size++;
}

template <typename elmtype> void CircularDynamicArray<elmtype>::delEnd() {
    back = (back - 1 + capacityVar) % capacityVar;
    size--;
    
    if (size == capacityVar / 4) {
        capacityVar /= 2;
        elmtype *temp = new elmtype[capacityVar];

        for (int i = 0, j = front; i < size; i++) {
            temp[i] = dynamicArray[j];
            j = (j + 1) % size;
        }

        front = 0;
        back = size - 1;

        delete[] dynamicArray;
        dynamicArray = temp;

        delete[] temp;
    }
}

template <typename elmtype> void CircularDynamicArray<elmtype>::delFront() {
    front = (front + 1) % capacityVar;
    size--;
    
    if (size == capacityVar / 4) {
        capacityVar /= 2;
        elmtype *temp = new elmtype[capacityVar];

        for (int i = 0, j = front; i < size; i++) {
            temp[i] = dynamicArray[j];
            j = (j + 1) % size;
        }

        front = 0;
        back = size - 1;

        delete[] dynamicArray;
        dynamicArray = temp;

        delete[] temp;
    }   
}

template <typename elmtype> int CircularDynamicArray<elmtype>::length() {
    return size;
}

template <typename elmtype> int CircularDynamicArray<elmtype>::capacity() {
    return capacityVar;
}

template <typename elmtype> void CircularDynamicArray<elmtype>::clear() {
    delete[] dynamicArray;
    dynamicArray = new elmtype[capacityVar = 2];
    size = front = back = 0;
}

template <typename elmtype> elmtype CircularDynamicArray<elmtype>::QSelect(int k) {
    fixIndexes();
    return select(dynamicArray, k, size);
}

template <typename elmtype> void CircularDynamicArray<elmtype>::Sort() {
    fixIndexes();
    mergeSort(dynamicArray, 0, size - 1);
}

template <typename elmtype> int CircularDynamicArray<elmtype>::linearSearch(elmtype e) {
    for (int i = 0, j = front; i < size; i++){
        if (dynamicArray[j] == e) return i;
        j = (j + 1) % capacityVar;
    }

    return -1;
}

template <typename elmtype> int CircularDynamicArray<elmtype>::binSearch(elmtype e) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        // Check if x is present at mid
        if (dynamicArray[(middle + front) % capacityVar] == e)
            return middle;

        // If x greater, ignore left half
        if (dynamicArray[(middle + front) % capacityVar] < e)
            left = middle + 1;

        // If x is smaller, ignore right half
        else
            right = middle - 1;
    }

    // If we reach here, then element was not present
    return -1;
}

template <typename elmtype> void CircularDynamicArray<elmtype>::fixIndexes(){
    elmtype *temp = new elmtype[capacityVar];

    for (int i = 0, j = front; i < size; i++) {
        temp[i] = dynamicArray[j];
        j = (j + 1) % capacityVar;
    }

    front = 0;
    back = size - 1;

    delete[] dynamicArray;
    dynamicArray = temp;
}

// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
template <typename elmtype> void CircularDynamicArray<elmtype>::merge(elmtype *array, int const left, int const mid,int const right) {
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;
 
    // Create temp arrays
    auto *leftArray = new elmtype[subArrayOne],
         *rightArray = new elmtype[subArrayTwo];
 
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
 
    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;
 
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
 
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
 
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}
 
// begin is for left index and end is right index
// of the sub-array of arr to be sorted
template <typename elmtype> void CircularDynamicArray<elmtype>::mergeSort(elmtype *array, int const begin, int const end) {
    if (begin >= end)
        return;
 
    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}


template <typename elmtype> elmtype CircularDynamicArray<elmtype>::select(elmtype *array, int k, int arraySize) { 
    
    elmtype randomPivot = array[rand() % arraySize];
    
    elmtype tempOne[arraySize];
    int sizeOne = 0;

    elmtype tempTwo[arraySize];
    int sizeTwo = 0;

    elmtype tempThree[arraySize];
    int sizeThree = 0;

    for (int i = 0; i < arraySize; i++) {
        if (array[i] < randomPivot) {
            tempOne[sizeOne] = array[i]; 
            sizeOne++;
        } 
        else if (array[i] == randomPivot) {
            tempTwo[sizeTwo] = array[i];
            sizeTwo++;
        }
        else {
            tempThree[sizeThree] = array[i];
            sizeThree++;
        }
    }
    
    
    if (k <= sizeOne) return select(tempOne, k, sizeOne);
    else if (k <= sizeOne + sizeTwo) return randomPivot;
    else return select(tempThree, k - sizeOne - sizeTwo, sizeThree);
} 