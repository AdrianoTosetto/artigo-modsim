#ifndef EXCITABLE_MEDIA_MODEL_H
#define EXCITABLE_MEDIA_MODEL_H

#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

#include "cellular_automata.h"
#include "excitable_media_cell.h"

class ExcitableMediaModel: public CellularAutomaton<ExcitableMediaCell<>> {
 public:
    ExcitableMediaModel(uint32_t rows, uint32_t cols): 
        CellularAutomaton<ExcitableMediaCell<>>(rows, cols) {
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
                    if (cRow < 3)
                        return ExcitableMediaCell<>(1, cRow, cCol);
                    else
                        return ExcitableMediaCell<>(cRow, cCol);
                }
            );
        }
    std::vector<ExcitableMediaCell<12, 13>> getMooreNeighborhoodPerturbed
        (uint32_t row, uint32_t col, const double radius) const {

        std::vector<ExcitableMediaCell<>> ret;

        uint32_t iradius = static_cast<int>(ceil(radius)) + 1;
        auto neighbors = getMooreNeighborhood(row, col, iradius, true);
        auto cell = getCellValue(row, col);
        for (const auto& n: neighbors)
            if (cell.distance(n) < radius) {
                ret.push_back(n);
            }

        return ret;
    }

    inline double excitedCellsSum(const std::vector<ExcitableMediaCell<12, 13>>& neighbors) {
        auto sum = 0.0;
        for (auto& neighbor: neighbors) {
            if (neighbor.excited()) 
                sum += neighbor.weight();
        }
        return sum;
    }

    inline double nonExcitedCellsSum(const std::vector<ExcitableMediaCell<12, 13>>& neighbors) {
        auto sum = 0.0;
        for (auto& neighbor: neighbors) {
            //std::cout << "w = " << neighbor.weight() << std::endl;
            if (neighbor.nonExcited() || neighbor.refractory())
                sum += neighbor.weight();
        }
        return sum;
    }

    void iterate() {
        Grid<ExcitableMediaCell<12, 13>> nextGrid(this->grid);

        for (auto i = 0; i < _rows; i++) {
            for (auto j = 0; j < _cols; j++) {
                auto neighbors = getMooreNeighborhoodPerturbed(i, j, 2);
                double temp = excitedCellsSum(neighbors) / nonExcitedCellsSum(neighbors);
                auto& cell = nextGrid.getCellRef(i, j);
                cell.update(temp);
            }
        }
        this->grid = nextGrid;
    }

    virtual void update() {
        iterate();
        // std::cout << "================================================" << std::endl;
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        // display();
    }
    
    ~ExcitableMediaModel() {}
};

#endif