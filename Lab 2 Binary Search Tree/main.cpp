#include "BST.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

	BST<int,string> seed;
	cout << "Testing the insert function of my binary tree." <<endl<< endl;
	seed.insert(77, "seventy-seven");
	seed.insert(70, "seventy");
	seed.insert(75, "seventy-five");
	seed.insert(66, "sixty-six");
	seed.insert(79, "seventy-nine");
	seed.insert(68, "sixty-eight");
	seed.insert(67, "sixty-seven");
	seed.insert(69, "sixty-nine");
	seed.insert(90, "ninety");
	seed.insert(85, "eighty-five");
	seed.insert(83, "eighty-three");
	seed.insert(87, "eighty-seven");
	seed.insert(65, "sixty-five");
	cout << "My BST tree size is " << seed.size() << endl;
	cout << "My tree's structure is: " << endl;
	seed.print();

	cout << endl << endl << endl;

	cout << "---------Inorder printing of my tree---------" << endl;
	cout << "(tests my right threads and printOrder function)" << endl;
	seed.printInorder();

	cout << endl << endl << endl;

	cout << "---------Reverse order printing of my tree---------" << endl;
	cout <<"(tests my left threads and printReverse function)" << endl;
	seed.printReverse();


	return 0;
}