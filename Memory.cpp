#include "Memory.h"

void Memory::reserve(int new_mSize)
{
  this->clear();

  totalMem = new char[new_mSize];
  m_size = new_mSize;
}

void Memory::clear()
{
  delete[] totalMem;
  m_size = 0;
}


void Memory::free_memory(Process * p)
{



}

bool Memory::insert_fFit(Process * p)
{


}
  
bool Memory::insert_nFit(Process * p)
{



}

bool Memory::insert_bFit(Process * p)
{


}
    
int Memory::empty_block_size(int index)
{

}

int Memory::next_empty(int index)
{


}

void Memory::map()
{


}
