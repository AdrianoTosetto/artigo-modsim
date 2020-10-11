#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "host_pathogen_ca.h"

template<typename T>
HostPathogen<T>::HostPathogen(int rows, int cols): CellularAutomaton<T>(rows, cols) {
    this->_grid[0] = 1;
    this->_grid[2] = 1;
    this->_grid[4] = 1;
    this->_grid[2] = 1;
    this->_grid[9] = 1;
    this->_grid[3] = 1;
    this->_grid[89] = 1;
    this->_grid[100] = 1;
    this->_grid[200] = 1;
    this->_grid[400] = 1;
    this->_grid[300] = 1;
}

template<typename T>
HostPathogen<T>::~HostPathogen() {}

template<typename T>
int HostPathogen<T>::aliveCells() {
    int aliveCells = 0;
    for (int cellValue : this->_grid)
        if (cellValue != 0)
            aliveCells++;

    return aliveCells;
}

template<typename T>
void HostPathogen<T>::births() {
    int _rows = this->_rows;
    int _cols = this->_cols;

    srand((int)time(0));
    std::cout << "cols  = " << _cols << " rows = " << _rows << "\n";
    std::vector<int> nextGrid(this->_grid);


    for(int i = 0; i < _rows; i++) {
        for(int j = 0; j < _cols; j++) {
            if (this->_grid[(i*_cols) + j] == 0) {
                double prob = (double)100 * aliveCells() / (_cols * _rows);
                //std::cout << "alive prob = " << prob << "\n";
                int draw = (rand() % 100) + 1;
                if (draw <= prob) {
                    nextGrid[(i*_cols) + j] = 1;
                }
            }
            if (this->_grid[(i*_cols) + j] == 1) {
                int prob = (rand() % 100) + 1;
                if (prob <= 4) {
                    nextGrid[(i*_cols) + j] = 0;
                }
            }
        }
    }
    this->_grid = nextGrid;
    /*for (int& cellValue : _grid) {
        if (cellValue == 0) {
            int prob = (rand() % 100) + 1;
            if (prob >= 98) {
                cellValue = 1;
            }
        }
    }*/
}

template<typename T>
void HostPathogen<T>::update() {
    this->births();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
    this->display();
    std::cout << "============================\n";
}

template class HostPathogen<int>;