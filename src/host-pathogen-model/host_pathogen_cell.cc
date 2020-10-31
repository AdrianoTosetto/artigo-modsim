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
        _pathogenAStatus = PathogenStatus::SUSCEPTIBLE;
        _pathogenBStatus = PathogenStatus::SUSCEPTIBLE;
    } else {
        _pathogenAStatus = NONE;
        _pathogenBStatus = NONE;
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

bool operator==(const HostPathogenCell& lhs, const HostPathogenCell& rhs) {
    return true;
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

    if (!cell._isAlive)
        os << " 0 ";
    else {
        os << " 1 ";
        // os << "A-" << cell._pathogenAStatus << "|B-" << cell._pathogenBStatus;
    }

    return os;
}