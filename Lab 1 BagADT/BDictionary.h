#pragma once
#include "dictionaryADT.h"
#include "kvpair.h"
#include "ABag.h"
#include <memory>
#include <iostream>

// The Dictionary abstract class.
template <typename Key, typename E>
class  BDictionary : public Dictionary<Key,E>{
private:
	unique_ptr<ABag<KVpair<Key, E>>> bagPtr;

public:
	BDictionary(int s = 10) { bagPtr = make_unique <ABag<KVpair<Key, E>>>(s); } // Default constructor
	~BDictionary() {} // Base destructor

	// Reinitialize dictionary
	void clear() { bagPtr->emptyBag(); }

	// Insert a record
	// k: The key for the record being inserted.
	// e: The record being inserted.
	// Return true if insert is successful and false otherwise
	bool insert(const Key& k, const E& e) {
		KVpair<Key, E> dot(k, e);
		return bagPtr->operator+=(dot);
	}

	// Looks for a record using the key and if found does the following:
	// - updates the E& rtnVal
	// - removes the record from the dictionary
	// - returns true
	// If the record is not found the function returns false.
	bool remove(const Key& k, E& rtnVal) {
		KVpair<Key, E> dot(k, rtnVal);
		rtnVal = dot.value();
		return bagPtr->remove(dot);;
	}

	// Takes an arbitrary record from the dictionary and does the following:
	// - updates the E& returnValue
	// - removes the record from the dictionary
	// - returns true
	// If the dictionary is empty the function returns false.
	bool removeAny(E& returnValue) {
		Key temp = bagPtr->list[1].key();
		KVpair<Key, E> dot(temp, returnValue);
		returnValue = dot.value();
		return bagPtr->remove(dot);
	}

	// Looks for a record using the key and if found does the following:
	// - updates the E& returnValue
	// - returns true
	// If the record is not found the function returns false.
	bool find(const Key& k, E& returnValue) const {
		KVpair<Key, E> dot(k, returnValue);
		return bagPtr->find(dot);}

	// Return the number of records in the dictionary.
	int size() { return bagPtr->size(); }

	// do not make any changes to this file or you will not get
	// any credit for your work -- Prof Sipantzi (05/13/2022)

};