#ifndef CELULLAR_AUTOMATON_H
#define CELULLAR_AUTOMATON_H
#include <vector>

template<typename T = int>
class CellularAutomaton {
 public:
    CellularAutomaton(int rows, int cols);
    void display();
    virtual void update();
    void simulate(int steps);
 protected:
    std::vector<T> _grid;
    int _rows;
    int _cols;
};

template class CellularAutomaton<int>;

#endif