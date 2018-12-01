#include "MemManager.h"

void MemManager::reset_clock()
{
  process_clock = 0;
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
  
  sort_start_time(ready_processes);
}

void MemManager::memrun(string fname)
{
  /*---READ FROM FILE AND LOAD---*/ 
  ifstream fin;
  string atts;
  string alg, size;
  vector<int> attributes;

  //Not checking if file succesfully opens at this time.
  fin.open(fname);
  
  //Get algorithm and size before loading. HAS WITH GETLINE
  fin >> alg;
  fin >> size; 

  memalg(stringToAlg(alg));
  memset(stoi(size));

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
  
  sort_start_time(ready_processes);

  /*---Mem Step through entire program---*/

}

void MemManager::memstep(int num_steps)
{
  if(num_steps != -99 && num_steps > 0){
    for(int i = 0; i < num_steps; i++){
      memstep_help();
    }
  } 
  else if(num_steps = -99){
    
  }

}

void MemManager::memstep_help()
{
  //Increment process clock
  process_clock++;
  
  //Check if any processes need freed.
    while(active_processes.size() > 0 && active_processes[0].exits_at() == process_clock){
      //Remove any processes from active_processes vector if need be.
      main_memory->free_memory(active_processes[0]);
      active_processes.erase(active_processes.begin());
    }  

  //Check if any blocked processes can be allocated
    while(blocked_processes.size() > 0 && main_memory->alg_function(current_alg, blocked_processes[0])){
      
      //If processes succesfully allocated then move to active and remove from blocked
      active_processes.push_back(blocked_processes[0]);
      blocked_processes.erase(blocked_processes.begin());

    //If unsucessfully allocated, do nothing beause process stays in queue.
    }


  //Check if any new processes need allocated
    while(ready_processes.size() > 0 && (ready_processes[0].arrives() == process_clock)){

        if(!(main_memory->alg_function(current_alg, ready_processes[0]))){
          cout << "Unsuccesful insertion: moving process to blocked state..." << endl;
          //If insertion unsucessful then add process to blocked processes.
          blocked_processes.push_back(ready_processes[0]);
        }
        else{
          //If insertion is succesful then move process to active_processes
          active_processes.push_back(ready_processes[0]);
        }  
        
        //Remove Process from ready vector
        ready_processes.erase(ready_processes.begin());
    }
  

  //Sort active and blocked vectors
  if(active_processes.size() > 1)
    sort_exit_time(active_processes);
  if(blocked_processes.size() > 1)
    sort_smallest_size(blocked_processes);
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

void MemManager::sort_smallest_size(vector<Process> & v)
{
  for(int i = 1; i < v.size(); i++){
    Process index = v[i];
    int j = i;

    while(j > 0 && !smaller_mem(v[j-1], index)){
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


Algorithm stringToAlg(string & str)
{
  Algorithm alg;

  if(str == "first")
    alg = firstFit;
  else if(str == "next")
    alg = nextFit;
  else if(str == "best")
    alg = bestFit;
}