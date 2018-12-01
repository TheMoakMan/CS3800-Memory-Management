#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <fstream>

using namespace std;

class Process
{
  private:

    int data_size;
    int arrival_time;
    int exit_time;
    int starting_mem_addr;
  
  public:
    Process();
    Process(int d_size, int arr_time, int e_time);
    
    //Accesors
    int size() {return data_size;}
    int arrives() {return arrival_time;}
    int exits_at() {return exit_time;}
    int memAddr() {return starting_mem_addr;}
    
    //Mutators
    void set_size(int size);
    void set_arrival(int a_time);
    void set_exit(int e_time);
    void set_addr(int index);

    Process & operator= (Process rhs);

    void print_attributes();
    
};

    //Comparator between two Process objects to determine which has
    //a lower arrival time. Built to be used with std::sort
    bool arrives_first(Process p1, Process p2);

    //Comparator betwen two Process objects to determine which has
    //a lower exit time. Built to be used with std::sort
    bool exits_first(Process p1, Process p2);

    bool smaller_mem(Process p1, Process p2);


#endif