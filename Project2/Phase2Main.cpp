#include <iostream>
using namespace std;
#include "two4Tree.cpp"

int main(){
	
	string K[12] = {"A","B","C","D","E","F","G","H","I","K","L","M"};
	float V[12] = {12.0, 11.0, 10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
	
	two4Tree<string,float> T1(K,V,12), T2;
	T1.preorder(); 
	cout << endl;
	cout << endl << "S: " << T1.size() << endl;
	cout << "REMOVE B " << T1.remove("B") << endl;
	T1.preorder();
	cout << endl << "S: " << T1.size() << endl;
	

	return 0;
}