#include <iostream>
#include "host_pathogen_ca.h"

int main(int argc, char const *argv[])
{
    HostPathogen hp(15, 15);
    hp.simulate(100);
    return 0;
}
