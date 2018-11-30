#ifndef MEMORY_H
#define MEMORY_H

#include "process.h"

class Memory
{

  char * totalMem;             //Array to be dynamically allocated representing the total amount of "memory" available.
  
  int m_size = 0;
  int index_last_allocated;

  public:
    Memory() {}
    Memory(int mem_size) {m_size = mem_size; totalMem = new char[m_size];}
    ~Memory() {delete[] totalMem;}
 
    //Acessors
    int size() {return m_size;}
    bool empty() {return !m_size}

    //Mutators
    void reserve(int new_mSize);
    void clear();

    //Insertion Algorithms
    void insert_fFit(process * p);
    void insert_nFit(process * p);
    void insert_bFit(process * p);

    //Freeing memory
    void free_memory(process * p);

    //Functionality
    void print();
};

void reserve(int new_mSize)
{
  this->clear();

  totalMem = new char[new_mSize];
  m_size = new_mSize;
}

void clear()
{
  delete[] totalMem;
  m_size = 0;
}

void print()
{
  

}


#endif