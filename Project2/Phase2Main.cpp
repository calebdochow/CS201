#include <iostream>
using namespace std;
#include "two4Tree.cpp"

int main(){
	string K[12] = {"A","B","C","D","E","F","G","H","I","K","L","M"};
	float V[12] = {12.0,11.0,10.0,9.0,8.0,7.0,6.0,5.0,4.0,3.0,2.0,1.0};
	
	two4Tree<string,float> T1(K,V,12), T2;
	
	for(int i=0; i<12; i++) T2.insert(K[i],V[i]);
	// T1 and T2 should be the same trees
	
	T1.preorder();
	//Should output "D\n B\n A\n C\n F H K\n E\n G\n I\n L M\n"
	cout << endl;
	
	cout << "REMOVE B: " << T1.remove("B") << endl;
	//Should output 0
	
	T1.preorder();
	//Should output "F\n B\n A\n C E\n H L\n G\n I K\n M\n"   
	
	return 0;
}