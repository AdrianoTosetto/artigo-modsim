#include <iostream>
#include <random>
#include "matplotlibcpp.h"

#include "host_pathogen_ca.h"
#include "host_pathgen_cell.h"

#include "cellular_automata.h"

namespace plt = matplotlibcpp;

int main(int argc, char const *argv[])
{

    HostPathogen hp(100, 100);
    hp.setInitialConditions(120, 10, 8);
    hp.setBreakpoints({1,20,40,70,120, 150, 200, 500});
    hp.simulate(501);
    hp.display();
    /*hp.getCellRef(2, 2).setIsAlive(true);
    hp.getCellRef(2, 2).setInfectedByA();

    hp.getCellRef(3, 2).setIsAlive(true);
    hp.getCellRef(4, 2).setIsAlive(true);
    hp.getCellRef(4, 3).setIsAlive(true);
    hp.getCellRef(4, 4).setIsAlive(true);
    hp.getCellRef(4, 5).setIsAlive(true);
    hp.getCellRef(3, 5).setIsAlive(true);
    hp.getCellRef(2, 5).setIsAlive(true);
    hp.getCellRef(2, 5).setInfectedByA();
    hp.setBreakpoints({0, 200, 500, 2000, 2999});
    //hp.getCellRef(14, 14).setIsAlive(true);

    auto cells = hp.getMooreNeighborhood(3, 3, 1, false);
    hp.display();
    auto probs = hp.calcInfectionProbability(3, 3);
    std::cout << probs.first << std::endl;
    std::cout << probs.second << std::endl;
    for (auto e: cells) {
       std::cout << e.isAlive() << std::endl;
    }
    hp.saveToImage("test");
    std::cout << "count " << cells.size() << std::endl;
    hp.simulate(3000);
    hp.display();
    std::cout << hp.aliveCells() << std::endl;*/
    plt::plot(hp.get__aliveCellsPerTimestamp());
    plt::show();
    return 0;
}
