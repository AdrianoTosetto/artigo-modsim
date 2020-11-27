#include <iostream>
#include <thread>

#include "gas_model.h"

int main(int argc, char const *argv[])
{
    GasModel gm(100,100);
    gm.init();
    gm.display();
    std::cout << gm.countParticles() << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "====================" << std::endl;
    gm.simulate(3000);

    return 0;
}
