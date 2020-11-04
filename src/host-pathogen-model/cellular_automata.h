#ifndef CELULLAR_AUTOMATON_H
#define CELULLAR_AUTOMATON_H
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>

#include "host_pathgen_cell.h"


template<typename T>
class Grid {
 public:
    Grid(uint32_t rows, uint32_t cols): _rows(rows), _cols(cols) {}
    Grid(const Grid& grid): _rows(grid.rows()), _cols(grid.cols()) {
        _rawGrid = grid._rawGrid;
    }
    Grid(): _rows(0), _cols(0) {}
    uint32_t rows() const { return _rows; }
    uint32_t cols() const { return _cols; }
    std::vector<T>& rawGridRef() {
        return _rawGrid;
    }
    void set(uint32_t a, uint32_t b) {
        _rows = a;
        _cols = b;
        _rawGrid.assign(a*b, HostPathogenCell());
    }
    T getCellValue(uint32_t row, uint32_t col) const {
        return _rawGrid[row * _cols + col];
    }
    T& getCellRef(uint32_t row, uint32_t col) {
        return _rawGrid[row * _cols + col];
    }

    std::vector<T>& rawGrid() {
        return _rawGrid;
    }

    void operator=(const Grid& rhs) {
        _rawGrid = rhs._rawGrid;
        _rows = rhs.rows();
        _cols = rhs.cols();
    }
    void operator=(const std::vector<T>& rhs) {
        _rawGrid = rhs;
    }
    T& operator[](size_t index) {
        return _rawGrid[index];
    }

 private:
    std::vector<T> _rawGrid;
    uint32_t _rows;
    uint32_t _cols;
};


enum NDIRECTION {
  TOP,
  TOP_RIGHT,
  RIGHT,
  BOTTOM_RIGHT,
  BOTTOM,
  BOTTOM_LEFT,
  LEFT,
  TOP_LEFT,
  SENTINEL
};


template<typename T>
class CellularAutomaton {

    typedef std::pair<NDIRECTION, uint32_t> Direction;
    typedef std::vector<Direction> DirectionsList;
    typedef std::pair<uint32_t, uint32_t> Position;

 public:
    CellularAutomaton(int rows, int cols);
    void display();
    virtual void update();
    virtual void simulate(uint32_t);
    T getCellValue(uint32_t, uint32_t) const;

    T& getCellRef(uint32_t, uint32_t);

    std::vector<T> getNeighbors(uint32_t, uint32_t, NDIRECTION, uint32_t radius = 1) const;
    std::vector<T> getMooreNeighborhood(uint32_t row, uint32_t col, uint32_t radius, bool) const;
    std::vector<T> path(uint32_t row, uint32_t col, DirectionsList directions) const;
 
    void saveToImage(const std::string& filename) const;
    void setBreakpoints(const std::initializer_list<uint32_t>&);
 protected:
    std::vector<T> _grid;
    Grid<T> grid;
    int _rows;
    int _cols;
    uint32_t _timestamp = 0;
 private:
    inline std::vector<T> _getMooreNeighborhoodEntirePath(uint32_t row,  
        uint32_t col, uint32_t radius) const;
    inline std::vector<T> _getMooreNeighborhood(uint32_t row, uint32_t col, uint32_t radius) const;

    std::pair<uint32_t, uint32_t> _getNeighboorPosition(uint32_t row,
        uint32_t col, NDIRECTION dir, uint32_t radius) const;

    T _getNeighbor(uint32_t row, uint32_t col, NDIRECTION dir, uint32_t radius);

    // in which timestamps the class should generate a snapshot of the grid
    std::vector<uint32_t> _imageBreakpoints;

};

template<typename T>
void CellularAutomaton<T>::saveToImage(const std::string& filename) const {

    std::ofstream fout;
    std::string filenameExt = filename + ".txt";
    fout.open(filenameExt);


    for (auto i = 0; i < _rows; i++) {
        for (auto j = 0; j < _cols - 1; j++) {
            fout << getCellValue(i, j).getColorString() << ";";
        }
        fout << getCellValue(i, _cols  - 1).getColorString();
        fout << "\n";
    }
    fout.close();
}

template<typename T>
void CellularAutomaton<T>::setBreakpoints(const std::initializer_list<uint32_t>& breakpoints) {
    _imageBreakpoints = breakpoints;
}

template<typename T>
CellularAutomaton<T>::CellularAutomaton(int rows, int cols): _rows(rows), _cols(cols) {
    //_grid.assign(_rows * _cols);
    grid.set(_rows, _cols);
}

template<typename T>
void CellularAutomaton<T>::display() {
    for(int i = 0; i < _rows; i++) {
        for (int j = 0; j < _cols; j++) {
            std::cout << grid[(i * _cols)  + j] << " ";
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
    return this->grid.getCellRef(row, col);
}

template<typename T>
T CellularAutomaton<T>::getCellValue(uint32_t row, uint32_t col) const {
    return grid.getCellValue(row, col);
}

template<typename T>
std::pair<uint32_t, uint32_t>  CellularAutomaton<T>::_getNeighboorPosition(uint32_t row, 
    uint32_t col, NDIRECTION dir, uint32_t radius) const {

        std::pair<uint32_t, uint32_t> ret;

        auto nCol = 0;
        auto nRow = 0;

        switch (dir) {
            case NDIRECTION::TOP:
                nCol = col % _cols;
                nRow = (row - radius) % _rows;
                break;
            case NDIRECTION::TOP_RIGHT:
                nCol = (col + radius) % _cols;
                nRow = (row - radius) % _rows;
                break;
            case NDIRECTION::RIGHT:
                nRow = row;
                nCol = (col + radius) % _cols;
                break;
            case NDIRECTION::BOTTOM_RIGHT:
                nRow = (row + radius) % _rows;
                nCol = (col + radius) % _cols;
                break;
            case NDIRECTION::BOTTOM:
                nRow = (row + radius) % _rows;
                nCol = col;
                break;
            case NDIRECTION::BOTTOM_LEFT:
                nRow = (row + radius) % _rows;
                nCol = (col - radius) % _cols;
                break;
            case NDIRECTION::LEFT:
                nRow = row;
                nCol = (col - radius) % _cols;
                break;
            case NDIRECTION::TOP_LEFT:
                nRow = (row - radius) % _rows;
                nCol = (col - radius) % _cols;
                break;
            default:
                break;
        }
        ret.first = nRow;
        ret.second = nCol;

    return ret;
}


template<typename T>
T CellularAutomaton<T>::_getNeighbor(uint32_t row, 
    uint32_t col, NDIRECTION dir, uint32_t radius) {
    
    auto position = this->_getNeighboorPosition(row, col, dir, radius);
    return getCellValue(position.first, position.second);
}

/*
    return the r neighboors from a given cell in given direction
*/

template<typename T> 
std::vector<T> CellularAutomaton<T>::getNeighbors(uint32_t row, 
    uint32_t col, NDIRECTION dir, uint32_t radius) const {

        std::vector<T> neighbors;
        neighbors.reserve(radius);

        for (auto r = 1; r <= radius; r++) {

            auto position = _getNeighboorPosition(row, col, dir, r);
            auto nRow = position.first;
            auto nCol = position.second;
            
            neighbors.push_back(this->getCellValue(nRow, nCol));
        }
    return neighbors;
}

template<typename T>
inline std::vector<T> CellularAutomaton<T>::_getMooreNeighborhoodEntirePath(uint32_t row, 
    uint32_t col, uint32_t radius) const {
        const uint32_t neighborsCount = (radius + 2) * (radius + 3) * (2*(radius+2) + 1) / 6;

    std::vector<T> neighbors;
    neighbors.reserve(neighborsCount);
    for (auto r = 1; r <= radius; r++) {

        // start scanning the top, then go right, bottom, left and finally top again
        // to complete the square
        auto topCellPos = _getNeighboorPosition(row, col, NDIRECTION::TOP, r);
        auto topCellRow = topCellPos.first;
        auto topCellCol = topCellPos.second;

        Direction right1(NDIRECTION::RIGHT, r);
        Direction bottom(NDIRECTION::BOTTOM, r*2);
        Direction left(NDIRECTION::LEFT, r*2);
        Direction top(NDIRECTION::TOP, r*2);
        Direction right2(NDIRECTION::RIGHT, r - 1);

        DirectionsList directionsList{right1, bottom, left, top };
        if (r > 1)
            directionsList.push_back(right2);

        // moore neighborhood with radius r
        auto rNeighborhood = path(topCellRow, topCellCol, directionsList);

        neighbors.insert (
            std::end(neighbors),
            std::begin(rNeighborhood),
            std::end(rNeighborhood)
        );
    }
    return neighbors;
}

template<typename T>
inline std::vector<T> CellularAutomaton<T>::_getMooreNeighborhood(uint32_t row, 
    uint32_t col, uint32_t radius) const {

    const uint32_t neighborsCount = (radius + 2) * (radius + 3) * (2*(radius+2) + 1) / 6;

    // approximation of how many cells will be stored in the vector
    // TODO: redo the formula to match exactly the numbers of elements needed
    std::vector<T> neighbors;
    neighbors.reserve(neighborsCount);

    // start scanning the top, then go right, bottom, left and finally top again
    // to complete the square
    auto topCellPos = _getNeighboorPosition(row, col, NDIRECTION::TOP, radius);
    auto topCellRow = topCellPos.first;
    auto topCellCol = topCellPos.second;

    Direction right1(NDIRECTION::RIGHT, radius);
    Direction bottom(NDIRECTION::BOTTOM, radius*2);
    Direction left(NDIRECTION::LEFT, radius*2);
    Direction top(NDIRECTION::TOP, radius*2);
    Direction right2(NDIRECTION::RIGHT, radius - 1);

    DirectionsList directionsList {right1, bottom, left, top };
    if (radius > 1)
        directionsList.push_back(right2);

    // moore neighborhood with radius r
    auto rNeighborhood = path(topCellRow, topCellCol, directionsList);

    neighbors.insert (
        std::end(neighbors),
        std::begin(rNeighborhood),
        std::end(rNeighborhood)
    );

    return neighbors;
}

/*
    returns a vector of cells that belong to the neighborhood of 
    (row, col) cell.
*/

template<typename T>
std::vector<T> CellularAutomaton<T>::getMooreNeighborhood(uint32_t row, 
    uint32_t col, uint32_t radius, bool entirePath) const {

    const uint32_t neighborsCount = (radius + 2) * (radius + 3) * (2*(radius+2) + 1) / 6;

    // approximation of how many cells will be stored in the vector
    // TODO: redo the formula to match exactly the numbers of elements needed
    std::vector<T> neighbors;
    neighbors.reserve(neighborsCount);


    if (entirePath)
        return _getMooreNeighborhoodEntirePath(row, col, radius);
    else
        return _getMooreNeighborhood(row, col, radius);

    return neighbors;
}

template<typename T>
std::vector<T> CellularAutomaton<T>::path(uint32_t row, uint32_t col,
    DirectionsList directions) const {

    std::vector<T> pathCells;

    auto maxRadius = std::max_element(std::begin(directions), std::end(directions), 
        [] (const Direction& lhs, const Direction& rhs) {
            return std::isless(lhs.second, rhs.second);
    })->second;

    pathCells.reserve((directions.size() * maxRadius) + 1);

    auto currentRow = row;
    auto currentCol = col;

    pathCells.push_back(getCellValue(row, col));

    for (auto direction: directions) {

        auto dir = direction.first;
        auto steps = direction.second; // how many steps in that direction
        std::vector<T> cells = getNeighbors(currentRow, currentCol, dir, steps);

        pathCells.insert(std::end(pathCells), std::begin(cells), std::end(cells));
        auto newPosition = _getNeighboorPosition(currentRow, currentCol, dir, steps);
        currentRow = newPosition.first;
        currentCol = newPosition.second;

    }

    return pathCells;
}

template<typename T>
void CellularAutomaton<T>::simulate(uint32_t steps) {

    for (auto i = 0; i < steps; i++) {
        auto breakpoint = _imageBreakpoints.front();
        if (i == breakpoint) {
            const std::string filename = "snapshot" + std::to_string(breakpoint);
            saveToImage(filename);
            _imageBreakpoints.erase(_imageBreakpoints.begin());
        }
        this->update();
    }
    //this->display();
}

#endif
