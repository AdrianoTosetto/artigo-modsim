#include <iostream>
#include <vector>
#include "cellular_automata.h"

template <typename T>
class Cell {
    T _data;
};


CellularAutomaton::CellularAutomaton(int rows, int cols): _rows(rows), _cols(cols) {
    _grid.assign(_rows * _cols, 0);
}
void CellularAutomaton::display() {
    for(int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            std::cout << _grid[(i * _cols)  + j] << " ";
        }
        std::cout << "\n";
    }
}
void CellularAutomaton::update() {

}

void CellularAutomaton::simulate(int steps) {
    for (int i = 0; i < steps; i++) {
        this->update();
    }
    this->display();
}
