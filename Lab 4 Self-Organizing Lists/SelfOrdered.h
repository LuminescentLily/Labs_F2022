#pragma once
#include "SelfOrderedListADT.h"
#include "llist.h"

template <typename E>
class SelfOrdered : public SelfOrderedListADT<E> {
private: 
	char choice;
	int compares;
	LList<E> ptr;
public:
	//Default constructor/destructor
	SelfOrdered() {}
	virtual ~SelfOrdered() {}

	//Look for 'it'.  If found return true and execute the self-ordering
	//heuristic used for ordering the list: count, move-to-front, or transpose.
	//Increments the compare instance variable every time it compares 'it' to
	//other members of the list. Returns true if 'it' is found.
	bool find(const E& it) { 
		if (choice == 'C') {		//count option
		
			ptr.moveToStart();

			for (int i{ 0 }; i < size(); i++) {
				compares++;
				if (it == ptr.getValue()) {
					ptr.incrementFreq();
					int temF = ptr.getCurrFreq();
					E temp = ptr.remove();

					ptr.moveToStart();
					for (int j{ 0 }; j < size(); j++) {
						if (temF > ptr.getCurrFreq())
						{
							ptr.insert(temp);
							ptr.setCurrFreq(temF);
							return true;
						}
						else
						{
							ptr.next();
						}
					}
										
				}
				else {
					ptr.next();
				}
			}
			add(it);

		}
		else if (choice == 'M') {		//move-to-front option

			ptr.moveToStart();

			for (int i{ 0 }; i < size(); i++) {
				compares++;
				if (it == ptr.getValue()) {
					int fr = ptr.getCurrFreq();
					E temp = ptr.remove();
					ptr.moveToStart();
					ptr.insert(temp);
					ptr.setCurrFreq(fr+1);
					return true;
				}
				else {
					ptr.next();
				}
			}
			ptr.moveToStart();
			ptr.insert(it);
		
		}
		else if (choice == 'T') {		//transpose option

			ptr.moveToStart();

			for (int i{ 0 }; i < size(); i++) {
				compares++;
				if (it == ptr.getValue()) {
					int fr = ptr.getCurrFreq();
					E temp = ptr.remove();
					ptr.prev();
					ptr.insert(temp);
					ptr.setCurrFreq(fr + 1);
					return true;
				}
				else {
					ptr.next();
				}
			}
			add(it);

		}
		else { cout << "You did not pick a supported heuristic to sort your list by. Please choose one: C (Count), M (Move-to-front), or T (Transpose)." << endl; 
		}
		return false;
	}

	//Called by find if 'it' is not in the list. Adds the new 'it' to the list
	//Can also be called independently when initially loading the list with
	//unique values and when you want to load the list in the order 'it' is 
	//read without your re-order method being called (or the number of compares
	//being incremented.)
	void add(const E& it) { ptr.append(it); }  //Add new 'it' to the list

	void sort(char h) { choice = h; }			//Sets the heuristic to be used
	int getCompares() const { return compares; }   //Returns the number of accumulated compares
	int size() const { return ptr.length(); }      //Returns the size of the list

	//Print the list
	//In order print of the list.  printlist() prints the entire list
	//whereas printlist(n) prints n nodes.
	void printlist() {
		ptr.moveToStart();
		for (int i{ 0 }; i < size(); i++) {
			cout << ptr.getValue() << "-" << ptr.getCurrFreq() << " ";
			ptr.next();
		}
	}
	void printlist(int n) { 
		ptr.moveToStart();
		for (int i = 0; i < n; i++) {
			cout << ptr.getValue()<<"-"<<ptr.getCurrFreq() << " ";
			ptr.next();
		}
	}
	

};