#include <iostream>
#include "excitable_media_model.h"

int main(int argc, char const *argv[])
{
    ExcitableMediaModel model(10, 10);
    model.display();
    std::cout << "x 2,2: " << model.getCellRef(2, 2).realPositionX() << std::endl;
    std::cout << "y 2,2: " << model.getCellRef(2, 2).realPositionY() << std::endl;

    std::cout << "x 3,3: " << model.getCellRef(3, 3).realPositionX() << std::endl;
    std::cout << "y 3,3: " << model.getCellRef(3, 3).realPositionY() << std::endl;

    std::cout << "d = " << model.getCellRef(2, 2).distance(model.getCellRef(3, 3)) << std::endl;
    std::cout << "d = " << model.getCellRef(3, 3).distance(model.getCellRef(2, 2)) << std::endl;
    return 0;
}
