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

    static void repulsionBetweenNonNeighbours(double dx, double dy, double dz, double distance3D,
                                              std::vector<std::vector<double>> compressionMatrixNonNeighbours);

    static void repulsion(std::vector<Cell> &cells, Parameters &params);

    static bool isNeighbourOf(std::vector<Cell> &cells, int cell, int potentialNeighbour);

    static void repulsionBetweenNeighbours(double dx, double dy, double dz, double distance3D, double distance2D,
                                           std::vector<std::vector<double>> compressionMatrixNeighbours,
                                           bool cell1IsEKCell, bool cell2IsEKCell, bool cell1IsInCenter, double adh);

    static std::vector<std::vector<double>> setUpCompressionMatrix();

    static void resetCompressionMatrix(std::vector<std::vector<double>> &compressionMatrix);

    static void updateTempPositions(std::vector<Cell> &cells, Parameters params, int cell,
                                    std::vector<std::vector<double>> compressionMatrix, bool isNeighbour);

    static void nucleusTraction(std::vector<Cell> &cells, Parameters params);

    static void anteriorPosteriorBias(std::vector<Cell> &cells, Parameters &params);
};


#endif //TOOTHMAKER_MODEL_H
