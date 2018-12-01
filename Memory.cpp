#include "Memory.h"

Memory::Memory() 
{
  m_size = DEFAULT_SIZE; 
  totalMem = new bool[m_size]();

  index_last_allocated = 0;
}

Memory::Memory(int mem_size) 
{
  m_size = mem_size; 
  totalMem = new bool[m_size](); 
  
  index_last_allocated = 0;
}

void Memory::reserve(int new_mSize)
{
  this->clear();

  totalMem = new bool[new_mSize]();
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

  int index = 0;
  int start_block;
  int displacement = 0;
  bool fully_mapped = false;
  
  while(!fully_mapped){
    displacement = 0;
    start_block = index;

    if(totalMem[index] == false){
      //Find empty blocks after index
      while(totalMem[index] == false && index < m_size){
        index++;
      }

       displacement = index - start_block;
       cout << "[E:" << displacement << "],";
    }
    else{ 
      //Find full blocks after index
      while(totalMem[index] == true && index < m_size){
        index++;
      }
       
       displacement = index - start_block;
       cout << "[F:" << displacement << "],";
    }
        
    if(index == m_size)
        fully_mapped = true;

  } 

  cout << endl;  
}
