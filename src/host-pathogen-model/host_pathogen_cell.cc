#include "host_pathgen_cell.h"

const auto& NONE = HostPathogenCell::PathogenStatus::NONE;

HostPathogenCell::HostPathogenCell(): 
    _pathogenAStatus(NONE), _pathogenBStatus(NONE), _isAlive(false) {}


HostPathogenCell::HostPathogenCell(bool isAlive = false): _isAlive(isAlive) {
    std::cout << "calling this: " << PathogenStatus::SUSCEPTIBLE <<  " ";
    if (isAlive) {
        _pathogenAStatus = PathogenStatus::SUSCEPTIBLE;
        _pathogenBStatus = PathogenStatus::SUSCEPTIBLE;
    }
}

HostPathogenCell::HostPathogenCell(
    const PathogenStatus& statusA,
    const PathogenStatus& statusB): _pathogenAStatus(statusA), _pathogenBStatus(statusB) {
        _isAlive = false;

        if (_pathogenAStatus != NONE || _pathogenBStatus != NONE)
            _isAlive = true;
}


void HostPathogenCell::setInfectedByA() {
    _pathogenAStatus = PathogenStatus::INFECTED;
}
void HostPathogenCell::setInfectedByB() {
    _pathogenBStatus = PathogenStatus::INFECTED;
}


void HostPathogenCell::setIsAlive(bool value) {
    _isAlive = value;
    if (value) {
        color = "255,255,255";
        _pathogenAStatus = PathogenStatus::SUSCEPTIBLE;
        _pathogenBStatus = PathogenStatus::SUSCEPTIBLE;
    } else {
        color = "0,0,0";
        _pathogenAStatus = NONE;
        _pathogenBStatus = NONE;
        _weeksAlive = 0;
    }
}

bool HostPathogenCell::isAlive() const {
    return _isAlive;
}

bool HostPathogenCell::infectedByA() const {
    return _pathogenAStatus == PathogenStatus::INFECTED;
}

bool HostPathogenCell::infectedByB() const {
    return _pathogenBStatus == PathogenStatus::INFECTED;
}

void HostPathogenCell::setRGBColor(std::array<uint8_t, 3>&& codes) {
    rgbColor = codes;
}

bool operator==(const HostPathogenCell& lhs, const HostPathogenCell& rhs) {
    return true;
}

std::string HostPathogenCell::getColorString() const {
    const std::string red = std::to_string(rgbColor[0]);
    const std::string green = std::to_string(rgbColor[1]);
    const std::string blue = std::to_string(rgbColor[2]);

    std::string ret = red + "," + green + "," + red;
    if (_isAlive) {
        if (infectedByA() || infectedByB())
            return "255,0,0";
            
        return "255,255,255";
    }
    return "0,0,0";
}

HostPathogenCell& HostPathogenCell::operator=(const HostPathogenCell& rhs) {
    //std::cout << "operator = being called\n";
    if (this == &rhs)
        return *this;

    _pathogenAStatus = rhs._pathogenAStatus;
    _pathogenBStatus = rhs._pathogenBStatus;
    _isAlive = rhs._isAlive;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const HostPathogenCell& cell) {

    if (cell._isAlive) {
        std::string code;

        if (cell.infectedByA() && cell.infectedByB())
            code = "m";
        if (cell.infectedByA() && !cell.infectedByB())
            code = "a";
        if (cell.infectedByB() && !cell.infectedByA())
            code = "b";
        if (!cell.infectedByA() && !cell.infectedByB())
            code = "h";
        os << code;
    } else {
        os << "d";
    }

    return os;
}

std::fstream& operator>>(std::fstream& os, const HostPathogenCell& cell) {

    if (!cell._isAlive)
        os >> "[255;255;255]";
    else {
        os >> "[0;0;0]";
    }

    return os;
}
