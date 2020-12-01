#ifndef GAS_MODEL_H
#define GAS_MODEL_H

#include "cellular_automata.h"
#include "gas_cell.h"
#include <random>
#include <array>
//#include <utility>

double_t randomProbability() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> distr(0, 1);

    return distr(gen);
}

int position() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, 7);

    return distr(gen);
}

typedef std::array<uint32_t, 4> macroBlockPosition;

class GasModel: public CellularAutomaton<GasCell> {
 private:
    std::vector<macroBlockPosition> macroblocks;
    /**
     * standard deviation from each macroblock at the
     * timestamp t
     */
    std::vector<double> standardDeviation;
    /**
     * total particles at a given timestamp t
     * it should be equal for each timestamp, otherwise
     * this implementation of gas model is wrong
    */
    std::vector<uint32_t> _totalParticles;
    /**
     * totalParticlesInMacroblock[4][2] -> returns the total
     * particles of macroblock 2 at timestamp 4
     * It works with the breakpoints, it means,
     * if breakpoints are {1, 2, 100} totalParticlesInMacroblockAtTimestamp vector
     * will store the total particles in each macroblock at timestamps 1, 2 and 100
     * 
    */
    std::vector<std::vector<uint32_t>> totalParticlesInMacroblockAtTimestamp;

 public:
    GasModel(uint32_t rows, uint32_t cols):
        CellularAutomaton<GasCell>(rows, cols) {}

    std::vector<uint32_t> getTotalParticles() const {
        return _totalParticles;
    }

    std::vector<double> getStandardDeviations() const {
        return standardDeviation;
    }

    std::vector<std::vector<uint32_t>> getTotalParticlesInMacroblockAtTimestamp() const {
        return totalParticlesInMacroblockAtTimestamp;
    }

    // the raw implementation of this function assumes that _rows = _cols
    void setMacroblocks(uint32_t macroblockSize) {
        uint32_t macroBlocksN = _rows / macroblockSize;
        for (auto i = 0; i < macroBlocksN; i++) {
            for (auto j = 0; j < macroBlocksN; j++) {

                auto startRow = i * macroblockSize;
                auto startCol = j * macroblockSize;

                auto endRow = (i+1) * macroblockSize;
                auto endCol = (j+1) * macroblockSize;

                macroBlockPosition position = {startRow, startCol, endRow, endCol};

                macroblocks.push_back(position);
 
            }
        }
    }

    std::vector<GasCell> getMacroblockCells(uint32_t macroblock) {
        std::vector<GasCell> ret;

        auto offsets = macroblocks[macroblock];
        auto startRow = offsets[0];
        auto startCol = offsets[1];

        auto endRow = offsets[2];
        auto endCol = offsets[3];

        for (auto row = startRow; row < endRow; row++) {
            for (auto col = startCol; col < endCol; col++)
                ret.push_back(grid.getCellValue(row, col));
        }

        return ret;
    }

    uint32_t countParticles(uint32_t macroblock) {
        auto cells = getMacroblockCells(macroblock);
        auto count = 0;

        for (auto& cell: cells )
            count += countParticlesInCell(cell);

        return count;
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
    inline uint32_t countParticlesInCell(const GasCell& cell) {
        auto count = 0;
        auto state = cell.state();
        while (state) {
            count = count + (state & 1);
            state >>= 1;
        }

        return count;
    }
    inline void setRandomBitDirection(uint32_t row, uint32_t col) {
        auto& cell = getCellRef(row, col);
        const int draw = position();

        if (draw == bTOP_LEFT)
            cell.setBitAt<bTOP_LEFT>(true);
        if (draw == bTOP)
            cell.setBitAt<bTOP>(true);
        if (draw == bTOP_RIGHT)
            cell.setBitAt<bTOP_RIGHT>(true);
        if (draw == bRIGHT)
            cell.setBitAt<bRIGHT>(true);

        if (draw == bBOTTOM_RIGHT)
            cell.setBitAt<bBOTTOM_RIGHT>(true);
        if (draw == bBOTTOM)
            cell.setBitAt<bBOTTOM>(true);
        if (draw == bBOTTOM_LEFT)
            cell.setBitAt<bBOTTOM_LEFT>(true);
        if (draw == bLEFT)
            cell.setBitAt<bLEFT>(true);
    }
    void init() {

        for (auto row = 20; row <= 90; row+=2) {
            for (auto col = 200; col < 280; col+=2) {
                if (randomProbability() <= 0.5) {
                    setRandomBitDirection(row, col);
                }
            }
        }

        for (auto row = 210; row < 280; row+=2) {
            for (auto col = 200; col < 280; col+=2) {
                if (randomProbability() <= 0.5) {
                    setRandomBitDirection(row, col);
                }
            }
        }
    }
    void initMiddle () {
        for (auto col = 0; col < _cols; col++)
            getCellRef(90, col).setIsSolid(true);
        for (auto col = 0; col < _cols; col++)
            getCellRef(110, col).setIsSolid(true);
    }
    void setSquareSolid() {
        for (auto col = 10; col < _cols - 10; col++)
            getCellRef(10, col).setIsSolid(true);

        for (auto row = 10; row < _rows-10; row++)
            getCellRef(row, _cols-10).setIsSolid(true);

        for (auto col = _cols-10; col >= 10; col--)
            getCellRef(_rows-10, col).setIsSolid(true);

        for (auto row = 10; row < _rows - 10; row++)
            getCellRef(row, 10).setIsSolid(true);
    }
    void setSquareWithOpenWallMiddle() {
        setSquareSolid();
        for (auto row = 10; row <= 125; row++)
            getCellRef(row, 149).setIsSolid(true);
    
        for (auto row = 175; row <= _rows - 10; row++)
            getCellRef(row, 149).setIsSolid(true);
    }

    void generateMetaData() {
        auto mean = 
            static_cast<double>(countParticles()) / macroblocks.size();

        auto sum = 0.0;
        auto totalParticles = 0;

        std::vector<uint32_t> totalParticlesInMacroblock;
        // standard deviation for every macroblock at timestamp t
        // and couting of how many particles exist in this macroblock
        for (auto i = 0; i < macroblocks.size(); i++) {
            auto particlesInMacroblock = countParticles(i);

            totalParticlesInMacroblock.push_back(particlesInMacroblock);
            sum += std::pow(particlesInMacroblock - mean, 2);

            totalParticles += particlesInMacroblock;

        }
        auto sd = sqrt(sum / macroblocks.size());
        standardDeviation.push_back(sd);

        _totalParticles.push_back(totalParticles);
        totalParticlesInMacroblockAtTimestamp.push_back(totalParticlesInMacroblock);
    }
    void iterate() {
        //display();
        // std::cout << "Particles = " << countParticles() << std::endl;
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
                    (cell.isSolid() && tGoingB) ||
                    ((
                        (
                            !tGoingB && !trGoingBl && rGoingL && !brGoingTl && !bGoingT && 
                            !blGoingTr && lGoingR && !tlGoingBr && !cell.isSolid()
                        ) ||
                        (
                            tGoingB && !trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && !tlGoingBr && !cell.isSolid()
                        )
                    ) // this expression is for collision
                        ||
                    (
                        !cell.isSolid() && bGoingT && !(
                            (tlGoingBr && trGoingBl && bGoingT) && (!tGoingB && !rGoingL && !brGoingTl && !blGoingTr && !lGoingR)
                                ||
                            ((tGoingB && bGoingT) && (!trGoingBl && !rGoingL && !brGoingTl && !blGoingTr && !lGoingR && !tlGoingBr))
                        )
                    ))
                );
                cell.setBitAt<bTOP_RIGHT>( // revisado
                    (cell.isSolid() && trGoingBl) ||
                    ((
                        (
                            !tGoingB && !trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            !blGoingTr && !lGoingR && tlGoingBr && !cell.isSolid()
                        ) ||
                        (
                            !tGoingB && trGoingBl && !rGoingL && !brGoingTl && bGoingT && 
                            !blGoingTr && !lGoingR && tlGoingBr && !cell.isSolid()
                        ) ||
                        (
                            !tGoingB && trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            !blGoingTr && lGoingR && !tlGoingBr && !cell.isSolid()
                        )
                    )
                        ||
                    (
                        !cell.isSolid() && blGoingTr && !(
                            ((blGoingTr && trGoingBl) && (!tGoingB && !rGoingL && !brGoingTl && !bGoingT && !lGoingR && !tlGoingBr)) ||
                            ((blGoingTr && tlGoingBr && rGoingL) && (!tGoingB && !trGoingBl && !brGoingTl && !bGoingT && !lGoingR)) ||
                            ((tGoingB && blGoingTr && brGoingTl) && (!trGoingBl && !rGoingL && !bGoingT && !lGoingR && !tlGoingBr))
                        )
                    ))
                );

                cell.setBitAt<bRIGHT>(
                    (cell.isSolid() && rGoingL) ||
                    ((
                        (
                            tGoingB && !trGoingBl && !rGoingL && !brGoingTl && bGoingT && 
                            !blGoingTr && !lGoingR && !tlGoingBr && !cell.isSolid()
                        ) ||
                        (
                            !tGoingB && !trGoingBl && rGoingL && !brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && tlGoingBr && !cell.isSolid()
                        )
                    )
                        ||
                    (
                        !cell.isSolid() && lGoingR && !(
                            ((lGoingR && rGoingL) && (!tGoingB && !trGoingBl && !brGoingTl && !bGoingT && !blGoingTr && !tlGoingBr)) ||
                            ((lGoingR && trGoingBl && brGoingTl) && (!tGoingB && !rGoingL && !bGoingT && !blGoingTr && !tlGoingBr))
                        )
                    ))
                );

                cell.setBitAt<bBOTTOM_RIGHT>( // revisado
                    (cell.isSolid() && brGoingTl) ||
                    ((
                        (
                            !tGoingB && trGoingBl && !rGoingL && !brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && !tlGoingBr && !cell.isSolid()
                        ) ||
                        (
                            tGoingB && !trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && !tlGoingBr && !cell.isSolid()
                        ) ||
                        (
                            !tGoingB && trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            !blGoingTr && lGoingR && !tlGoingBr && !cell.isSolid()
                        )
                    ) ||
                    (
                        !cell.isSolid() && tlGoingBr && !(
                            ((tlGoingBr && brGoingTl) && (!tGoingB && !trGoingBl && !rGoingL && !bGoingT && !blGoingTr && !lGoingR)) ||
                            ((tlGoingBr && rGoingL && blGoingTr) && (!tGoingB && !trGoingBl && !brGoingTl && !bGoingT && !lGoingR)) ||
                            ((tlGoingBr && trGoingBl && bGoingT) && (!tGoingB && !rGoingL && !brGoingTl && !blGoingTr && !lGoingR))
                        )
                    ))
                );

                cell.setBitAt<bBOTTOM>( // revisar
                    (cell.isSolid() && bGoingT) ||
                    ((
                        (
                            !tGoingB && !trGoingBl && rGoingL && !brGoingTl && !bGoingT && 
                            !blGoingTr && lGoingR && !tlGoingBr && !cell.isSolid()
                        ) ||
                        (
                            !tGoingB && trGoingBl && !rGoingL && !brGoingTl && bGoingT && 
                            !blGoingTr && !lGoingR && tlGoingBr && !cell.isSolid()
                        )
                    )
                        ||
                    (
                        !cell.isSolid() && tGoingB && !(
                            ((tGoingB && bGoingT) && (!trGoingBl && !rGoingL && !brGoingTl && !blGoingTr && !lGoingR && !tlGoingBr))
                                ||
                            ((tGoingB && blGoingTr && brGoingTl) && (!trGoingBl && !rGoingL && !bGoingT && !lGoingR && !tlGoingBr))
                        )
                    ))
                );

                cell.setBitAt<bBOTTOM_LEFT>(
                    (cell.isSolid() && blGoingTr) ||
                    ((
                        (
                            !tGoingB && !trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            !blGoingTr && !lGoingR && tlGoingBr && !cell.isSolid() // ok 
                        ) ||
                        (
                            tGoingB && !trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && !tlGoingBr && !cell.isSolid() // ok
                        ) ||
                        (
                            !tGoingB && !trGoingBl && rGoingL && !brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && tlGoingBr && !cell.isSolid() // ok
                        )
                    ) ||
                    (
                        !cell.isSolid() && trGoingBl && !(
                            ((trGoingBl && blGoingTr) && (!tGoingB && !rGoingL && !brGoingTl && !bGoingT && !lGoingR && !tlGoingBr)) ||
                            ((trGoingBl && tlGoingBr && bGoingT) && (!tGoingB && !rGoingL && !brGoingTl && !blGoingTr && !lGoingR)) ||
                            ((lGoingR && trGoingBl && brGoingTl) && (!tGoingB && !rGoingL && !bGoingT && !blGoingTr && !tlGoingBr))
                        )
                    ))
                );

                cell.setBitAt<bLEFT>(
                    (cell.isSolid() && lGoingR) ||
                    ((
                        (
                            tGoingB && !trGoingBl && !rGoingL && !brGoingTl && bGoingT && 
                            !blGoingTr && !lGoingR && !tlGoingBr && !cell.isSolid() // ok
                        ) ||
                        (
                            !tGoingB && trGoingBl && !rGoingL && brGoingTl && !bGoingT && 
                            !blGoingTr && lGoingR && !tlGoingBr && !cell.isSolid() // ok
                        )

                    )
                        ||
                    (
                        !cell.isSolid() && rGoingL && !(
                            ((rGoingL && lGoingR) && (!tGoingB && !trGoingBl && !brGoingTl && !bGoingT && !blGoingTr && !tlGoingBr)) ||
                            ((rGoingL && tlGoingBr && blGoingTr) && (!tGoingB && !trGoingBl && !brGoingTl && !bGoingT && !lGoingR))
                        )
                    ))
                );

                cell.setBitAt<bTOP_LEFT>( // revisado
                    (cell.isSolid() && tlGoingBr) ||
                    ((
                        (
                            !tGoingB && trGoingBl && !rGoingL && !brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && !tlGoingBr && !cell.isSolid() // ok
                        ) ||
                        (
                            !tGoingB && trGoingBl && !rGoingL && !brGoingTl && bGoingT && 
                            !blGoingTr && !lGoingR && tlGoingBr && !cell.isSolid() // ok
                        ) ||
                        (
                            !tGoingB && !trGoingBl && rGoingL && !brGoingTl && !bGoingT && 
                            blGoingTr && !lGoingR && tlGoingBr //&& !cell.isSolid()// ok
                        )
                    ) ||
                    (
                        !cell.isSolid() && brGoingTl && !(
                            ((brGoingTl && tlGoingBr) && (!tGoingB && !trGoingBl && !rGoingL && !bGoingT && !blGoingTr && !lGoingR)) ||
                            ((lGoingR && trGoingBl && brGoingTl) && (!tGoingB && !rGoingL && !bGoingT && !blGoingTr && !tlGoingBr)) ||
                            ((brGoingTl && tGoingB && blGoingTr) && (!trGoingBl && !rGoingL && !bGoingT && !lGoingR && !tlGoingBr))
                        )
                    ))
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