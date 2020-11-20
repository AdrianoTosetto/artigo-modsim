#include <iostream>
#include "excitable_media_model.h"

int main(int argc, char const *argv[])
{

    ExcitableMediaModel modelR1(100, 150, 1.3);
    modelR1.setSnapshotsFolder("r_1.3/");
    modelR1.setBreakpoints({0, 25, 50, 100, 200, 500, 999});
    modelR1.simulate(1000);
    modelR1.saveEverBeenActive("hasEverBeenActive");

    ExcitableMediaModel modelR2(100, 150, 1.4);
    modelR2.setSnapshotsFolder("r_1.4/");
    modelR2.setBreakpoints({0, 25, 50, 100, 200, 500, 999});
    modelR2.simulate(1000);
    modelR2.saveEverBeenActive("hasEverBeenActive");

    ExcitableMediaModel modelR3(100, 150, 1.5);
    modelR3.setSnapshotsFolder("r_1.5/");
    modelR3.setBreakpoints({0, 25, 50, 100, 200, 500, 999});
    modelR3.simulate(1000);
    modelR3.saveEverBeenActive("hasEverBeenActive");

    ExcitableMediaModel modelR4(100, 150, 1.6);
    modelR4.setSnapshotsFolder("r_1.6/");
    modelR4.setBreakpoints({0, 25, 50, 100, 200, 500, 999});
    modelR4.simulate(1000);
    modelR4.saveEverBeenActive("hasEverBeenActive");

    ExcitableMediaModel modelR5(100, 150, 1.8);
    modelR5.setSnapshotsFolder("r_1.8/");
    modelR5.setBreakpoints({0, 25, 50, 100, 200, 500, 999});
    modelR5.simulate(1000);
    modelR5.saveEverBeenActive("hasEverBeenActive");

    return 0;
}
