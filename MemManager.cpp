#include "MemManager.h"

void MemManager::reset_clock()
{


}

void MemManager::set_algorithm(Algorithm alg)
{
  current_alg = alg; 
}

void MemManager::set_total_mem(int total_size)
{
  main_memory->reserve(total_size);
}

void MemManager::memload(string fname)
{
  ifstream fin;
  string atts;
  vector<int> attributes;

  //Not checking if file succesfully opens at this time.
  fin.open(fname);
  
  while(getline(fin, atts, '\n')){
    attributes.clear();
    istringstream attrStream(atts);  
    string str;

    while(getline(attrStream, str, ' ')){
      if(str != "")
        attributes.push_back(stoi(str));  
    }

    Process temp_p;
    temp_p.set_arrival(attributes[0]);
    temp_p.set_size(attributes[1]);
    temp_p.set_exit(attributes[0] + attributes[2]);

    ready_processes.push_back(temp_p);
  }
  
  fin.close();
  print_Pvector(ready_processes);
  
}

void MemManager::memrun(string fname)
{


}

void MemManager::memstep()
{
  


}

void MemManager::memreset()
{
  active_processes.clear();
  blocked_processes.clear();
  ready_processes.clear();

  main_memory->reserve(DEFAULT_SIZE);
  
  this->reset_clock();
  this->set_algorithm(DEFAULT_ALG);
}

void MemManager::allocate(Process * p)
{


}

void MemManager::free(Process * p)
{


}

Process * MemManager::need_to_free()
{


}

void MemManager::sort_start_time(vector<Process> & v)
{
  for(int i = 1; i < v.size(); i++){
    Process index = v[i];
    int j = i;

    while(j > 0 && !arrives_first(v[j-1], index)){
      v[j] = v[j-1];
      j--;  
    }
    
    v[j] = index;
  }
}


void MemManager::sort_exit_time(vector<Process> & v)
{
  for(int i = 1; i < v.size(); i++){
    Process index = v[i];
    int j = i;

    while(j > 0 && !exits_first(v[j-1], index)){
      v[j] = v[j-1];
      j--;  
    }
    
    v[j] = index;
  }
}

void MemManager::print_Pvector(vector<Process> v)
{
  for(int i = 0; i < v.size(); i++){
    cout << "Process " << i << ": ";
    v[i].print_attributes();
    cout << endl; 
  }
}