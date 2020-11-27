#ifndef CELULLAR_AUTOMATON_H
#define CELULLAR_AUTOMATON_H
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>
#include <filesystem>

#include "gas_cell.h"

std::vector<std::pair<int, int>> genOffsets(int radius) {
    std::vector<std::pair<int, int>> offsets;
    for (auto r = -radius; r <= radius; r++)
        offsets.push_back(std::make_pair(-radius, r));

    for (auto r = -(radius-1); r <= (radius-1); r++)
        offsets.push_back(std::make_pair(r, radius));

    for (auto r = radius; r >= -radius; r--)
        offsets.push_back(std::make_pair(radius, r));

    for (auto r = (radius-1); r >= -(radius-1); r--)
        offsets.push_back(std::make_pair(r, -radius));

    return offsets;
}

int mod(int a, int b)
{
    int r = a % b;
    return r < 0 ? r + b : r;
}

template<typename T>
class Grid {
 public:
    Grid(uint32_t rows, uint32_t cols): _rows(rows), _cols(cols) {
        _rawGrid.resize(_rows*_cols);
    }
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
        _rawGrid.resize(a*b);
        //_rawGrid.assign(a*b, T(0, 0));
        //std::generate(_rawGrid.begin(), _rawGrid.end(), [](){ return T(); });
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
  TOP_LEFT
};

enum NeighborLocation : uint8_t {
    nTOP_LEFT,
    nTOP,
    nTOP_RIGHT,
    nRIGHT,
    nBOTTOM_RIGHT,
    nBOTTOM,
    nBOTTOM_LEFT,
    nLEFT
};
enum BitDirection: uint8_t {
    bTOP_LEFT,
    bTOP,
    bTOP_RIGHT,
    bRIGHT,
    bBOTTOM_RIGHT,
    bBOTTOM,
    bBOTTOM_LEFT,
    bLEFT
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
    std::vector<T> moore(uint32_t, uint32_t, uint32_t) const;
    std::vector<T> getMooreNeighborhood(uint32_t row, uint32_t col, uint32_t radius, bool) const;
    std::vector<T> path(uint32_t row, uint32_t col, DirectionsList directions) const;
 
    void saveToImage(const std::string& filename) const;
    void setBreakpoints(const std::initializer_list<uint32_t>&);
    void setSnapshotsFolder(const std::string& folder) {
        _snapshotsFolder = folder;
    }
 protected:
    Grid<T> grid;
    int _rows;
    int _cols;
    uint32_t _timestamp = 0;
    std::string _snapshotsFolder;
 private:
    inline std::vector<T> _getMooreNeighborhoodEntirePath(uint32_t row,  
        uint32_t col, uint32_t radius) const;
    inline std::vector<T> _getMooreNeighborhood(uint32_t row, uint32_t col, uint32_t radius) const;

    std::pair<uint32_t, uint32_t> _getNeighboorPosition(uint32_t row,
        uint32_t col, NDIRECTION dir, uint32_t radius) const;

    std::tuple<uint32_t, uint32_t, int32_t, int32_t> _getNeighboorPositionV2(uint32_t row, 
        uint32_t col, NDIRECTION dir, uint32_t radius) const;

    T _getNeighbor(uint32_t row, uint32_t col, NDIRECTION dir, uint32_t radius) const;



    // in which timestamps the class should generate a snapshot of the grid
    std::vector<uint32_t> _imageBreakpoints{};

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
T CellularAutomaton<T>::_getNeighbor(uint32_t row, 
    uint32_t col, NDIRECTION dir, uint32_t radius) const {
    
    auto position = this->_getNeighboorPositionV2(row, col, dir, radius);
    auto nRow  = std::get<0>(position);
    auto nCol  = std::get<1>(position);
    auto nRowV = std::get<2>(position);
    auto nColV = std::get<3>(position);
    auto ncell = getCellValue(nRow, nCol);

    ncell.setVirtualPosition(nRowV, nColV);

    return ncell;
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
            auto cell = _getNeighbor(row, col, dir, r);
            neighbors.push_back(cell);
        }
    return neighbors;
}

template<typename T> 
std::vector<T> CellularAutomaton<T>::moore(uint32_t row, 
    uint32_t col, uint32_t radius) const {

    std::vector<T> ret;
    for (auto r = 1; r <= radius; r++) {
        for (auto& offset: genOffsets(r)) {
            auto nRow = mod(row + offset.first, _rows);
            auto nCol = mod(col + offset.second, _cols);

            auto nRowV = row + offset.first;
            auto nColV = col + offset.second;

            auto nCell = getCellValue(nRow, nCol);
            nCell.setVirtualPosition(nRowV, nColV);

            ret.push_back(nCell);
        }
    }

    return ret;
}

template<typename T>
void CellularAutomaton<T>::simulate(uint32_t steps) {

    for (auto i = 0; i < steps; i++) {
        if (!_imageBreakpoints.empty()) {
            auto breakpoint = _imageBreakpoints.front();
            if (i == breakpoint) {
                const std::string filename = _snapshotsFolder + "snapshot" + std::to_string(breakpoint);
                if (!std::filesystem::is_directory(_snapshotsFolder)) {
                    if (!std::filesystem::create_directory(_snapshotsFolder)) {
                        throw "Error on creating snapshots folder";
                    }
                }
                saveToImage(filename);
                _imageBreakpoints.erase(_imageBreakpoints.begin());
            }
        }
        this->update();
    }
    //this->display();
}

#endif
