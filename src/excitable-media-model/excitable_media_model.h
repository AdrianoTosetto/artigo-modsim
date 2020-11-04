#ifndef EXCITABLE_MEDIA_MODEL_H
#define EXCITABLE_MEDIA_MODEL_H

#include <iostream>
#include <cmath>

#include "cellular_automata.h"
#include "excitable_media_cell.h"

class ExcitableMediaModel: public CellularAutomaton<ExcitableMediaCell> {
 public:
    ExcitableMediaModel(uint32_t rows, uint32_t cols): 
        CellularAutomaton<ExcitableMediaCell>(rows, cols) {
            grid.set(rows, cols);
            uint32_t cRow = 0;
            uint32_t cCol = -1;
            std::generate(
                grid.rawGridRef().begin(),
                grid.rawGridRef().end(),
                [&cRow, &cCol, cols]() {
                    if (cCol == cols - 1) {
                        cCol = 0;
                        cRow++;
                    } else {
                        cCol++;
                    }
                    return ExcitableMediaCell(cRow, cCol);
                }
            );
        }
    std::vector<ExcitableMediaCell> getMooreNeighborhoodPerturbed
        (uint32_t row, uint32_t col, const double radius) const {

        uint32_t iradius = static_cast<int>(ceil(radius));
        auto neighbors = getMooreNeighborhood(row, col, iradius, true);
        auto cell = getCellValue(row, col);
        for (const auto& n: neighbors) {
            std::cout << cell.distance(n);
        }
    }
    virtual void update() {}

    ~ExcitableMediaModel() {}
};

#endif