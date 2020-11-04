#ifndef EXICITABLE_MEDIA_CELL_H
#define EXICITABLE_MEDIA_CELL_H

#include <iostream>
#include <random>

double_t uniformDistribution(double low, double high) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> distr(low, high);

    return distr(gen);
}



class ExcitableMediaCell {
 public:
    ExcitableMediaCell();
    ExcitableMediaCell(uint32_t, uint32_t);
    double distance(const ExcitableMediaCell& other);

    double xPerturbation() const;
    double yPerturbation() const;

    uint32_t row() const;
    uint32_t col() const;

    double realPositionX() const;
    double realPositionY() const;

    std::string getColorString() const {
        return _colorString;
    }
    void update(double sum) {
        if (_state < E + R) {
            _state++;
        } else {
            
        }
    }
    friend std::ostream& operator<<(std::ostream& os, const ExcitableMediaCell& cell);
 private:
    double _xPerturbation;
    double _yPerturbation;
    double _weight;
    uint32_t _row;
    uint32_t _col;

    uint8_t _state{0};

    uint32_t E = 5;
    uint32_t R = 8; 
    std::string _colorString = "0,0,0";
};


ExcitableMediaCell::ExcitableMediaCell(uint32_t row, uint32_t col): 
    _row(row), _col(col) {
    _xPerturbation = uniformDistribution(-0.5, 0.5);
    _yPerturbation = uniformDistribution(-0.5, 0.5);
    _weight = uniformDistribution(0.5, 1.5);
}

ExcitableMediaCell::ExcitableMediaCell(): _row(0), _col(0) {

    _xPerturbation = uniformDistribution(-0.5, 0.5);
    _yPerturbation = uniformDistribution(-0.5, 0.5);
    _weight = uniformDistribution(0.5, 1.5);
}

uint32_t ExcitableMediaCell::row() const {
    return _row;
}
uint32_t ExcitableMediaCell::col() const {
    return _col;
}

double ExcitableMediaCell::xPerturbation() const {
    return _xPerturbation;
}
double ExcitableMediaCell::yPerturbation() const {
    return _xPerturbation;
}

double ExcitableMediaCell::realPositionX() const {
    return static_cast<double>(_row) + _xPerturbation;
}

double ExcitableMediaCell::realPositionY() const {
    return static_cast<double>(_col) + _yPerturbation;
}

double ExcitableMediaCell::distance(const ExcitableMediaCell& other) {
    return (
        std::abs(this->realPositionX() - other.realPositionX()) +
        std::abs(this->realPositionY() - other.realPositionY())
    );
}

std::ostream& operator<<(std::ostream& os, const ExcitableMediaCell& cell) {
    os << cell._row << ";" << cell._col;
}

#endif