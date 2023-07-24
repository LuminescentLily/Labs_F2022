#pragma once

#include <memory>
#include "bagADT.h"

using namespace std;

template <typename E>
class ABag : public Bag<E> {
private:
	int max_size, cur_size;
public:
	unique_ptr<E[]> list;

	ABag(int s = 10) {
		max_size = s;
		cur_size = 0;
		list = make_unique<E[]>(max_size);
	}            // base constructor
	~ABag() {}   // base destructor

	// Insert a new item into the bag -- return false if fails and true if
	// successful
	bool addItem(const E& item) { 
		if (size() < bagCapacity()) {
			list[size()] = item;
			cur_size++;
			return true;
		}
		return false; }

	// Looks for 'item' in the bag and if found updates 'item' with the 
	// bag value and returns true.  Otherwise 'item' is left unchanged
	// and the method returns false.
	bool remove(E& item) { 
		if (find(item) == true) { cur_size--;  return true; }
		return false; }

	// Removes the top record from the bag, puts it in returnValue, and
	// returns true if the bag is not empty.  If the bag is empty the 
	// function returns false and returnValue remains unchanged.
	bool removeTop(E& returnValue) { 
		if (inspectTop(returnValue) == false) { return false; }
		cur_size--;
		return true; }

	// Finds the record using returnValue and if the record is found updates
	// returnValue based on the contents of the bag and returns true.  If the
	// record is not found the function returns false.  Works just like remove()
	// except that the found record is not removed from the bag.
	bool find(E& returnValue) const { 
		for (int i{ 0 }; i <= size(); i++) {
			if (returnValue == list[i]) {
				returnValue = list[i];
				return true;
			}
		}
		return false; }

	// Inspect the top of the bag.  If the bag is empty return
	// false and leave 'item' unchanged; otherwise, return true and update 
	// 'item' with the contents of the bag.
	bool inspectTop(E& item) const { 
		if (size() == 0) { return false; }
		item = list[size()];
		return true; }

	// empties the bag
	void emptyBag() { cur_size = 0; }

	// use the += operator to add an item to the bag
	bool operator+=(const E& addend) { return addItem(addend); }

	// get the number of items in the bag
	int size() const { return cur_size; }

	// get the capacity of the bag (size of your bag's array)
	int bagCapacity() const { return max_size; }

};