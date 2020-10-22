#ifndef HOST_PATHOGEN_CELL_H
#define HOST_PATHOGEN_CELL_H

#include <iostream>

class HostPathogenCell {
 public:
    enum PathogenStatus: uint8_t {
        SUSCEPTIBLE = 1,
        INFECTED = 2,
        IMMUNE = 3,
        NONE = 4
    };

    HostPathogenCell();

    HostPathogenCell(const PathogenStatus& statusA, const PathogenStatus& statusB);
    HostPathogenCell(bool isAlive);

    void setIsAlive(bool value);
    bool isAlive() const;

    friend bool operator==(const HostPathogenCell& lhs, const HostPathogenCell& rhs);
    friend std::ostream& operator<<(std::ostream& os, const HostPathogenCell& cell);
    HostPathogenCell& operator=(const HostPathogenCell& rhs);

 private:
    bool _isAlive = false;
    PathogenStatus _pathogenAStatus = PathogenStatus::NONE;
    PathogenStatus _pathogenBStatus = PathogenStatus::NONE;
    uint8_t _weeksAlive = 0;
};

#endif