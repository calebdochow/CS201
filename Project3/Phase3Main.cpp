#include <iostream>
using namespace std;
#include "BHeap.cpp"

int main() {
    BHeap<int> heap;
	heap.insert(5);
    heap.insert(3);
    heap.insert(7);
    heap.insert(2);
	heap.printKey();

    return 0;
}