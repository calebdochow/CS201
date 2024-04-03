#include <iostream>
using namespace std;
#include "two4Tree.cpp"

int main(){
	string K[12] = {"A","B","C","D","E","F","G","H","I","K","L","M"};
	float V[12] = {12,11,10,9,8,7,6,5,4,3,2,1};
	
	two4Tree<string,float> T1(K,V,12), T2;
	
	for(int i=0; i<12; i++) T2.insert(K[i],V[i]);
	// T1 and T2 should be the same trees
	
	T1.preorder();
	//Should output "D\n B\n A\n C\n F H K\n E\n G\n I\n L M\n"

	cout << T1.remove("H") << endl;

	T1.preorder();
	//Should output "D\n B\n A\n C\n F H K\n E\n G\n I\n L M\n"
	
	return 0;
}