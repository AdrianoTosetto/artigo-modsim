#ifndef EXCITABLE_MEDIA_MODEL_H
#define EXCITABLE_MEDIA_MODEL_H

#include "cellular_automata.h"

template<typename T>
class ExcitableMediaModel: public CellularAutomaton<T> {
 public:
    ExcitableMediaModel(int, int);
    virtual void update();

    ~ExcitableMediaModel();
};

#endif