#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <fstream>

class Process
{
  private:

    int data_size;
    int arrival_time;
    int remaining_time;
    int starting_mem_addr;
  
  public:
    Process();
    Process(int d_size, int arr_time, int r_time, int index);
    
    //Accesors
    int size() {return data_size;}
    int arrives() {return arrival_time;}
    int remaining() {return remaining_time;}
    int memAddr() {return starting_mem_addr;}
    
    //Mutators
    void set_size(int size);
    void set_arrival(int a_time);
    void update_time(int r_time);
    void set_addr(int index);
    
};


#endif