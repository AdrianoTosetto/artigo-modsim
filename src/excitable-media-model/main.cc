#include <iostream>
#include "excitable_media_model.h"

int main(int argc, char const *argv[])
{

    ExcitableMediaModel modelR1(100, 150, 1.3);
    modelR1.setSnapshotsFolder("r_1.3/");
    modelR1.setBreakpoints({100, 499, 999});
    modelR1.generateSimulationVideo("videoR1");
    modelR1.simulate(1000);

    ExcitableMediaModel modelR2(100, 150, 1.4);
    modelR2.setSnapshotsFolder("r_1.4/");
    modelR2.setBreakpoints({99, 499, 999});
    modelR2.generateSimulationVideo("videoR2");
    modelR2.simulate(1000);

    ExcitableMediaModel modelR3(100, 150, 1.5);
    modelR3.setSnapshotsFolder("r_1.5/");
    modelR3.setBreakpoints({99, 499, 999});
    modelR3.generateSimulationVideo("videoR3");
    modelR3.simulate(1000);

    ExcitableMediaModel modelR4(100, 150, 1.6);
    modelR4.setSnapshotsFolder("r_1.6/");
    modelR4.setBreakpoints({99, 499, 999});
    modelR4.generateSimulationVideo("videoR4");
    modelR4.simulate(1000);

    ExcitableMediaModel modelR5(100, 150, 1.7);
    modelR5.setSnapshotsFolder("r_1.7/");
    modelR5.setBreakpoints({99, 499, 999});
    modelR5.generateSimulationVideo("videoR5");
    modelR5.simulate(1000);

    ExcitableMediaModel modelR6(100, 150, 1.8);
    modelR6.setSnapshotsFolder("r_1.8/");
    modelR6.setBreakpoints({99, 499, 999});
    modelR6.generateSimulationVideo("videoR6");
    modelR6.simulate(1000);

    ExcitableMediaModel modelR7(100, 150, 1.9);
    modelR7.setSnapshotsFolder("r_1.9/");
    modelR7.setBreakpoints({99, 499, 999});
    modelR7.generateSimulationVideo("videoR7");
    modelR7.simulate(1000);


    std::cout << "Total cells that have been active at least once: R1" << std::endl;
    std::cout << "Timestamp 100: " << modelR1.getEverBeenGrayInBreakpoint()[0] << std::endl;
    std::cout << "Timestamp 500: " << modelR1.getEverBeenGrayInBreakpoint()[1] << std::endl;
    std::cout << "Timestamp 1000: " << modelR1.getEverBeenGrayInBreakpoint()[2] << std::endl;

    std::cout << "Total cells that have been active at least once: R2" << std::endl;
    std::cout << "Timestamp 100: " << modelR2.getEverBeenGrayInBreakpoint()[0] << std::endl;
    std::cout << "Timestamp 500: " << modelR2.getEverBeenGrayInBreakpoint()[1] << std::endl;
    std::cout << "Timestamp 1000: " << modelR2.getEverBeenGrayInBreakpoint()[2] << std::endl;

    std::cout << "Total cells that have been active at least once: R3" << std::endl;
    std::cout << "Timestamp 100: " << modelR3.getEverBeenGrayInBreakpoint()[0] << std::endl;
    std::cout << "Timestamp 500: " << modelR3.getEverBeenGrayInBreakpoint()[1] << std::endl;
    std::cout << "Timestamp 1000: " << modelR3.getEverBeenGrayInBreakpoint()[2] << std::endl;

    std::cout << "Total cells that have been active at least once: R4" << std::endl;
    std::cout << "Timestamp 100: " << modelR4.getEverBeenGrayInBreakpoint()[0] << std::endl;
    std::cout << "Timestamp 500: " << modelR4.getEverBeenGrayInBreakpoint()[1] << std::endl;
    std::cout << "Timestamp 1000: " << modelR4.getEverBeenGrayInBreakpoint()[2] << std::endl;

    std::cout << "Total cells that have been active at least once: R5" << std::endl;
    std::cout << "Timestamp 100: " << modelR5.getEverBeenGrayInBreakpoint()[0] << std::endl;
    std::cout << "Timestamp 500: " << modelR5.getEverBeenGrayInBreakpoint()[1] << std::endl;
    std::cout << "Timestamp 1000: " << modelR5.getEverBeenGrayInBreakpoint()[2] << std::endl;

    std::cout << "Total cells that have been active at least once: R6" << std::endl;
    std::cout << "Timestamp 100: " << modelR6.getEverBeenGrayInBreakpoint()[0] << std::endl;
    std::cout << "Timestamp 500: " << modelR6.getEverBeenGrayInBreakpoint()[1] << std::endl;
    std::cout << "Timestamp 1000: " << modelR6.getEverBeenGrayInBreakpoint()[2] << std::endl;

    std::cout << "Total cells that have been active at least once: R7" << std::endl;
    std::cout << "Timestamp 100: " << modelR7.getEverBeenGrayInBreakpoint()[0] << std::endl;
    std::cout << "Timestamp 500: " << modelR7.getEverBeenGrayInBreakpoint()[1] << std::endl;
    std::cout << "Timestamp 1000: " << modelR7.getEverBeenGrayInBreakpoint()[2] << std::endl;
    return 0;
}
