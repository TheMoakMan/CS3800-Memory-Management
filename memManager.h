#ifndef MEMMANAGER_H
#define MEMMANAGER_H

#include <vector>
#include "memory.h"
#include "process.h"
#include "Algorithm.h"

class MemManager {
  private:
    vector active_processes;
    Memory ram;
    Algortihm currentAlg;
    
  public:
    void allocate(Algorithm alg, process * p);
    void free(process * p);
};

#endif