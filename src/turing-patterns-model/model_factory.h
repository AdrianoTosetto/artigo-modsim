#ifndef MODEL_FACTORY_H
#define MODEL_FACTORY_H

#include <utility>
#include <vector>
#include <memory>

#include "turing_patterns_model.h"

typedef std::pair<uint32_t, uint32_t> position; 

class ModelFactory {
 public:
    ModelFactory() {}
    ModelFactory(int rows, int cols) {
        //_model = std::make_unique<TuringPatternsModel>(TuringPatternsModel<>(rows, cols));
    }
    TuringPatternsModel<>& model() {
        return *_model.get();
    }
    void setDCCells(const std::vector<position>& positions) {
        for (auto& pos: positions) {
            auto row = pos.first;
            auto col = pos.second;
            _model->grid.getCellRef(row, col).setType(CellType::DC);
        }
    }

 private:
    std::unique_ptr<TuringPatternsModel<>> _model;

};

#endif