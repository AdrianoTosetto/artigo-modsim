#ifndef CELULLAR_AUTOMATON_H
#define CELULLAR_AUTOMATON_H
#include <vector>
#include "host_pathgen_cell.h"

enum class NDIRECTION {
  TOP,
  TOP_RIGHT,
  RIGHT,
  BOTTOM_RIGHT,
  BOTTOM,
  BOTTOM_LEFT,
  LEFT,
  TOP_LEFT
};

template<typename T>
class CellularAutomaton {
 public:
    CellularAutomaton(int rows, int cols);
    void display();
    virtual void update();
    virtual void simulate(uint32_t);
    T& getCellRef(uint32_t, uint32_t);
    T getCellValue(uint32_t, uint32_t) const;

    std::vector<T> leftNeighbors(uint32_t, uint32_t,uint32_t) const;
    std::vector<T> rightNeighbors(uint32_t, uint32_t,uint32_t) const;
    std::vector<T> topNeighbors(uint32_t, uint32_t,uint32_t) const;
    std::vector<T> bottomNeighbors(uint32_t, uint32_t,uint32_t) const;
    std::vector<T> getNeighbors(uint32_t, uint32_t, NDIRECTION, uint32_t radius = 1) const;
    std::vector<T> getMooreNeighborhood(uint32_t, uint32_t, uint32_t) const;

 protected:
    std::vector<T> _grid;
    int _rows;
    int _cols;
    uint32_t _timestamp = 0;
};

template class CellularAutomaton<int>;
template class CellularAutomaton<HostPathogenCell>;

#endif