#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <random>
#include "host_pathogen_ca.h"
#include "host_pathgen_cell.h"
#include "random.h"
#include "matplotlibcpp.h"

template<typename T>
HostPathogen<T>::HostPathogen(int rows, int cols): CellularAutomaton<T>(rows, cols) {
    this->_grid.assign(rows*cols, HostPathogenCell());
    for (auto i = 0; i < 32; i++)
        this->_grid[i].setIsAlive(true);
    /*this->_grid[0].setIsAlive(true);
    this->_grid[2].setIsAlive(true);
    this->_grid[4].setIsAlive(true);
    this->_grid[2].setIsAlive(true);
    this->_grid[9].setIsAlive(true);
    this->_grid[3].setIsAlive(true);
    this->_grid[50].setIsAlive(true);
    this->_grid[89].setIsAlive(true);
    this->_grid[100].setIsAlive(true);
    this->_grid[105].setIsAlive(true);
    this->_grid[109].setIsAlive(true);
    this->_grid[117].setIsAlive(true);
    this->_grid[120].setIsAlive(true);
    this->_grid[123].setIsAlive(true);
    this->_grid[200].setIsAlive(true);
    this->_grid[210].setIsAlive(true);*/
}

template<typename T>
HostPathogen<T>::~HostPathogen() {}

template<typename T>
int HostPathogen<T>::aliveCells() {
    int aliveCells = 0;
    for (auto cell : this->_grid)
        if (cell.isAlive())
            aliveCells++;

    return aliveCells;
}

template<typename T>
std::vector<uint32_t>& HostPathogen<T>::get__timestamps() const {
    return this->__timestamps;
}

template<typename T>
std::vector<uint32_t>& HostPathogen<T>::get__aliveCells() const {
    return this->__aliveCells;
}

template<typename T>
void HostPathogen<T>::births() {
    uint32_t _rows = this->_rows;
    uint32_t _cols = this->_cols;
    uint32_t totalSites = _rows * _cols;
    uint32_t aliveIndividuals = aliveCells();
    uint32_t emptySites = totalSites - aliveIndividuals;
   
    std::cout << "a = " << aliveIndividuals << " - " << emptySites << std::endl;
    
    std::vector<HostPathogenCell> nextGrid(this->_grid);

    this->__aliveCells.push_back(this->aliveCells());

    for (auto i = 0; i < _rows; i++) {
        for (auto j = 0; j < _cols; j++) {
            if (!this->_grid[(i*_cols) + j].isAlive()) {

                double newIndividuals = 0.005 * aliveIndividuals * (1 - (aliveIndividuals / totalSites));  
                double prob = newIndividuals / emptySites;
                double draw = randomProbability();

                if (draw <= prob) {
                    //std::cout<< "new born" << std::endl;
                    nextGrid[(i*_cols) + j].setIsAlive(true);
                }
            }
            else if (this->_grid[(i*_cols) + j].isAlive()) {
                double draw = randomProbability();
                if (draw <= 0.0004) {
                    //std::cout<< "new death" << std::endl;
                    nextGrid[(i*_cols) + j].setIsAlive(false);
                }
            }
        }
    }
    this->_grid = nextGrid;
}

template<typename T>
void HostPathogen<T>::births2() {
    uint32_t _rows = this->_rows;
    uint32_t _cols = this->_cols;
    uint32_t totalSites = _rows * _cols;
    uint32_t aliveIndividuals = aliveCells();
    uint32_t emptySites = totalSites - aliveIndividuals;
    if (this->_timestamp % 100 == 0)
        std::cout << "a = " << aliveIndividuals << " - " << emptySites << std::endl;
    
    std::vector<HostPathogenCell> nextGrid(this->_grid);

    this->__aliveCells.push_back(this->aliveCells());
    for (auto i = 0; i < this->_grid.size(); i++) {
        if (!this->_grid[i].isAlive()) {

            double newIndividuals = 0.005 * aliveIndividuals * (1 - (aliveIndividuals / totalSites));  
            //std::cout << newIndividuals << " n" << std::endl;
            
            double prob = newIndividuals / emptySites;
            double draw = randomProbability();
            //std::cout << draw << " d" << std::endl;
            if (draw <= prob) {
                //std::cout<< "new born" << std::endl;
                nextGrid[i].setIsAlive(true);
            }
        }
        if (this->_grid[i].isAlive()) {
            double draw = randomProbability();
            //std::cout << draw << std::endl;
            if (draw <= 0.0004) {
                //std::cout<< "new death" << std::endl;
                nextGrid[i].setIsAlive(false);
            }
        }
    }
    this->_grid = nextGrid;
}


template<typename T>
void HostPathogen<T>::update() {
    //using namespace std::chrono_literals;
    this->__timestamps.push_back(this->_timestamp);
    //this->__aliveCells.push_back(this->aliveCells());
    this->births2();
    //std::this_thread::sleep_for(1s);
    //this->display();
    this->_timestamp++;
    //std::cout << "============================\n";
}

template class HostPathogen<HostPathogenCell>;
