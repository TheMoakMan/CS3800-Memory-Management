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
  index_last_allocated = 0;
}

bool Memory::full()
{
  int i = 0;
  while(i < m_size && totalMem[i] == false){
    i++;  
  } 

  if(i = m_size)
    return true;

  return false;

}

void Memory::free_memory(Process & p)
{
  //Start at index of memory address of process and "deallocate" bits until block
  //end of block but check for array bounds.
  int i = p.memAddr();

  int end_index = p.memAddr() + p.size() - 1;

  while(i <= end_index && end_index < m_size && totalMem[i] == true){
    totalMem[i] = false;
    i++;    
  }
}

void Memory::allocate(Process & p, int index)
{
  int end = index + p.size();
  
  index_last_allocated = index;
  p.set_addr(index);

  while(index < end && end < m_size && totalMem[index] == false)
  {
    totalMem[index] = true;
    index++;
  }

}

bool Memory::insert_fFit(Process & p)
{
  bool is_inserted = false;
  int index = 0;
  int next_open;

  while(!is_inserted && index < m_size)
  {    

    //Find first open memory block that will fit process.
    next_open = next_empty(index);

    if(empty_block_size(next_open) > 0 && p.size() <= empty_block_size(next_open)){
      allocate(p, index);
      is_inserted = true;
    }
    else if(empty_block_size(next_open) == 0 || p.size() > empty_block_size(next_open))
      index = m_size;
    
  }

  return is_inserted;
}
  
bool Memory::insert_nFit(Process & p)
{

  bool is_inserted = false;
  bool halt = false;
  int index = index_last_allocated;
  int next_open;

  while(!is_inserted && !halt && index < m_size)
  {    

    //Find first open memory block that will fit process.
    next_open = next_empty(index);

    if(empty_block_size(next_open) > 0 && p.size() <= empty_block_size(next_open)){
      allocate(p, index);
      is_inserted = true;
    }
    else if(empty_block_size(next_open) == 0 || p.size() > empty_block_size(next_open))
      halt = true;

    //If index reaches m_size then loop back around.
    if(index = m_size)
      index_last_allocated = index = 0;
    
  }

  return is_inserted;

}

bool Memory::insert_bFit(Process & p)
{
    bool is_inserted = false;
    bool has_fit = false;
    int index = 0;
    int start_best_block;
    int next_open;
    int size_next_open;

    start_best_block = next_empty(index);
    next_open = start_best_block;
   
    while(start_best_block != -1 && index < m_size){
      size_next_open = empty_block_size(next_open);
       
      //Checks if next block can fit process. 
      if(size_next_open > 0 && p.size() <= size_next_open){
      has_fit = true;

        //Checks if next block is closer to p.size() then the best block so far. 
        if(next_open != start_best_block && size_next_open - p.size() < empty_block_size(start_best_block) - p.size()){
          start_best_block = next_open;
        }
      }
      
      index += size_next_open;
      //Increment index and check another block
      next_open = next_empty(index);
      
      //When at end of memory, process results. 
      if(next_open == -1){
        if(has_fit)
          allocate(p, start_best_block);
          is_inserted = true;
        }
   
    }

    return is_inserted;
}

 bool Memory::alg_function(Algorithm alg, Process & p)
 {
    if(alg == firstFit)
      return this->insert_fFit(p);
    else if(alg == nextFit)
      return this->insert_nFit(p);
    else if(alg == bestFit)
      return this->insert_bFit(p);
 }

int Memory::empty_block_size(int index)
{
  if(index == -1)
    return 0;

  int count = 0;
  while(index < m_size && totalMem[index] == false){
    count++;
    index++;
  }
  
  return count;
}

int Memory::next_empty(int &index)
{

  if(index < m_size && totalMem[index] == false)
    return index;
  else{  
    while(index < m_size && totalMem[index] == true){
      index++;  
    }
    
    //If memory is full then throw a flag value.
    if(index == m_size)
      return -1;
    else
      return index;
  }

}

void Memory::map()
{

  int index = 0;
  int start_block;
  int displacement = 0;
  bool fully_mapped = false;
  
  cout << "|";
  for(int i = 0; i < m_size; i++){
     if(totalMem[i] == true)
       cout << "1|";
     else
       cout << "0|";
  }
  cout << endl;


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
