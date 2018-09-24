//
// Created by Stefanie on 13.08.2018.
//

#ifndef TOOTHMAKER_MODEL_H
#define TOOTHMAKER_MODEL_H


#include "Cell.h"
#include "Parameters.h"

class Model {
public:
    /**
     * @brief   calculates new protein concentrations due to diffusion between cells
     * @details Diffusion is proportional to diffusion area (flux), diffusion coefficient of the protein and delta
     * @param   cells   vector containing all cells
     * @param   parameters  struct containing all parameters
     */
    static void diffusion(std::vector<Cell> &cells, Parameters &parameters);

    /**
     * @brief   Calculates the resulting protein concentration differences due to diffusion between a cell and an upper one
     * @param   cells   vector containing all cells
     * @param   cell    ID of lower cell
     * @param   layer   0 if in epithelium, >0 if in mesenchymal layer
     * @param   protein 0:Act, 1:Inh, 2:Sec1, 3:Sec2
     * @param   pCellArea   diffusion area (cell area, relative to total diffusion area)
     */
    static void upDiffusion(std::vector<Cell> &cells, int cell, int layer, int protein, double pCellArea);

    /**
     * @brief   Calculates the resulting protein concentration differences due to diffusion between a cell and an lower one
     * @param   cells   vector containing all cells
     * @param   cell    ID of upper cell
     * @param   layer   0 if in epithelium, >0 if in mesenchymal layer
     * @param   protein 0:Act, 1:Inh, 2:Sec1, 3:Sec2
     * @param   pCellArea   diffusion area (cell area, relative to total diffusion area)
     */
    static void downDiffusion(std::vector<Cell> &cells, int cell, int layer, int protein, double pCellArea);

    /**
     * @brief   Calculates protein concentration differences due to a sink (for cells at the border)
     * @param   cells   vector containing all cells
     * @param   cell    ID of cell in question
     * @param   layer   0 if in epithelium, >0 if in mesenchymal layer
     * @param   protein 0:Act, 1:Inh, 2:Sec1, 3:Sec2
     * @param   contactArea     diffusion area (relative cell area or perimeter part)
     */
    static void sink(std::vector<Cell> &cells, int cell, int layer, int protein, double contactArea);

    /**
     * @brief   Calculates protein concentration differences due to diffusion in horizontal direction
     * @param   cells   vector containing all cells
     * @param   cell    ID of cell in question
     * @param   layer   0 if in epithelium, >0 if in mesenchymal layer
     * @param   protein 0:Act, 1:Inh, 2:Sec1, 3:Sec2
     * @param   diffusionArea   pDiffusionArea for non-epithelial and eDiffusionArea for epithelial diffusion
     */
    static void horizontalDiffusion(std::vector<Cell> &cells, int cell, int layer, int protein, double diffusionArea);

    /**
     * @brief   Calls all methods that implement the reaction (Activation, Inhibition, Expression, Degradation) of the proteins
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     */
    static void reaction(std::vector<Cell> &cells, Parameters &params);

    /**
     * @brief   Cell becomes an enamel knot cell if Act concentration is >1 and if it is in the center
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     * @param   cell    ID of cell in question
     */
    static void EKDifferentiation(std::vector<Cell> &cells, Parameters &params, int cell);

    /**
     * @brief   Reaction (Self-activation and inhibition by Inh) and Degradation of Act
     * @details Reaction: positive Term (Self-activation of Act) divided by negative term (Inhibition by Inh)
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     * @param   cell    ID of cell in question
     */
    static void ActReactionAndDegradation(std::vector<Cell> &cells, Parameters &params, int cell);

    /**
     * @brief   Inh is produced if the differentiation state is higher than a threshold and if the cell is an EK cell
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     * @param   cell    ID of cell in question
     */
    static void InhProduction(std::vector<Cell> &cells, Parameters &params, int cell);

    /**
     * @brief   Sec1 is produced if differentiation state is higher than a threshold or if the cell is an EK cell
     * @details The production is proportional to a secretion rate (sec) and to the differentiation state minus the degradation
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     * @param   cell    ID of cell in question
     */
    static void Sec1Production(std::vector<Cell> &cells, Parameters &params, int cell);

    /**
     * @brief   Sec2 is produced proportionally to Act concentration minus inhibition by Sec1 and minus degradation
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     * @param   cell    ID of cell in question
     */
    static void Sec2Production(std::vector<Cell> &cells, Parameters &params, int cell);

    /**
     * @brief   If a center cell deviates too much in buccal or lingual direction (y), then its Act concentration is set to a certain value
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     */
    static void buccalLingualBias(std::vector<Cell> &cells, Parameters &params);

    /**
     * @brief   Increases the differentiation state of each cell proportionally to Sec1 concentration
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     */
    static void differentiation(std::vector<Cell> &cells, Parameters &params);

    /**
     * @brief   Cells are drifting away from the center proportional to a proliferation rate and inverse proportional
     * to their differentiation state. It implements also downgrowth of the cervical loop
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     */
    static void epithelialProliferation(std::vector<Cell> &cells, Parameters &params);

    /**
     * @brief   A force that is normal to the epithelial cell surface and proportional to Sec1 concentration
     * @param   cells   vector containing all cells
     * @param   params  struct containing all cells
     */
    static void buoyancy(std::vector<Cell> &cells, Parameters &params);

    /**
     * @brief   if two cells are too close there is a force that pushes them away from each other (repulsion)
     * @param   dx  difference in x values
     * @param   dy  difference in y values
     * @param   dz  difference in z values
     * @param   distance3D  distance between the cells in xyz plane
     * @param   compressionMatrixNonNeighbours
     */
    static void repulsionBetweenNonNeighbours(double dx, double dy, double dz, double distance3D,
                                              std::vector<std::vector<double>> &compressionMatrixNonNeighbours);

    /**
     *
     * @param cells
     * @param params
     */
    static void repulsion(std::vector<Cell> &cells, Parameters &params);

    static bool isNeighbourOf(std::vector<Cell> &cells, int cell, int potentialNeighbour);

    static void repulsionBetweenNeighbours(double dx, double dy, double dz, double distance3D, double distance2D,
                                           std::vector<std::vector<double>> &compressionMatrixNeighbours,
                                           bool cell1IsEKCell, bool cell2IsEKCell, bool cell1IsInCenter, double adh);

    static std::vector<std::vector<double>> setUpCompressionMatrix();

    static void resetCompressionMatrix(std::vector<std::vector<double>> &compressionMatrix);

    static void updateTempPositions(std::vector<Cell> &cells, Parameters params, int cell,
                                    std::vector<std::vector<double>> compressionMatrix, bool isNeighbour);

    static void nucleusTraction(std::vector<Cell> &cells, Parameters params);

    static void anteriorPosteriorBias(std::vector<Cell> &cells, Parameters &params);

    static void applyForces(std::vector<Cell> &cells, Parameters params);

    static void cellDivision(std::vector<Cell> &cells, Parameters params);
};


#endif //TOOTHMAKER_MODEL_H
