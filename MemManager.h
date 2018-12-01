#ifndef MEMMANAGER_H
#define MEMMANAGER_H

#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
#include "Memory.h"
#include "Process.h"
#include "Algorithm.h"

using namespace std;

const Algorithm DEFAULT_ALG = firstFit;

class MemManager {
  private:
    vector<Process> active_processes;
    vector<Process> blocked_processes;
    vector<Process> ready_processes; 

    Memory * main_memory;
    Algorithm current_alg;

    int process_clock;

    //Mutators
    void reset_clock();
    void set_algorithm(Algorithm alg);
    void set_total_mem(int total_size);

  public:
    MemManager() {main_memory = new Memory; process_clock = 0; current_alg = DEFAULT_ALG;}
    ~MemManager() {delete main_memory;}

    /*---Main Functionality---*/
    void memload(string fname);
    void memrun(string fname);
    void memstep(int num_steps);
    void memreset();
    void memalg(Algorithm alg) {this->set_algorithm(alg);}
    void memset(int m_size) {this->set_total_mem(m_size);}
    void memview() {main_memory->map();}    

    /*---Helper Functions---*/
    
    void memstep_help();

    //Sorts a vector of processes by the starting time.
    void sort_start_time(vector<Process> & processes);

    //Sorts a vector of processes by the exit time.
    void sort_exit_time(vector<Process> & processes);

    //Sorts a vector of processes by the shortest memory size
    void sort_smallest_size(vector<Process> & v);
    
    void print_Pvector(vector<Process> v);

};

Algorithm stringToAlg(string & str);

#endif