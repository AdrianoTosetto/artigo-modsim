#include <iostream>
#include "turing_patterns_model.h"
#include "model_factory.h"
#include "cellular_automata.h"

int main(int argc, char const *argv[])
{
    /*TuringPatternsModel tpm(100, 25);
    //tpm.display();
    tpm.setBreakpoints({0, 50, 75, 100, 125, 150, 175, 200, 300, 350, 400});
    tpm.display();
    tpm.simulate(200);
    std::cout << "===========================" << std::endl;
    tpm.display();*/
    /*ModelFactory factory(10, 10);
    factory.setDCCells({
        position(1,2)
    });
    auto& model = factory.model();
    model.display();*/
    TuringPatternsModel<Area_Policy::Ellipse> tpm(400, 400);
    tpm.setBreakpoints({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 50, 75, 100, 125, 150, 175, 200, 300, 350, 400});
    tpm.setSnapshotsFolder("test/");
    tpm.setEllipses(2.30, 1.38, 3.61, 6.01);
    tpm.setWeights(1, -0.1);
    tpm.simulate(400);
    // TuringPatternsModel ca(10, 10);

    // ca.getCellRef(1, 9).setType(CellType::DC);
    // ca.getCellRef(0, 9).setType(CellType::DC);
    // ca.getCellRef(0, 8).setType(CellType::DC);
    // ca.getCellRef(1, 8).setType(CellType::DC);
    // ca.getCellRef(2, 8).setType(CellType::DC);
    // ca.getCellRef(2, 9).setType(CellType::DC);

    // ca.getCellRef(0, 0).setType(CellType::DC);
    // ca.getCellRef(1, 0).setType(CellType::DC);
    // ca.getCellRef(2, 0).setType(CellType::DC);
    // ca.display();
    // ca.getCellRef(5, 5).setType(CellType::DC);
    // ca.getCellRef(4, 4).setType(CellType::DC);
    // ca.getCellRef(4, 5).setType(CellType::DC);
    // ca.getCellRef(4, 6).setType(CellType::DC);
    // //ca.getCellRef(9, 5).setType(CellType::DC);
    // ca.getCellRef(6, 5).setType(CellType::DC);
    // //ca.getCellRef(9, 6).setType(CellType::DC);

    // std::cout << ca.getCellRef(5, 5).realPositionX() << std::endl;
    // std::cout << ca.getCellRef(5, 5).realPositionY() << std::endl;

    // std::cout << ca.getCellRef(6, 5).realPositionX() << std::endl;
    // std::cout << ca.getCellRef(6, 5).realPositionY() << std::endl;
    // std::cout << "d = " << ca.getCellRef(5,5).distance(ca.getCellRef(6,5));

    // ca.display();
    // auto nss = ca.moore(1, 9, 1);
    // for (auto n: nss) {
    //     std::cout << "row = " << n.row() << " col = " << n.col();
    //     std::cout << " vrow = " << n.rowV() << " vcol = " << n.colV() << " | ";
    //     std::cout << n.isVirtual() << " | " << n;
    //     std::cout << "d = " << ca.getCellRef(5,5).distance(n) << std::endl;
    // }
    // // //auto ns = ca.getNeighbors(0, 0, NDIRECTION::TOP, 2);

    return 0;
}
