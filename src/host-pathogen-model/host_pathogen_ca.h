#ifndef HOST_PATHOGEN_H
#define HOST_PATHOGEN_H

#include <vector>
#include "cellular_automata.h"

template<typename T = HostPathogenCell>
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
    std::pair<double, double> calcInfectionProbability(uint32_t row, uint32_t col) const;

    std::vector<uint32_t>& get__timestamps() const;
    std::vector<uint32_t>& get__aliveCellsPerTimestamp() const;

    std::pair<uint32_t, uint32_t> countInfectedsInNeighborhood(const std::vector<T> neighbors) const;

private:
    const double deathProbability = 0.04 / 100; // 0.04% of dying

    void iterate();

    bool born(T& cell);
    bool death(T& cell);

    void updatePathogensStatusInCell(T&cell);
    void updatePathogensStatusInCell(uint32_t, uint32_t);
    /*
        for debug purposes and for data generation
    */

    mutable std::vector<uint32_t> __timestamps;
    mutable std::vector<uint32_t> __aliveCellsPerTimestamp;
    mutable uint32_t __aliveCells;

    /*
        end debug
    */

};

template class HostPathogen<HostPathogenCell>;

#endif