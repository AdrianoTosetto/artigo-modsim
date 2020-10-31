#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <random>
#include <array>

#include "host_pathogen_ca.h"
#include "host_pathgen_cell.h"
#include "random.h"
#include "matplotlibcpp.h"

template<typename T>
HostPathogen<T>::HostPathogen(int rows, int cols): CellularAutomaton<T>(rows, cols) {
    this->_grid.assign(rows*cols, HostPathogenCell());
    for (auto i = 0; i < 32; i++);
        //this->_grid[i].setIsAlive(true);
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
std::vector<uint32_t>& HostPathogen<T>::get__aliveCellsPerTimestamp() const {
    return this->__aliveCellsPerTimestamp;
}

template<typename T>
bool HostPathogen<T>::death(T& cell) {
    double draw = randomProbability();
    if (draw <= deathProbability) {
        cell.setIsAlive(false);
        return true;
    }
    return false;
}

template<typename T>
bool HostPathogen<T>::born(T& cell) {

    uint32_t totalSites = this->_rows * this->_cols;
    uint32_t aliveIndividuals = this->__aliveCells;
    uint32_t emptySites = totalSites - aliveIndividuals;

    //std::cout << "a = " << aliveIndividuals << " - " << emptySites << std::endl;

    double controlFactor = static_cast<double>(aliveIndividuals) /
            static_cast<double>(totalSites);
    double newIndividuals = 0.005 * aliveIndividuals * (1 - controlFactor);  
    
    double prob = newIndividuals / emptySites;
    double draw = randomProbability();

    if (draw <= prob) {
        cell.setIsAlive(true);
        return true;
    }
    return false;
}

template<typename T>
void HostPathogen<T>::updatePathogensStatusInCell(T& cell) {

}

template<typename T>
void HostPathogen<T>::updatePathogensStatusInCell(uint32_t row, uint32_t col) {
    
}

template<typename T>
void HostPathogen<T>::iterate() {
    std::vector<HostPathogenCell> nextGrid(this->_grid);
    this->__aliveCells = this->aliveCells();
    this->__aliveCellsPerTimestamp.push_back(this->__aliveCells);

    for (auto i = 0; i < this->_rows; i++) {
       for (auto j = 0; j < this->_cols; j++) {
           auto& cell = nextGrid[(i*this->_cols) + j];

           if (this->getCellValue(i, j).isAlive()) {
               // if cell did not die in the death stage so it can be infected
                if (!death(cell)) {
                    auto infectionProbability = calcInfectionProbability(i, j);
                }

           } else {
                born(cell);
           }
       }
    }
    std::cout << this->__aliveCellsPerTimestamp.size() << std::endl;
    this->_grid = nextGrid;
}


template<typename T>
std::pair<uint32_t, uint32_t> HostPathogen<T>::countInfectedsInNeighborhood(
    const std::vector<T> neighbors) const {

    uint32_t counterA = 0;
    uint32_t counterB = 0;
    std::pair<uint32_t, uint32_t> ret;

    for (auto& e: neighbors) {
        if (e.infectedByA())
            counterA++;
        if (e.infectedByB())
            counterB++;
    }

    ret.first = counterA;
    ret.second = counterB;

    return ret;
}

template<typename T>
std::pair<double, double> HostPathogen<T>::calcInfectionProbability(
    uint32_t row,  uint32_t col) const {

    std::pair<double, double> ret;

    const double Wa = 0.038461538;
    const double Wb = 0.019230769;
    const double Wc = 0.0096153846;
    const double Wd = 0.0048076923;
    const double TcA = 1;
    const double TcB = TcA*1.5;

    auto cell = this->getCellValue(row, col);
    auto radiusOneNeighbors  = this->getMooreNeighborhood(row, col, 1, false);
    auto radiusTwoNeighbors  = this->getMooreNeighborhood(row, col, 2, false);
    auto radiusThreeNeigbors = this->getMooreNeighborhood(row, col, 3, false);
    auto radiusFoursNeigbors = this->getMooreNeighborhood(row, col, 3, false);

    auto a = countInfectedsInNeighborhood(radiusOneNeighbors);
    auto b = countInfectedsInNeighborhood(radiusTwoNeighbors);
    auto c = countInfectedsInNeighborhood(radiusThreeNeigbors);
    auto d = countInfectedsInNeighborhood(radiusFoursNeigbors);


    // std::cout << "a = " << a.first << std::endl;
    // std::cout << "b = " << b.first << std::endl;
    // std::cout << "c = " << c.first << std::endl;
    // std::cout << "d = " << d.first << std::endl;

    auto term1A = std::pow((1-Wa), a.first);
    auto term2A = std::pow((1-Wb), b.first);
    auto term3A = std::pow((1-Wc), c.first);
    auto term4A = std::pow((1-Wd), d.first);

    auto term1B = std::pow((1-Wa), a.second);
    auto term2B = std::pow((1-Wb), b.second);
    auto term3B = std::pow((1-Wc), c.second);
    auto term4B = std::pow((1-Wd), d.second);

    double probOfInfectionByA = TcA*(1 - (term1A * term2A * term3A * term4A));
    double probOfInfectionByB = TcB*(1 - (term1B * term2B * term3B * term4B));

    ret.first = probOfInfectionByA;
    ret.second = probOfInfectionByB;

    return ret;
}


template<typename T>
void HostPathogen<T>::update() {
    std::cout << "timestamp = " << this->_timestamp << std::endl;
    this->__timestamps.push_back(this->_timestamp);
    this->iterate();
    this->_timestamp++;
}
// UNSED CODE ============================================================================== UNSED CODE
// template<typename T>
// void HostPathogen<T>::births() {
//     uint32_t _rows = this->_rows;
//     uint32_t _cols = this->_cols;
//     uint32_t totalSites = _rows * _cols;
//     uint32_t aliveIndividuals = aliveCells();
//     uint32_t emptySites = totalSites - aliveIndividuals;
   
//     std::cout << "a = " << aliveIndividuals << " - " << emptySites << std::endl;
    
//     std::vector<HostPathogenCell> nextGrid(this->_grid);

//     this->__aliveCellsPerTimestamp.push_back(this->aliveCells());

//     for (auto i = 0; i < _rows; i++) {
//         for (auto j = 0; j < _cols; j++) {
//             if (!this->getCellValue(i, j).isAlive()) {

//                 double controlFactor = static_cast<double>(aliveIndividuals) /
//                      static_cast<double>(totalSites);
//                 double newIndividuals = 0.005 * aliveIndividuals * (1 - controlFactor);  
                
//                 double prob = newIndividuals / emptySites;
//                 double draw = randomProbability();

//                 if (draw <= prob) {
//                     nextGrid[(i*_cols) + j].setIsAlive(true);
//                 }
//             } else if (this->_grid[(i*_cols) + j].isAlive()) {
//                 double draw = randomProbability();
//                 if (draw <= 0.0004) {
//                     //std::cout<< "new death" << std::endl;
//                     nextGrid[(i*_cols) + j].setIsAlive(false);
//                 }
//             }
//         }
//     }
//     this->_grid = nextGrid;
// }
//template class HostPathogen<HostPathogenCell>;
