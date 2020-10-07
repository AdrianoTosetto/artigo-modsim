#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include "host_pathogen_ca.h"

HostPathogen::HostPathogen(int rows, int cols): CellularAutomaton(rows, cols) {
    _grid[0] = 1;
    _grid[2] = 1;
    _grid[4] = 1;
    _grid[2] = 1;
    _grid[9] = 1;
    _grid[3] = 1;
    _grid[89] = 1;
    _grid[100] = 1;
    _grid[200] = 1;
    _grid[400] = 1;
    _grid[300] = 1;
}

HostPathogen::~HostPathogen()
{
}
int HostPathogen::aliveCells() {
    int aliveCells = 0;
    for (int cellValue : _grid)
        if (cellValue != 0)
            aliveCells++;

    return aliveCells;
}

void HostPathogen::births() {
    srand((int)time(0));
    std::cout << "cols  = " << _cols << " rows = " << _rows << "\n";
    std::vector<int> nextGrid(_grid);
    for(int i = 0; i < _rows; i++) {
        for(int j = 0; j < _cols; j++) {
            if (_grid[(i*_cols) + j] == 0) {
                double prob = (double)100 * aliveCells() / (_cols * _rows);
                //std::cout << "alive prob = " << prob << "\n";
                int draw = (rand() % 100) + 1;
                if (draw <= prob) {
                    nextGrid[(i*_cols) + j] = 1;
                }
            }
            if (_grid[(i*_cols) + j] == 1) {
                int prob = (rand() % 100) + 1;
                if (prob <= 4) {
                    nextGrid[(i*_cols) + j] = 0;
                }
            }
        }
    }
    _grid = nextGrid;
    /*for (int& cellValue : _grid) {
        if (cellValue == 0) {
            int prob = (rand() % 100) + 1;
            if (prob >= 98) {
                cellValue = 1;
            }
        }
    }*/
}

void HostPathogen::test() {
    std::cout << "test";
}

void HostPathogen::update() {
    births();
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(3s);
    display();
    std::cout << "============================\n";
}