#ifndef EXICITABLE_MEDIA_CELL_H
#define EXICITABLE_MEDIA_CELL_H

#include <iostream>
#include <random>

double uniformDistribution(double low, double high) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(low, high);

    return distr(gen);
}

template<std::size_t E = 12, std::size_t R = 13>
class ExcitableMediaCell {
 public:
    ExcitableMediaCell();
    ExcitableMediaCell(uint32_t, uint32_t);
    ExcitableMediaCell(uint32_t, uint32_t, uint32_t);
    double distance(const ExcitableMediaCell& other);

    double xPerturbation() const;
    double yPerturbation() const;

    uint32_t row() const;
    uint32_t col() const;

    double realPositionX() const;
    double realPositionY() const;

    uint32_t state() const;
    double weight() const;
    bool excited() const;
    bool refractory() const;
    bool nonExcited() const;

    std::string getColorString() const {
        if (excited())
            return "255,255,255";
        if (refractory())
            return "100,100,100";
        return "000,000,000";
    }
    void update(double sum) {
        //std::cout << sum << std::endl;
        if (_state == 0) {
            if (sum > 0.35) {
                //std::cout << "aqui" << std::endl;
                _state = 1;
                _hasEverBeenActive = true;
            }
            return;
        }
        if (_state <= (E + R)) {
            _state++;
            return;
        }
        if (_state > (E + R))
            _state = 0;
    }

    bool hasEverBeenActive() {
        return _hasEverBeenActive;
    }
    friend inline std::ostream& operator<<(std::ostream& os, const ExcitableMediaCell<E, R>& cell) {
        //os << cell._row << ";" << cell._col;
        os << cell.state();
        return os;
    }
 private:
    double _xPerturbation;
    double _yPerturbation;
    double _weight;

    uint32_t _row;
    uint32_t _col;

    uint8_t _state{0};

    std::string _colorString = "0,0,0";

    bool _hasEverBeenActive;
};

template<std::size_t E, std::size_t R>
ExcitableMediaCell<E, R>::ExcitableMediaCell(uint32_t row, uint32_t col): 
    _row(row), _col(col) {
    _xPerturbation = uniformDistribution(-0.5, 0.5);
    _yPerturbation = uniformDistribution(-0.5, 0.5);
    _weight = uniformDistribution(0.5, 1.5);
    _hasEverBeenActive = false;
}

template<std::size_t E, std::size_t R>
ExcitableMediaCell<E, R>::ExcitableMediaCell(uint32_t state, uint32_t row, uint32_t col): 
    _row{row}, _col{col}, _state{state} {
    _xPerturbation = uniformDistribution(-0.5, 0.5);
    _yPerturbation = uniformDistribution(-0.5, 0.5);
    _weight = uniformDistribution(0.5, 1.5);
    if (_state > 0)
        _hasEverBeenActive = true;
}

template<std::size_t E, std::size_t R>
ExcitableMediaCell<E, R>::ExcitableMediaCell(): _row(0), _col(0) {

    _xPerturbation = uniformDistribution(-0.5, 0.5);
    _yPerturbation = uniformDistribution(-0.5, 0.5);
    _weight = uniformDistribution(0.5, 1.5);
    _hasEverBeenActive = false;
}

template<std::size_t E, std::size_t R>
uint32_t ExcitableMediaCell<E, R>::row() const {
    return _row;
}

template<std::size_t E, std::size_t R>
uint32_t ExcitableMediaCell<E, R>::col() const {
    return _col;
}

template<std::size_t E, std::size_t R>
double ExcitableMediaCell<E, R>::xPerturbation() const {
    return _xPerturbation;
}

template<std::size_t E, std::size_t R>
double ExcitableMediaCell<E, R>::yPerturbation() const {
    return _xPerturbation;
}

template<std::size_t E, std::size_t R>
double ExcitableMediaCell<E, R>::realPositionX() const {
    return static_cast<double>(_row) + _xPerturbation;
}

template<std::size_t E, std::size_t R>
double ExcitableMediaCell<E, R>::realPositionY() const {
    return static_cast<double>(_col) + _yPerturbation;
}

template<std::size_t E, std::size_t R>
double ExcitableMediaCell<E, R>::distance(const ExcitableMediaCell& other) {
    return (
        std::abs(this->realPositionX() - other.realPositionX()) +
        std::abs(this->realPositionY() - other.realPositionY())
    );
}

template<std::size_t E, std::size_t R>
uint32_t ExcitableMediaCell<E, R>::state() const {
    return _state;
}

template<std::size_t E, std::size_t R>
double ExcitableMediaCell<E, R>::weight() const {
    return _weight;
}

template<std::size_t E, std::size_t R>
bool ExcitableMediaCell<E, R>::excited() const {
    return _state > 0 && _state <= E;
}

template<std::size_t E, std::size_t R>
bool ExcitableMediaCell<E, R>::refractory() const {
    return _state > E && _state <= E + R;
}

template<std::size_t E, std::size_t R>
bool ExcitableMediaCell<E, R>::nonExcited() const {
    return _state == 0;
}

#endif