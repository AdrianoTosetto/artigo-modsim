#ifndef TURING_PATTERNS_MODEL_H
#define TURING_PATTERNS_MODEL_H

#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

#include "cellular_automata.h"

class TuringPatternsModel: public CellularAutomaton<int> {
    TuringPatternsModel(uint32_t rows, uint32_t cols): 
        CellularAutomaton<int>(rows, cols) {

    }
};

#endif