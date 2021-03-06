#ifndef MEMORY_H
#define MEMORY_H

#include "Process.h"

const int DEFAULT_SIZE = 10;

class Memory
{

  char * totalMem;             //Array to be dynamically allocated representing the total amount of "memory" available.
  
  int m_size;                  //curent total size of the memory array.
  int index_last_allocated;    //Ending index of last allocated process.

  public:
    Memory() {m_size = DEFAULT_SIZE; totalMem = new char[m_size]; index_last_allocated = 0;}
    Memory(int mem_size) {m_size = mem_size; totalMem = new char[m_size]; index_last_allocated = 0;}
    ~Memory() {delete[] totalMem;}
 
    //Acessors
    int size() {return m_size;}
    bool empty() {return !m_size;}

    //Mutators
    void reserve(int new_mSize);
    void clear();

    /*---Memory Management---*/
    void free_memory(Process * p);

    //Insertion Algorithms (Return true if succesful, false if insertion failed)
    bool insert_fFit(Process * p);
    bool insert_nFit(Process * p);
    bool insert_bFit(Process * p);

    /*---Functionality---*/

    //Finds the size of an empty memory block given the starting address 
    int empty_block_size(int index);

    //Finds the next empty block at or after the index.
    int next_empty(int index);

    //Outputs a "map" of the memory state to the screen.
    void map();
};

#endif