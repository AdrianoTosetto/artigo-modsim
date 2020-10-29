#ifndef HOST_PATHOGEN_H
#define HOST_PATHOGEN_H

#include <vector>
#include "cellular_automata.h"

template<typename T>
class HostPathogen: public CellularAutomaton<T>
{

public:
    HostPathogen(int rows, int cols);
    ~HostPathogen();
    virtual void update();
    int aliveCells();
    void births();
    void births2();
    void test();

    std::vector<uint32_t>& get__timestamps() const;
    std::vector<uint32_t>& get__aliveCells() const;

private:

    /*
        for debug purposes and for data generation
    */

    mutable std::vector<uint32_t> __timestamps;
    mutable std::vector<uint32_t> __aliveCells;

    /*
        end debug
    */

};

template class HostPathogen<HostPathogenCell>;

#endif