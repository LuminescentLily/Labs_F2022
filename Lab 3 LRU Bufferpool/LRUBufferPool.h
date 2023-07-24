#pragma once

#include <string>
#include "BufferPoolADT.h"
#include "LRUBlock.h"
#include <fstream>
using namespace std;

// ADT for buffer pools using the message-passing style
class LRUBufferPool : BufferPoolADT {
private:
	//The buffer pool consists of X number of buffer blocks
	string file;
	int pool, blockSZ;
	LRUBlock lru[POOL_SIZE];


public:
	//Constructor gets the filename of the file to be buffered,
	//opens the file, and instantiates poolSize buffer blocks by
	//reading the file and filling the blocks in order.  When the constructor
	//is done the buffer pool blocks should be full with the beginning
	//contents of the input file.
	LRUBufferPool() { 
		file = ""; 
		pool = POOL_SIZE; 
		blockSZ = BLOCKSIZE; 
	}
	LRUBufferPool(string filename, int poolSize = 5, int blockSize = 4096) { 
		file = filename; 
		pool = poolSize; 
		blockSZ = blockSize; 

		fstream input;
		input.open(file.c_str(), fstream::in | fstream::binary);
		for (int i{ 0 };i<pool;i++)
		{ 
			lru[i].setID(i); 
			char* temp = new char[blockSZ];
			input.read(temp, blockSZ);
			lru[i].setBlock(temp);
		}
		if (!input) {
			cout << "Could not open." << endl;
			exit(1);
		}
		input.close();
	}
	~LRUBufferPool() {}

	// Copy "sz" bytes from position "pos" of the buffered
	//   storage to "space".
	void getBytes(char* space, int sz, int pos) {
		bool checkVar = false;
		LRUBlock tem;

		
		for (int i{ 0 }; i < pool; i++) {
			if (pos / BLOCKSIZE == lru[i].getID())
			{
				lru[i].getData(pos % BLOCKSIZE, sz, space);
				tem = lru[i];
				for (int j = i; j > 0; j--)
				{
					lru[j] = lru[j - 1];
				}
				checkVar = true;
				lru[0] = tem;
			}
		}

		if(checkVar == false)
		{
			ifstream read;
			read.open(file.c_str(),fstream::in | fstream::binary);
			if (!read) {
				cout << "Could not open." << endl;
				exit(1);
			}
			read.seekg((pos/BLOCKSIZE)*BLOCKSIZE);
			char* temp = new char[BLOCKSIZE];
			read.read(temp, BLOCKSIZE);
			tem.setBlock(temp);
			tem.setID(pos/BLOCKSIZE);

			for(int i=4;i>0;i--){
				lru[i].setBlock(lru[i - 1].getBlock());
				lru[i].setID(lru[i - 1].getID());
			}
			lru[0] = tem;
			lru[0].getData(pos % BLOCKSIZE, sz, space);

			read.close();
		}

	}

	// Print the order of the buffer blocks using the block id
	//	 numbers.
	void printBufferBlockOrder() {
	//My buffer block order from most recently used to LRU is:
	//	1, 0, 2, 3, 4,

		cout << "My buffer block order from most recently used to LRU is:" << endl;
		for (int i{ 0 }; i < pool; i++) {
			cout << lru[i].getID() << ", ";
		}
		cout << endl;
	}

	// Get the block id number of the least recently used 
	//	 buffer block.
	int getLRUBlockID() { return lru[4].getID(); }

};




