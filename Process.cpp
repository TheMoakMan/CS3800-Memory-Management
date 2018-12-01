#include "Process.h"

Process::Process()
{
  data_size = 0;
  arrival_time = 1;
  exit_time = 1;
  starting_mem_addr = 0;
}

Process::Process(int d_size, int arr_time, int e_time)
{
  data_size = d_size;
  arrival_time = arr_time;
  exit_time = e_time;
}

void Process::set_size(int size)
{
  data_size = size;
}

void Process::set_arrival(int a_time)
{
  arrival_time = a_time;
}

void Process::set_exit(int e_time)
{
  exit_time = e_time;
}

void Process::set_addr(int index)
{
  starting_mem_addr = index;
}

bool arrives_first(Process p1, Process p2)
{
  return (p1.arrives() < p2.arrives());
}

bool exits_first(Process p1, Process p2)
{
  return (p1.exits_at() < p2.exits_at());
}

bool smaller_mem(Process p1, Process p2)
{
  return (p1.size() < p2.size());
}
    
Process& Process::operator= (Process rhs)
{
  data_size = rhs.data_size;
  arrival_time = rhs.arrival_time;
  exit_time = rhs.exit_time;
  starting_mem_addr = rhs.starting_mem_addr;
}

void Process::print_attributes()
{
  cout << "Size: " << data_size << " Arr: " << arrival_time
       << " Exit: " << exit_time;
}