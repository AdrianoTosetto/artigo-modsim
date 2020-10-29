#ifndef EXICITABLE_MEDIA_CELL_H
#define EXICITABLE_MEDIA_CELL_H
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

 private:
    double _xPerturbation;
    double _yPerturbation;
    uint32_t _row;
    uint32_t _col;
};


ExcitableMediaCell::ExcitableMediaCell(uint32_t row, uint32_t col): 
    _row(row), _col(col) {
    _xPerturbation = uniformDistribution(-0.5, 0.5);
    _yPerturbation = uniformDistribution(-0.5, 0.5);
}

ExcitableMediaCell::ExcitableMediaCell() {}

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

double ExcitableMediaCell::realPositionY() const {}

double ExcitableMediaCell::distance(const ExcitableMediaCell& other) {
    return (
        std::abs(this->realPositionX() - other.realPositionX()) - 
        std::abs(this->realPositionY() - other.realPositionY())
    );
}

#endif