#include <iostream>
#include <fstream>
#include <string>
#include "SelfOrdered.h"
#include "llist.h"

using namespace std;


int main()
{
	ifstream input;
	string word, name = "test.txt";
	LList<string> alpha;

	input.open(name.c_str());
	if (!input)
	{
		cout << "Could not open input." << endl;
		exit(1);
	}
	while (input >> word) {  alpha.append(word); }
	
	cout << "~~~~~~~~String Test~~~~~~~~" << endl;

	SelfOrdered<string> sc;
	sc.sort('C');
	alpha.moveToStart();
	for (int i{ 0 }; i < alpha.length(); i++)
	{
		sc.find(alpha.getValue());
		alpha.next();
	}

	cout << "Count Heuristic: Size of list: " << sc.size() << endl;
	cout << "Number of compares: " << sc.getCompares() << endl;
	sc.printlist(10);
	cout << endl << endl;


	
	SelfOrdered<string> sm;
	sm.sort('M');
	alpha.moveToStart();
	for (int i{ 0 }; i < alpha.length(); i++)
	{
		sm.find(alpha.getValue());
		alpha.next();
	}

	cout << "Move to Front Heuristic: Size of list: " <<sm.size() << endl;
	cout << "Number of compares: "<< sm.getCompares() << endl;
	sm.printlist(10);
	cout << endl<<endl;



	SelfOrdered<string> st;
	st.sort('T');
	alpha.moveToStart();
	for (int i{ 0 }; i < alpha.length(); i++)
	{
		st.find(alpha.getValue());
		alpha.next();
	}

	cout << "Transpose Heuristic: Size of list: " <<st.size()<< endl;
	cout << "Number of compares: " <<st.getCompares() << endl;
	st.printlist(10);
	cout << endl;

	cout << endl << endl << endl;
	cout << "~~~~~~~~Char Test~~~~~~~~" << endl;

	char list[8] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H' };
	char search[14] = { 'F' ,'D', 'F' ,'G', 'E', 'G', 'F', 'A', 'D', 'F' ,'G' ,'E', 'H', 'I' };
	
	
	
		SelfOrdered<char> C;
		C.sort('C');
			for (int i{ 0 }; i < 8; i++) {
				C.add(list[i]);
			}
			for (int i{ 0 }; i < 14; i++) {
				C.find(search[i]);
			}
			cout << "Count Heuristic: Size of list: " << C.size() << endl;
			cout << "Number of compares: " << C.getCompares() << endl;
			C.printlist();
			cout << endl << endl;
	
		SelfOrdered<char> M;
		M.sort('M');
			for (int i{ 0 }; i < 8; i++) {
				M.add(list[i]);
			}
			for (int i{ 0 }; i < 14; i++) {
				M.find(search[i]);
			}
			cout << "Move-to-Front Heuristic: Size of list: " << M.size() << endl;
			cout << "Number of compares: " << M.getCompares() << endl;
			M.printlist();
			cout << endl << endl;
	
		SelfOrdered<char> T;
			T.sort('T');
			for (int i{ 0 }; i < 8; i++) {
				T.add(list[i]);
			}
			for (int i{ 0 }; i < 14; i++) {
				T.find(search[i]);
			}
			cout << "Transpose Heuristic: Size of list: " << T.size() << endl;
			cout << "Number of compares: " << T.getCompares() << endl;
			T.printlist();
			cout << endl << endl;



	input.close();
	return 0;
}
