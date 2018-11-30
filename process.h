#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <fstream>

class process
{
  Private:

    int data_size;
    int arrival_time;
    int remaining_time;
    int starting_mem_addr;
  
  Public:
    process();
    process(int d_size, arr_time, r_time, index);
    
    //Accesors
    void size() {return data_size;}
    void arrives() {return arrival_time;}
    void remaining() {return remaining_time;}
    void memAddr() {return starting_mem_addr;}
    
    //Mutators
    void set_size(int size);
    void set_arrival(int a_time);
    void update_time(int r_time);
    void set_addr(int index);
    
};

#endif