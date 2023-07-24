#pragma once

#include <iostream>
#include "BufferBlockADT.h"
#include "constants.h"

using namespace std;

class LRUBlock : BufferblockADT {
private:
    //Instance variables:
    	int blockID;
    	char* block;

public:

    //sz is the size of the character array that data
    //points to
    LRUBlock() { }
    LRUBlock(char* data, int sz = 4096) {
        block = data; 
        blockID = sz/BLOCKSIZE; 
    }
    ~LRUBlock() {}

    //read the block from pos to pos + sz-1 (or to the end of the block)
    void getData(int pos, int sz, char* data) {
        if(pos+sz-1 > getBlocksize())
        { 
            for (int i = pos; i < (pos + sz - 1); i++) {
              /* if (i < getBlocksize())
                    { data[i] = block[i]; }*/
                data[i - pos] = block[i];
            }
        }
        else
        {
            for (int i = pos; i < (pos + sz); i++)
            {
                data[i - pos] = block[i];
            }
        }
    }

    //setID
    void setID(int id) { blockID = id; }

    //getID
    int getID() const { return blockID; }

    //getBlocksize
    int getBlocksize() const { 
        int i{ 0 };
        while(block[i] != '\0')
        { i++; }
        return i; 
    }

    //return the block
    char* getBlock() const { return block; }

    //set the block
    void setBlock(char* blk) { block = blk; }

};




