#ifndef CELULLAR_AUTOMATON_H
#define CELULLAR_AUTOMATON_H
#include <vector>

class CellularAutomaton {
 public:
    CellularAutomaton(int rows, int cols);
    void display();
    virtual void update();
    void simulate(int steps);
 protected:
    std::vector<int> _grid;
    int _rows;
    int _cols;
};

#endif