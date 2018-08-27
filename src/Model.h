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

    static void reaction(std::vector<Cell> &cells, Parameters &params);

    static void EKDifferentiation(std::vector<Cell> &cells, Parameters &params, int cell);

    static void ActReactionAndDegradation(std::vector<Cell> &cells, Parameters &params, int cell);

    static void InhProduction(std::vector<Cell> &cells, Parameters &params, int cell);

    static void Sec1Production(std::vector<Cell> &cells, Parameters &params, int cell);

    static void Sec2Production(std::vector<Cell> &cells, Parameters &params, int cell);

    static void buccalLingualBias(std::vector<Cell> &cells, Parameters &params);

    static void differenciation(std::vector<Cell> &cells, Parameters &params);

    static void epithelialProliferation(std::vector<Cell> &cells, Parameters &params);

    static void buoyancy(std::vector<Cell> &cells, Parameters &params);

    static void repulsionBetweenNonNeighbours(std::vector<Cell> &cells, Parameters &params);
};


#endif //TOOTHMAKER_MODEL_H
