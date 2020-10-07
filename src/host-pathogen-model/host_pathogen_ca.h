#ifndef HOST_PATHOGEN_H
#define HOST_PATHOGEN_H
#include "cellular_automata.h"

class HostPathogen: public CellularAutomaton
{

public:
    HostPathogen(int rows, int cols);
    ~HostPathogen();
    virtual void update();
    int aliveCells();
    void births();
    void test();
};

#endif