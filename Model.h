//
// Created by Stefanie on 13.08.2018.
//

#ifndef TOOTHMAKER_MODEL_H
#define TOOTHMAKER_MODEL_H


#include "Cell.h"
#include "Parameters.h"

class Model {
public:
    static void diffusion(std::vector<Cell> &cells, Parameters &parameters);
    static void upDiffusion(std::vector<Cell> &cells, int cell, int layer, int protein, double pCellArea);
    static void downDiffusion(std::vector<Cell> &cells, int cell, int layer, int protein, double pCellArea);
    static void sink(std::vector<Cell> &cells, int cell, int layer, int protein, double contactArea);
    static void horizontalDiffusion(std::vector<Cell> &cells, int cell, int layer, int protein, double diffusionArea);

};


#endif //TOOTHMAKER_MODEL_H
