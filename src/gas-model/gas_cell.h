#ifndef GAS_CELL_H
#define GAS_CELL_H
#include <iostream>

class GasCell {
 public:
    GasCell() {

    }
    unsigned state() const {
        return _state;
    }
    template<unsigned bit>
    bool getBitAt() const {
        return (_state >> bit) & 0b00000001;
        //return _state & (1U << bit);
    }

    std::string getColorString() const {
        if (_isSolid)
            return "000,000,000";
        if (_state)
            return "0,255,0";
        return "255,255,255";
    }


    template<unsigned bit>
    void setBitAt(bool val) {
        // std::cout << "old state " << _state << std::endl;
        if (val)
            _state =  _state | (1U << bit);
        else
            _state = _state & ~(1U << bit);
        // std::cout << "new state " << _state << std::endl;

    }

    bool isSolid() const {
        return _isSolid;
    }
    void setIsSolid(bool value) {
        _isSolid = value;
    }
    void setVirtualPosition(const uint32_t&, const uint32_t&) {}

    friend inline std::ostream& operator<<(std::ostream& os, const GasCell& cell) {
        //os << cell._row << ";" << cell._col;
        std::string isSolid = cell._isSolid ? "*" : " ";
        if (cell._state)
            os << "1" << isSolid;
        else
            os << "0" << isSolid;

        return os;
    }
 private:
    unsigned _state;
    bool _isSolid;
};

#endif