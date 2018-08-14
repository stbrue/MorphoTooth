//
// Created by Stefanie on 13.08.2018.
//

#ifndef TOOTHMAKER_MODEL_H
#define TOOTHMAKER_MODEL_H


#include "Cell.h"

class Model {
public:
    static void diffusion(std::vector<Cell> &cells, int CellsInSimulation);

};


#endif //TOOTHMAKER_MODEL_H
