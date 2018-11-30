#ifndef MEMMANAGER_H
#define MEMMANAGER_H

#include <vector>
#include <queue>
#include <fstream>
#include "Memory.h"
#include "Process.h"
#include "Algorithm.h"

using namespace std;

class MemManager {
  private:
    vector<Process> active_processes;
    vector<Process> blocked_processed;
    queue<Process> ready_processes; 

    Memory * main_memory;
    Algorithm current_alg;

    int process_clock;

    //Mutators
    void reset_clock();
    void set_algorithm(Algorithm alg);
    void set_total_mem(int total_size);

  public:
    MemManager() {main_memory = new Memory; process_clock = 0; current_alg = firstFit;}
    ~MemManager() {delete main_memory;}

    /*---Main Functionality---*/
    void memload(string fname);
    void memrun(string fname);
    void memstep();
    void memreset();
    void memalg(Algorithm alg) {this->set_algorithm(alg);}
    void memset(int m_size) {this->set_total_mem(m_size);}
    void memview() {main_memory->map();}    

    /*---Helper Functions---*/

    //Allocates space for process in Memory class 
    void allocate(Process * p);

    //Frees process from Memory class
    void free(Process * p);

    //Checks process vector to see if any processes need to be freed, and if
    //so returns a pointer to the process. If none need freed then returns nullptr. 
    Process * need_to_free();

};

#endif