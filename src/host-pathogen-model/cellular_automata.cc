#include <iostream>
#include <vector>
#include "cellular_automata.h"

template<typename T>
CellularAutomaton<T>::CellularAutomaton(int rows, int cols): _rows(rows), _cols(cols) {
    //_grid.assign(_rows * _cols);
}

template<typename T>
void CellularAutomaton<T>::display() {
    for(int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            std::cout << _grid[(i * _cols)  + j] << " ";
        }
        std::cout << "\n";
    }
}

template<typename T>
void CellularAutomaton<T>::update() {
    this->_timestamp++;
}

template<typename T>
T& CellularAutomaton<T>::getCellRef(uint32_t row, uint32_t col) {
    return this->_grid[row * _cols + col];
}

template<typename T>
T CellularAutomaton<T>::getCellValue(uint32_t row, uint32_t col) const {
    return this->_grid[row * _cols + col];
}

//template<typename T>
//std::vector<T> neighbors(uint32_t row, uint32_t col, uint32_t radius = 1) {}

template<typename T>
std::vector<T> CellularAutomaton<T>::leftNeighbors(uint32_t row, uint32_t col, 
                uint32_t radius) const {

    std::vector<T> neighbors;
    neighbors.reserve(radius);

    for (auto r = 0; r < radius; r++) {
        auto nCol = (col - r) % _cols;
        auto nRow = row;
        neighbors.push_back(this->getCellValue(nRow, nCol));
    }

    return neighbors;
}

template<typename T>
std::vector<T> CellularAutomaton<T>::rightNeighbors(uint32_t row, uint32_t col, 
                uint32_t radius) const {

    std::vector<T> neighbors;
    neighbors.reserve(radius);

    for (auto r = 0; r < radius; r++) {
        auto nCol = (col + r) % _cols;
        auto nRow = row;
        neighbors.push_back(this->getCellValue(nRow, nCol));
    }

    return neighbors;
}

template<typename T>
std::vector<T> CellularAutomaton<T>::topNeighbors(uint32_t row, uint32_t col, 
                uint32_t radius) const {

    std::vector<T> neighbors;
    neighbors.reserve(radius);

    for (auto r = 0; r < radius; r++) {
        auto nCol = _cols;
        auto nRow = (row + r) % _rows;
        neighbors.push_back(this->getCellValue(nRow, nCol));
    }

    return neighbors;
}

template<typename T>
std::vector<T> CellularAutomaton<T>::bottomNeighbors(uint32_t row, uint32_t col, 
                uint32_t radius) const {

    std::vector<T> neighbors;
    neighbors.reserve(radius);

    for (auto r = 0; r < radius; r++) {
        auto nCol = col;
        auto nRow = (row - r) % _rows;
        neighbors.push_back(this->getCellValue(nRow, nCol));
    }

    return neighbors;
}

template<typename T> 
std::vector<T> CellularAutomaton<T>::getNeighbors(uint32_t row, 
    uint32_t col, NDIRECTION dir, uint32_t radius) const {

        std::vector<T> neighbors;
        neighbors.reserve(radius);

        for (auto r = 1; r <= radius; r++) {

            auto nRow = -1;
            auto nCol = -1;

            switch (dir) {
                case NDIRECTION::TOP:
                    nCol = col;
                    nRow = (row - r) % _rows;
                    break;
                case NDIRECTION::TOP_RIGHT:
                    nCol = (col + r) % _cols;
                    nRow = (row - r) % _rows;
                    break;
                case NDIRECTION::RIGHT:
                    nRow = row;
                    nCol = (col + r) % _cols;
                    break;
                case NDIRECTION::BOTTOM_RIGHT:
                    nRow = (row + r) % _rows;
                    nCol = (col + r) % _cols;
                    break;
                case NDIRECTION::BOTTOM:
                    nRow = (row + r) % _rows;
                    nCol = col;
                    break;
                case NDIRECTION::BOTTOM_LEFT:
                    nRow = (row + r) % _rows;
                    nCol = (col - r) % _cols;
                    break;
                case NDIRECTION::LEFT:
                    nRow = row;
                    nCol = (col - r) % _cols;
                    break;
                case NDIRECTION::TOP_LEFT:
                    nRow = (row - r) % _rows;
                    nCol = (col - r) % _cols;
                    break;
                default:
                    break;
            }
            neighbors.push_back(this->getCellValue(nRow, nCol));
        }
    return neighbors;
}

template<typename T>
void CellularAutomaton<T>::simulate(uint32_t steps) {
    for (auto i = 0; i < steps; i++) {
        this->update();
    }
    //this->display();
}
