#include <iostream>
#include <thread>
#include "gas_model_v2.h"

int main(int argc, char const *argv[])
{
    GasModel gm(10,10);
    
    // caso #1 ==============================================
    // gm.getCellRef(2,2).setBitAt<bBOTTOM_RIGHT>(true);
    // gm.getCellRef(4,2).setBitAt<bRIGHT>(true);
    // gm.getCellRef(2,6).setBitAt<bBOTTOM_LEFT>(true);
    // gm.getCellRef(6,2).setBitAt<bTOP_RIGHT>(true);
    // gm.getCellRef(6,6).setBitAt<bTOP_LEFT>(true);

    // caso #1.5 ==============================================
    // gm.getCellRef(2,2).setBitAt<bBOTTOM_RIGHT>(true);
    // gm.getCellRef(4,6).setBitAt<bLEFT>(true);
    // gm.getCellRef(2,6).setBitAt<bBOTTOM_LEFT>(true);
    // gm.getCellRef(6,2).setBitAt<bTOP_RIGHT>(true);
    // gm.getCellRef(6,6).setBitAt<bTOP_LEFT>(true);
    // =====================================================
    // caso #2 =============================================
    // gm.getCellRef(3,3).setBitAt<bBOTTOM_RIGHT>(true);
    // gm.getCellRef(5,3).setBitAt<bTOP_RIGHT>(true);
    // gm.getCellRef(4,5).setBitAt<bLEFT>(true);
    // =====================================================


    // caso #3 ============================================
    // gm.getCellRef(3,3).setBitAt<bBOTTOM>(true);
    // gm.getCellRef(7,3).setBitAt<bTOP>(true);
    // ====================================================

    // caso #4
    // gm.getCellRef(3, 4).setBitAt<bLEFT>(true);
    // gm.getCellRef(4, 4).setBitAt<bTOP_LEFT>(true);
    // gm.getCellRef(4, 3).setBitAt<bTOP>(true);
    // ====================================================

    // gm.getCellRef(8, 8).setBitAt<bTOP>(true);
    // gm.getCellRef(6, 6).setBitAt<bBOTTOM>(true);
    // gm.getCellRef(8, 6).setBitAt<bTOP>(true);
    // caso #5
    // gm.getCellRef(3, 2).setBitAt<bRIGHT>(true);
    // gm.getCellRef(2, 4).setBitAt<bBOTTOM_LEFT>(true);
    // gm.getCellRef(4, 4).setBitAt<bTOP_LEFT>(true);


    // caso #6 ==========================================
    // gm.getCellRef(1,3).setBitAt<bBOTTOM>(true);
    // gm.getCellRef(1,5).setBitAt<bBOTTOM_LEFT>(true);
    // gm.getCellRef(3,5).setBitAt<bLEFT>(true);
    // gm.getCellRef(5,5).setBitAt<bTOP_LEFT>(true);
    // gm.getCellRef(5,3).setBitAt<bTOP>(true);
    // gm.getCellRef(5,1).setBitAt<bTOP_RIGHT>(true);
    // gm.getCellRef(3,1).setBitAt<bRIGHT>(true);
    // gm.getCellRef(1,1).setBitAt<bBOTTOM_RIGHT>(true);
    // ==================================================

    // caso #7 ==========================================
    // gm.getCellRef(1,3).setBitAt<bBOTTOM>(true);
    // gm.getCellRef(1,5).setBitAt<bBOTTOM_LEFT>(true);
    // gm.getCellRef(3,5).setBitAt<bLEFT>(true);
    // gm.getCellRef(5,5).setBitAt<bTOP_LEFT>(true);
    // gm.getCellRef(5,3).setBitAt<bTOP>(true);
    // gm.getCellRef(5,1).setBitAt<bTOP_RIGHT>(true);
    // gm.getCellRef(3,1).setBitAt<bRIGHT>(true);
    // gm.getCellRef(1,1).setBitAt<bBOTTOM_RIGHT>(true);
    // ==================================================
    //gm.init();
    // gm.getCellRef(0,0).setBitAt<bTOP_LEFT>(true);
    // gm.getCellRef(0,1).setBitAt<bRIGHT>(true);
    // gm.getCellRef(0,2).setBitAt<bLEFT>(true);

    // gm.getCellRef(1,0).setBitAt<bBOTTOM>(true);
    // gm.getCellRef(1,1).setBitAt<bRIGHT>(true);
    // gm.getCellRef(1,2).setBitAt<bTOP>(true);

    // gm.getCellRef(2,0).setBitAt<bRIGHT>(true);
    // gm.getCellRef(2,1).setBitAt<bTOP_RIGHT>(true);
    // gm.getCellRef(2,2).setBitAt<bLEFT>(true);

    // gm.getCellRef(4, 2).setBitAt<bRIGHT>(true);
    // gm.getCellRef(4, 6).setBitAt<bLEFT>(true);
    // gm.getCellRef(6, 4).setBitAt<bTOP>(true);
    gm.init();
    gm.display();
    std::cout << gm.countParticles() << std::endl;
    std::cout << "====================" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    gm.simulate(2000);

    return 0;
}
