#ifndef TURING_PATTERNS_CELL
#define TURING_PATTERNS_CELL

#include <cmath>
#include "utils.h"

enum CellType {
    UC = 0,
    DC = 1
};

class TuringPatternsCell {

 public:
    TuringPatternsCell() {
        _row = _col = _rowV = _colV = 0;
        _xposition = 0.5; // uniformDistribution(0, 1);
        _yposition = 0.5; //uniformDistribution(0, 1);
        _type = CellType::UC;
        _isVirtual = false;
    }

    TuringPatternsCell(uint32_t row, uint32_t col): 
        _row(row), _col(col) {

        _rowV = row;
        _colV = col;
        _xposition = 0.5; // niformDistribution(0, 1);
        _yposition = 0.5; //uniformDistribution(0, 1);
        _type = CellType::UC;
        _isVirtual = false;
    }
    TuringPatternsCell(uint32_t row, uint32_t col, CellType type): 
        _row(row), _col(col) {

        _rowV = row;
        _colV = col;

        _xposition = 0.5; //uniformDistribution(0, 1);
        _yposition = 0.5; //uniformDistribution(0, 1);
        _type = type;
        _isVirtual = false;
    }

    TuringPatternsCell(uint32_t row, uint32_t col, int32_t rowV, int32_t colV,
        CellType type): _row(row), _col(col), _rowV(rowV), _colV(colV) {

        if (rowV != row || colV != col)
            _isVirtual = true;
        else
            _isVirtual = false;
    
        _xposition = 0.5; //uniformDistribution(0, 1);
        _yposition = 0.5; //uniformDistribution(0, 1);
        _type = type;
    }

    double realPositionX() const {
        return static_cast<double>(_rowV) + _xposition;
    }
    double realPositionY() const {
        return static_cast<double>(_colV) + _yposition;
    }
    double distance(const TuringPatternsCell& other) const {

        auto temp = std::pow(realPositionX() - other.realPositionX(), 2) +
            std::pow(realPositionY() - other.realPositionY(), 2);

        return std::sqrt(temp);

    }
    CellType type() const {
        return _type;
    }
    void setType(const CellType& type) {
        _type = type;
    }
    void setVirtualPosition(int32_t row, int32_t col) {
        _rowV = row;
        _colV = col;
        if (_row != _rowV || _col != _colV)
            _isVirtual = true;
    }
    bool isVirtual() const {
        return _isVirtual;
    }
    void setIsVirtual(const bool& value) {
        _isVirtual = value;
    }
    uint32_t row() const {
        return _row;
    }
    uint32_t col() const {
        return _col;
    }
    int32_t rowV() const {
        return _rowV;
    }
    int32_t colV() const {
        return _colV;
    }

    std::string getColorString() const {
        if (_type == CellType::DC)
            return "333,333,333";
        else
            return "255,255,255";
    }

    friend inline std::ostream& operator<<(std::ostream& os, const TuringPatternsCell& cell) {
        //os << cell._row << "," << cell._col;
        os << cell._type;
        return os;
    }

 private:
    uint32_t _row;
    uint32_t _col;

    int32_t _rowV;
    int32_t _colV;

    bool _isVirtual;
    double _xposition;
    double _yposition;
    CellType _type;
};

#endif