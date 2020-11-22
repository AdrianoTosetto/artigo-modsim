#ifndef TURING_PATTERNS_MODEL_H
#define TURING_PATTERNS_MODEL_H

#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <functional>

#include "cellular_automata.h"
#include "turing_patterns_cell.h"
#include "utils.h"

class Area_Policy {
 public:
    class Circle {};
    class Ellipse {};
};

template <typename Policy = Area_Policy::Circle>
class TuringPatternsModel: public CellularAutomaton<TuringPatternsCell> {
 public:
    double calculateSum(uint32_t, uint32_t);

    TuringPatternsModel(uint32_t rows, uint32_t cols): 
        CellularAutomaton<TuringPatternsCell>(rows, cols) {

            grid.set(rows, cols);
            _w2 = -0.34;
            uint32_t cRow = 0;
            uint32_t cCol = -1;
            std::generate (
                grid.rawGridRef().begin(),
                grid.rawGridRef().end(),
                [&cRow, &cCol, cols]() {
                    auto draw = uniformDistribution(0, 1);
                    CellType cellType;
                    if (draw <= 0.1)
                        cellType = CellType::DC;
                    else
                        cellType = CellType::UC;

                    if (cCol == cols - 1) {
                        cCol = 0;
                        cRow++;
                    } else {
                        cCol++;
                    }
                    return TuringPatternsCell(cRow, cCol, cellType);
                }
            );

    }
    TuringPatternsModel(uint32_t rows, uint32_t cols, bool test): 
        CellularAutomaton<TuringPatternsCell>(rows, cols) {
            
        }

    void setWeights(const double& w1, const double& w2) {
        _w1 = w1;
        _w2 = w2;
    }
    void setEllipses(
            const double& a1, const double& b1,
            const double& a2, const double& b2) {
        _a1 = a1;
        _b1 = b1;
        _a2 = a2;
        _b2 = b2;
    }
    double calculate(uint32_t row, uint32_t col) {

        const auto max = std::max(_a2, _b2);
        uint32_t radius = static_cast<int>(std::ceil(max)) + 1;
        auto mooreNeighbors = moore(row, col, radius);
        auto cell = getCellValue(row, col);

        auto cellFallsWithinEllipse = [] (
                const TuringPatternsCell& center,
                const TuringPatternsCell& other,
                const double a,
                const double b) -> bool {

            auto temp1 = std::pow(center.realPositionX() - other.realPositionX(), 2);
            auto temp2 = std::pow(center.realPositionY() - other.realPositionY(), 2);

            return (temp1 / std::pow(a, 2)) + (temp2 / std::pow(b, 2)) <= 1;
        };

        auto inhibitionSumFilter = [this, cell, cellFallsWithinEllipse](const TuringPatternsCell& other) -> bool {
            return !cellFallsWithinEllipse(cell, other, _a1, _b1) &&
                        cellFallsWithinEllipse(cell, other, _a2, _b2);
        };

        auto activationSumFilter = [this,cell, cellFallsWithinEllipse](const TuringPatternsCell& other) -> bool {
            return cellFallsWithinEllipse(cell, other, _a1, _b1);
        };

        auto sum = [cell](const std::vector<TuringPatternsCell>& neighbors, double weight)
            -> double {
            double sum = 0.0;

            for (auto& neighbor: neighbors) {
                if (neighbor.type() == CellType::DC) {
                    sum += weight * cell.distance(neighbor);
                }
            }

            return sum;
        };

        auto activationNeighbors =
            filter<TuringPatternsCell>(mooreNeighbors, activationSumFilter);

        auto inhibitionNeighbors =
            filter<TuringPatternsCell>(mooreNeighbors, inhibitionSumFilter);

        return sum(activationNeighbors, _w1) + sum(inhibitionNeighbors, _w2);
    }

    std::vector<TuringPatternsCell> 
        neighborsFromRadius(uint32_t row, uint32_t col, double radius) {

        uint32_t iRadius = static_cast<int>(ceil(radius)) + 1;
        auto mooreNeigborhood = moore(row, col, iRadius);
        auto cell = getCellValue(row, col);
        auto lambdaFilter = [cell, radius](const TuringPatternsCell& other) {
            return cell.distance(other) <= radius;
        };

        return filter<TuringPatternsCell>(mooreNeigborhood, lambdaFilter);
    }

    std::vector<TuringPatternsCell> 
        neighborsFromWithinRange(uint32_t row, uint32_t col, double r1, double r2) {

        uint32_t iRadius = static_cast<int>(ceil(r2)) + 1;
        auto mooreNeigborhood = moore(row, col, iRadius);
        auto cell = getCellValue(row, col);
        auto lambdaFilter = [cell, r1, r2](const TuringPatternsCell& other) {
            auto distance = cell.distance(other);
            return distance >= r1 && distance <= r2;
        };

        return filter<TuringPatternsCell>(mooreNeigborhood, lambdaFilter);
    }

    double activationSum(uint32_t row, uint32_t col) {
        auto cell = getCellValue(row, col);
        auto neighbors = neighborsFromRadius(row, col, 2.3);
        auto sum = 0.0;
        //std::cout << "SIZE = " << neighbors.size() << std::endl;

        for (auto& neighbor: neighbors) {
            if (neighbor.type() == CellType::DC) {
                sum += 1 * cell.distance(neighbor);
            }
        }
        return sum;
    }

    double inhibitionSum(uint32_t row, uint32_t col) {
        auto cell = getCellValue(row, col);
        auto neighbors = neighborsFromWithinRange(row, col, 2.3, 6.01);
        auto sum = 0.0;

        for (auto& neighbor: neighbors) {
            if (neighbor.type() == CellType::DC) {
                sum += -0.1 * cell.distance(neighbor);
            }
        }
        return sum;
    }

    std::vector<TuringPatternsCell> 
        activationFilter(
            std::vector<TuringPatternsCell> mooreNeighborhood,
            uint32_t row, uint32_t col, double radius) {

        auto cell = getCellValue(row, col);
        auto lambdaFilter = [cell, radius](const TuringPatternsCell& other) {
            return cell.distance(other) <= radius;
        };

        return filter<TuringPatternsCell>(mooreNeighborhood, lambdaFilter);
    }

    double activationSum(
            std::vector<TuringPatternsCell> mooreNeighborhood, 
            uint32_t row,
            uint32_t col) {

        auto cell = getCellValue(row, col);
        auto neighbors = activationFilter(mooreNeighborhood, row, col, 2.3);
        auto sum = 0.0;

        for (auto& neighbor: neighbors) {
            if (neighbor.type() == CellType::DC) {
                sum += 1 * cell.distance(neighbor);
            }
        }
        return sum;
    }

    virtual void update() {
        iterate();
        _timestamp++;
        std::cout << _timestamp << std::endl;
        //display();
    }

    void iterate() {
        Grid<TuringPatternsCell> nextGrid(this->grid);
        for (auto i = 0; i < _rows; i++) {
            for (auto j = 0; j < _cols; j++) {
                auto& cell = nextGrid.getCellRef(i, j);
                double temp = calculateSum(i, j);
                if (temp > 0)
                    cell.setType(CellType::DC);

                if (temp < 0)
                    cell.setType(CellType::UC);
            }
        }
        this->grid = nextGrid;
    }
    friend class ModelFactory;

 private:
    double _w1;
    double _w2;
    double _a1 = 2.30;
    double _b1 = 1;
    double _a2 = 3.61;
    double _b2 = 6.01;
};

// template<>
// double TuringPatternsModel<Area_Policy::Circle>::calculateSum() const {
//     return 1;
// }

template<>
double TuringPatternsModel<Area_Policy::Ellipse>::calculateSum(uint32_t row, uint32_t col) {
    return calculate(row, col);
}

template<>
double TuringPatternsModel<Area_Policy::Circle>::calculateSum(uint32_t row, uint32_t col) {
    return activationSum(row, col) + inhibitionSum(row, col);
}

#endif
