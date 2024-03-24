#include <iostream>
using namespace std;
#include "two4Tree.cpp"

int main(){
	string K[12] = {"A","B","C","D","E","F","G","H","I","K","L","M"};
	float V[12] = {12,11,10,9,8,7,6,5,4,3,2,1};
	
	two4Tree<string,float> T1(K,V,12);
	cout << "HELPPPPPPPPPPP" << endl;

	//cout << *(T1.search("C")) << endl;
	// Should output 4
	
	return 0;
}