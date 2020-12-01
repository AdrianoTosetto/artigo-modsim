#ifndef GAS_MODEL_H
#define GAS_MODEL_H

#include "cellular_automata.h"
#include "gas_cell.h"
#include <random>

int position() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 7);

    return distr(gen);
}

class GasModel: public CellularAutomaton<GasCell> {
 public:
    GasModel(uint32_t rows, uint32_t cols):
        CellularAutomaton<GasCell>(rows, cols) {

        }
    uint32_t countParticles() {
        auto count = 0;

        for (auto& cell: grid.rawGridRef()) {
            auto state = cell.state();
            while(state) {
                count = count + (state & 1);
                state >>= 1;
            }
        }
        return count;
    }
    void init() {
        for (auto row = 0; row < 8; row++) {
            for (auto col = 0; col < _cols; col++) {
                const int draw = position();
                if (draw == bTOP_LEFT)
                    getCellRef(row, col).setBitAt<0>(true);
                if (draw == bTOP)
                    getCellRef(row, col).setBitAt<1>(true);
                if (draw == bTOP_RIGHT)
                    getCellRef(row, col).setBitAt<2>(true);
                if (draw == bRIGHT)
                    getCellRef(row, col).setBitAt<3>(true);

                if (draw == bBOTTOM_RIGHT)
                    getCellRef(row, col).setBitAt<4>(true);
                if (draw == bBOTTOM)
                    getCellRef(row, col).setBitAt<5>(true);
                if (draw == bBOTTOM_LEFT)
                    getCellRef(row, col).setBitAt<6>(true);
                if (draw == bLEFT)
                    getCellRef(row, col).setBitAt<7>(true);

            }
        }
    }
    void iterate() {
        display();
        std::cout << "Particles = " << countParticles() << std::endl;
        Grid<GasCell> nextGrid(this->grid);

        /*
            NeighborLocation is the location of the neighbor on the moore neighborhood

        */
        for (auto i = 0; i < _rows; i++) {
            for (auto j = 0; j < _cols; j++) {

                auto& cell = nextGrid.getCellRef(i, j);
                auto neighbors = moore(i, j, 1);
                // t now holds a bool with true if there is a particle 
                // going down (i.e going to south), false otherwise
                bool tGoingB  = neighbors[NeighborLocation::nTOP]
                            .getBitAt<BitDirection::bBOTTOM>();

                bool trGoingBl = neighbors[NeighborLocation::nTOP_RIGHT]
                            .getBitAt<BitDirection::bBOTTOM_LEFT>();

                bool rGoingL  = neighbors[NeighborLocation::nRIGHT]
                            .getBitAt<BitDirection::bLEFT>();

                bool brGoingTl = neighbors[NeighborLocation::nBOTTOM_RIGHT]
                            .getBitAt<BitDirection::bTOP_LEFT>();

                bool bGoingT  = neighbors[NeighborLocation::nBOTTOM]
                            .getBitAt<BitDirection::bTOP>();

                bool blGoingTr = neighbors[NeighborLocation::nBOTTOM_LEFT]
                            .getBitAt<BitDirection::bTOP_RIGHT>();

                bool lGoingR  = neighbors[NeighborLocation::nLEFT]
                            .getBitAt<BitDirection::bRIGHT>();

                bool tlGoingBr = neighbors[NeighborLocation::nTOP_LEFT]
                            .getBitAt<BitDirection::bBOTTOM_RIGHT>();

                cell.setBitAt<bTOP>( // revisado
                    (
                        (
                            !tGoingB && !trGoingBl && rGoingL && !brGoingTl && !bGoingT && 
                            !blGoingTr && lGoingR && !tlGoingBr
                        ) ||
                        (
                            tGoingB && !trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && !tlGoingBr
                        )
                    ) // this expression is for collision
                        ||
                    (
                        bGoingT && !(
                            (tlGoingBr && trGoingBl && bGoingT) && (!tGoingB && !rGoingL && !brGoingTl && !blGoingTr && !lGoingR)
                                ||
                            ((tGoingB && bGoingT) && (!trGoingBl && !rGoingL && !brGoingTl && !blGoingTr && !lGoingR && !tlGoingBr))
                        )
                    )
                );
                cell.setBitAt<bTOP_RIGHT>( // revisado
                    (
                        (
                            !tGoingB && !trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            !blGoingTr && !lGoingR && tlGoingBr
                        ) ||
                        (
                            !tGoingB && trGoingBl && !rGoingL && !brGoingTl && bGoingT && 
                            !blGoingTr && !lGoingR && tlGoingBr
                        ) ||
                        (
                            !tGoingB && trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            !blGoingTr && lGoingR && !tlGoingBr
                        )
                    )
                        ||
                    (
                        blGoingTr && !(
                            ((blGoingTr && trGoingBl) && (!tGoingB && !rGoingL && !brGoingTl && !bGoingT && !lGoingR && !tlGoingBr)) ||
                            ((blGoingTr && tlGoingBr && rGoingL) && (!tGoingB && !trGoingBl && !brGoingTl && !bGoingT && !lGoingR)) ||
                            ((tGoingB && blGoingTr && brGoingTl) && (!trGoingBl && !rGoingL && !bGoingT && !lGoingR && !tlGoingBr))
                        )
                    )
                );

                cell.setBitAt<bRIGHT>(
                    (
                        (
                            tGoingB && !trGoingBl && !rGoingL && !brGoingTl && bGoingT && 
                            !blGoingTr && !lGoingR && !tlGoingBr
                        ) ||
                        (
                            !tGoingB && !trGoingBl && rGoingL && !brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && tlGoingBr
                        )
                    )
                        ||
                    (
                        lGoingR && !(
                            ((lGoingR && rGoingL) && (!tGoingB && !trGoingBl && !brGoingTl && !bGoingT && !blGoingTr && !tlGoingBr)) ||
                            ((lGoingR && trGoingBl && brGoingTl) && (!tGoingB && !rGoingL && !bGoingT && !blGoingTr && !tlGoingBr))
                        )
                    )
                );

                cell.setBitAt<bBOTTOM_RIGHT>( // revisado
                    (
                        (
                            !tGoingB && trGoingBl && !rGoingL && !brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && !tlGoingBr
                        ) ||
                        (
                            tGoingB && !trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && !tlGoingBr
                        ) ||
                        (
                            !tGoingB && trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            !blGoingTr && lGoingR && !tlGoingBr
                        )
                    ) ||
                    (
                        tlGoingBr && !(
                            ((tlGoingBr && brGoingTl) && (!tGoingB && !trGoingBl && !rGoingL && !bGoingT && !blGoingTr && !lGoingR)) ||
                            ((tlGoingBr && rGoingL && blGoingTr) && (!tGoingB && !trGoingBl && !brGoingTl && !bGoingT && !lGoingR)) ||
                            ((tlGoingBr && trGoingBl && bGoingT) && (!tGoingB && !rGoingL && !brGoingTl && !blGoingTr && !lGoingR))
                        )
                    )
                );

                cell.setBitAt<bBOTTOM>( // revisar
                    (
                        (
                            !tGoingB && !trGoingBl && rGoingL && !brGoingTl && !bGoingT && 
                            !blGoingTr && lGoingR && !tlGoingBr //   ok
                        ) ||
                        (
                            !tGoingB && trGoingBl && !rGoingL && !brGoingTl && bGoingT && 
                            !blGoingTr && !lGoingR && tlGoingBr
                        )
                    )
                        ||
                    (
                        tGoingB && !(
                            ((tGoingB && bGoingT) && (!trGoingBl && !rGoingL && !brGoingTl && !blGoingTr && !lGoingR && !tlGoingBr))
                                ||
                            ((tGoingB && blGoingTr && brGoingTl) && (!trGoingBl && !rGoingL && !bGoingT && !lGoingR && !tlGoingBr))
                        )
                    )
                );

                cell.setBitAt<bBOTTOM_LEFT>(
                    (
                        (
                            !tGoingB && !trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            !blGoingTr && !lGoingR && tlGoingBr // ok 
                        ) ||
                        (
                            tGoingB && !trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && !tlGoingBr // ok
                        ) ||
                        (
                            !tGoingB && !trGoingBl && rGoingL && !brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && tlGoingBr // ok
                        )
                    ) ||
                    (
                        trGoingBl && !(
                            ((trGoingBl && blGoingTr) && (!tGoingB && !rGoingL && !brGoingTl && !bGoingT && !lGoingR && !tlGoingBr)) ||
                            ((trGoingBl && tlGoingBr && bGoingT) && (!tGoingB && !rGoingL && !brGoingTl && !blGoingTr && !lGoingR)) ||
                            ((lGoingR && trGoingBl && brGoingTl) && (!tGoingB && !rGoingL && !bGoingT && !blGoingTr && !tlGoingBr))
                        )
                    )
                );

                cell.setBitAt<bLEFT>(
                    (
                        (
                            tGoingB && !trGoingBl && !rGoingL && !brGoingTl && bGoingT && 
                            !blGoingTr && !lGoingR && !tlGoingBr // ok
                        ) ||
                        (
                            !tGoingB && trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            !blGoingTr && lGoingR && !tlGoingBr // ok
                        )

                    )
                        ||
                    (
                        rGoingL && !(
                            ((rGoingL && lGoingR) && (!tGoingB && !trGoingBl && !brGoingTl && !bGoingT && !blGoingTr && !tlGoingBr)) ||
                            ((rGoingL && tlGoingBr && blGoingTr) && (!tGoingB && !trGoingBl && !brGoingTl && !bGoingT && !lGoingR))
                        )
                    )
                );

                cell.setBitAt<bTOP_LEFT>( // revisado
                    (
                        (
                            !tGoingB && trGoingBl && !rGoingL && !brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && !tlGoingBr // ok
                        ) ||
                        (
                            !tGoingB && trGoingBl && !rGoingL && !brGoingTl && bGoingT && 
                            !blGoingTr && !lGoingR && tlGoingBr // ok
                        ) ||
                        (
                            !tGoingB && !trGoingBl && rGoingL && !brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && tlGoingBr // ok
                        )
                    ) ||
                    (
                        brGoingTl && !(
                            ((brGoingTl && tlGoingBr) && (!tGoingB && !trGoingBl && !rGoingL && !bGoingT && !blGoingTr && !lGoingR)) ||
                            ((lGoingR && trGoingBl && brGoingTl) && (!tGoingB && !rGoingL && !bGoingT && !blGoingTr && !tlGoingBr)) ||
                            ((brGoingTl && tGoingB && blGoingTr) && (!trGoingBl && !rGoingL && !bGoingT && !lGoingR && !tlGoingBr))
                        )
                    )
                );
            }
        }

        grid = nextGrid;
    }

    void update() {
        iterate();
    }

};

#endif