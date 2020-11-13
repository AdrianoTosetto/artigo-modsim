#include <iostream>
#include "excitable_media_model.h"

int main(int argc, char const *argv[])
{
    ExcitableMediaModel model(100, 150);
    model.display();
    std::cout << "x 2,2: " << model.getCellRef(2, 2).realPositionX() << std::endl;
    std::cout << "y 2,2: " << model.getCellRef(2, 2).realPositionY() << std::endl;

    std::cout << "x 3,3: " << model.getCellRef(3, 3).realPositionX() << std::endl;
    std::cout << "y 3,3: " << model.getCellRef(3, 3).realPositionY() << std::endl;

    std::cout << "d = " << model.getCellRef(2, 2).distance(model.getCellRef(3, 3)) << std::endl;
    std::cout << "d = " << model.getCellRef(3, 3).distance(model.getCellRef(2, 2)) << std::endl;
    model.setBreakpoints({0, 25, 50, 100, 200, 500, 999});
    model.simulate(1000);
    //std::cout << model.getCellValue(4,1).state() << std::endl;
    // ExcitableMediaCell<12, 13> cell(9090, 0, 0);
    // std::cout << cell.weight() << std::endl;
    // std::cout << uniformDistribution1(-0.5, 1.5) << std::endl;
    // std::cout << uniformDistribution1(0.5, 1.5) << std::endl;
    return 0;
}
