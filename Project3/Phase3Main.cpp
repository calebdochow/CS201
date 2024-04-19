#include <iostream>
using namespace std;
#include "BHeap.cpp"

int main() {
    char K[6] = {'a','b','c','d','e','f'};
	
	BHeap<char> H1, H2;
	for(int i=0; i<6; i++) H1.insert(K[i]);
    H1.printKey();
    cout << H1.extractMin() << endl; //Should output a
    H1.printKey();
    return 0;
}