#ifndef MEMORY_H
#define MEMORY_H

#include "Process.h"
#include "Algorithm.h"
#include <iostream>

using namespace std;

const int DEFAULT_SIZE = 10;

class Memory
{

  bool * totalMem;             //Array to be dynamically allocated representing the total amount of "memory" available.
  
  int m_size;                  //curent total size of the memory array.
  int index_last_allocated;    //Ending index of last allocated process.

  public:
    Memory();
    Memory(int m_size);
    ~Memory() {delete[] totalMem;}
 
    //Acessors
    int size() {return m_size;}
    bool empty() {return !m_size;}
    bool full();

    //Mutators
    void reserve(int new_mSize);
    void clear();

    /*---Memory Management---*/
    void free_memory(Process & p);

    //Insertion Algorithms (Return true if succesful, false if insertion failed)
    bool insert_fFit(Process & p);
    bool insert_nFit(Process & p);
    bool insert_bFit(Process & p);

    /*---Helper Functions---*/
    
    //Allocates process at index.
    void allocate(Process & p, int index);

    //Chooses appopriate insertion algorithm to call and calls it.
    bool alg_function(Algorithm alg, Process & p);
    
    //Finds the size of an empty memory block given the starting address 
    int empty_block_size(int index);

    //Finds the next empty block at or after the index.
    int next_empty(int & index);

    //Outputs a "map" of the memory state to the screen.
    void map();
};

#endif