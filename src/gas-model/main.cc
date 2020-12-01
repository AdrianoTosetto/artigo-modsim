#include <iostream>
#include <thread>
#include <initializer_list>
#include "matplotlibcpp.h"

#include "gas_model.h"

namespace plt = matplotlibcpp;

int main(int argc, char const *argv[])
{
    GasModel gm(300, 300);
    // set macroblock size of 75 x 75
    gm.setMacroblocks(75);
    gm.setSquareWithOpenWallMiddle();
    gm.init();
    gm.generateSimulationVideo("grid_300_300");
    //gm.test();
    std::vector<uint32_t> timestamps;

    for (auto i = 0; i < 1000; i++) {
        timestamps.push_back(i);
    }

    gm.setBreakpoints(timestamps);

    gm.setSnapshotsFolder("test/");

    std::cout << gm.countParticles() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    gm.simulate(1000);

    auto totalParticlesInEachMacroblockAt = gm.getTotalParticlesInMacroblockAtTimestamp();
    std::cout << "Particles in each macroblock at timestamp 1" << std::endl;
    for (auto i = 0; i < totalParticlesInEachMacroblockAt[0].size(); i++) {
        std::cout << "Macroblock " << i << " total Particles = " << totalParticlesInEachMacroblockAt[0][i] << std::endl;
    }

    std::cout << "Particles in each macroblock at timestamp 300" << std::endl;
    for (auto i = 0; i < totalParticlesInEachMacroblockAt[299].size(); i++) {
        std::cout << "Macroblock " << i << " total Particles = " << totalParticlesInEachMacroblockAt[299][i] << std::endl;
    }

    std::cout << "Particles in each macroblock at timestamp 500" << std::endl;
    for (auto i = 0; i < totalParticlesInEachMacroblockAt[499].size(); i++) {
        std::cout << "Macroblock " << i << " total Particles = " << totalParticlesInEachMacroblockAt[499][i] << std::endl;
    }

    std::cout << "Particles in each macroblock at timestamp 1000" << std::endl;
    for (auto i = 0; i < totalParticlesInEachMacroblockAt[999].size(); i++) {
        std::cout << "Macroblock " << i << " total Particles = " << totalParticlesInEachMacroblockAt[999][i] << std::endl;
    }

    /**
     *
     *  plot: timestamps (breakpoints ) x standardDeviations
     * */
    plt::plot(timestamps, gm.getStandardDeviations());
    plt::show();

    /**
     *
     *  plot: timestamps (breakpoints ) x total particles in the automaton
     * */

    plt::plot(timestamps, gm.getTotalParticles());
    plt::show();

    return 0;
}
