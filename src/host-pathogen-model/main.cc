#include <iostream>
#include <random>
#include "matplotlibcpp.h"

#include "host_pathogen_ca.h"
#include "host_pathgen_cell.h"

namespace plt = matplotlibcpp;

int main(int argc, char const *argv[])
{
    HostPathogen<HostPathogenCell> hp(100, 100);
    /*hp.getCellRef(4, 2).setIsAlive(true);
    hp.getCellRef(3, 2).setIsAlive(true);
    hp.getCellRef(2, 2).setIsAlive(true);
    hp.getCellRef(14, 2).setIsAlive(true);
    auto left = hp.getNeighbors(2, 2, NDIRECTION::BOTTOM, 2);
    hp.display();

    for (auto e: left) {
        std::cout << e.isAlive() << std::endl;
    }*/
    hp.simulate(3000);
    plt::plot(hp.get__aliveCells());
    plt::show();
    return 0;
}
