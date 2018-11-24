#ifndef MEMORY_H
#define MEMORY_H

#include "mem_block.h"

class Memory
{
  
  Mem_block * totalMem;             //Array to be dynamically allocated representing the total amount of "memory" available.
  int m_size = 0;
  int index_last_allocated;

  public:
    Memory() {}
    Memory(int mem_size) {m_size = mem_size; totalMem = new Mem_block[m_size];}
    ~Memory() {delete[] totalMem;}
 
    //Acessors
    int size() {return m_size;}
    bool empty() {return !m_size}

    //Mutators
    void reserve(int new_mSize);
    void clear();

    //Insertion Algorithms
    void insert_fFit(Mem_block * block);
    void insert_nFit(Mem_block * block);
    void insert_bFit(Mem_block * block);
};

void reserve(int new_mSize)
{
  this->clear();

  totalMem = new Mem_block[new_mSize];
  m_size = new_mSize;
}

void clear()
{
  delete[] totalMem;
  m_size = 0;
}


#endif