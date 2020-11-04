#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <random>
#include <array>
#include <algorithm>

#include "host_pathogen_ca.h"
#include "host_pathgen_cell.h"
#include "random.h"
#include "matplotlibcpp.h"


HostPathogen::HostPathogen(int rows, int cols): 
    CellularAutomaton<HostPathogenCell>(rows, cols) {
    //this->_grid.assign(rows*cols, HostPathogenCell());
}


HostPathogen::~HostPathogen() {}


int HostPathogen::aliveCells() {
    int aliveCells = 0;
    for (auto cell : this->grid.rawGridRef())
        if (cell.isAlive())
            aliveCells++;

    return aliveCells;
}

std::vector<uint32_t>& HostPathogen::get__timestamps() const {
    return this->__timestamps;
}

std::vector<uint32_t>& HostPathogen::get__aliveCellsPerTimestamp() const {
    return this->__aliveCellsPerTimestamp;
}

bool HostPathogen::death(HostPathogenCell& cell) {
    double draw = randomProbability();
    if (draw <= deathProbability) {
        cell.setIsAlive(false);
        return true;
    }
    return false;
}

void HostPathogen::setInitialConditions(uint32_t aliveHosts, uint32_t infectedByA, uint32_t infectedByB) {
    uint32_t i = 0;
    std::vector<uint32_t> indexes(_rows * _cols);
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::generate(indexes.begin(), indexes.end(), [&] {return i++;});
    std::shuffle(indexes.begin(), indexes.end(), std::default_random_engine(seed));

    for (auto i = 0; i < aliveHosts; i++) {
        auto randomIndex = indexes[i];
        grid[randomIndex].setIsAlive(true);
    }

    for (auto i = 0; i < infectedByA; i++) {
        auto randomIndex = indexes[i];
        grid[randomIndex].setInfectedByA();
    }

    for (auto i = infectedByA; i < infectedByA + infectedByB; i++) {
        auto randomIndex = indexes[i];
        grid[randomIndex].setInfectedByB();
    }
        
}

bool HostPathogen::born(HostPathogenCell& cell) {

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

void HostPathogen::updatePathogensStatusInCell(HostPathogenCell& cell) {

}

void HostPathogen::updatePathogensStatusInCell(uint32_t row, uint32_t col) {
    
}

void HostPathogen::iterate() {
    Grid<HostPathogenCell> nextGrid(this->grid);
    this->__aliveCells = this->aliveCells();
    this->__aliveCellsPerTimestamp.push_back(this->__aliveCells);

    for (auto i = 0; i < this->_rows; i++) {
       for (auto j = 0; j < this->_cols; j++) {
           auto& cell = nextGrid.getCellRef(i, j);

           if (grid.getCellRef(i, j).isAlive()) {
               // if cell did not die in the death stage so it can be infected
                if (death(cell))
                    continue;
                auto infectionProbability = calcInfectionProbability(i, j);
                double a = infectionProbability.first;
                double b = infectionProbability.second;

                double drawA = randomProbability();
                double drawB = randomProbability();
                //std::cout << "prob a " <<  a << std::endl;
                //std::cout << "prob b " <<  b << std::endl;
                if (drawA <= a) {
                    cell.setInfectedByA();
                }
                if (drawB <= b) {
                    cell.setInfectedByB();
                }
           } else {
                if (born(cell)) {
                }
           }
       }
    }
    //std::cout << this->__aliveCellsPerTimestamp.size() << std::endl;

    //std::this_thread::sleep_for(std::chrono::seconds(1));
    this->grid = nextGrid;
    // std::cout << "=============================================" << std::endl;
    // display();
    // std::cout << "=============================================" << std::endl;

}

std::pair<uint32_t, uint32_t> HostPathogen::countInfectedsInNeighborhood(
    const std::vector<HostPathogenCell> neighbors) const {

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

std::pair<double, double> HostPathogen::calcInfectionProbability(
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

void HostPathogen::update() {
    //std::cout << "timestamp = " << this->_timestamp << std::endl;
    this->__timestamps.push_back(this->_timestamp);
    this->iterate();
    this->_timestamp++;
}
