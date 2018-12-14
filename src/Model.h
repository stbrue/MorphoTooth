//
// Created by Stefanie on 13.08.2018.
//

#ifndef TOOTHMAKER_MODEL_H
#define TOOTHMAKER_MODEL_H


#include "Cell.h"
#include "Parameters.h"
#include "consts.h"

class Model {
public:

    static bool NanIsPresent(double x, double y, double z);

    static void iterationStep(Cell (&cells)[maxNrOfCells], Parameters &params, int iteration);

    /**
     * @brief   calculates new protein concentrations due to diffusion between cells
     * @details Diffusion is proportional to diffusion area (flux), diffusion coefficient of the protein and delta
     * @param   cells   vector containing all cells
     * @param   parameters  struct containing all parameters
     */

    static bool testPositions(Cell cells[maxNrOfCells]);


    static void diffusion(Cell (&cells)[maxNrOfCells], Parameters &parameters);

    /**
     * @brief   Calculates the resulting protein concentration differences due to diffusion between a cell and an upper one
     * @details Compares concentration with the upper cell.
     * @param   cells   vector containing all cells
     * @param   cell    ID of lower cell
     * @param   layer   0 if in epithelium, >0 if in mesenchymal layer
     * @param   protein 0:Act, 1:Inh, 2:Sec1, 3:Sec2
     * @param   pCellArea   diffusion area (cell area, relative to total diffusion area)
     */
    static void
    upDiffusion(Cell (&cells)[maxNrOfCells], int cell, int layer, int protein, double relativeDiffusionArea);

    /**
     * @brief   Calculates the resulting protein concentration differences due to diffusion between a cell and an lower one
     * @details Compares concentration with the cell below.
     * @param   cells   vector containing all cells
     * @param   cell    ID of upper cell
     * @param   layer   0 if in epithelium, >0 if in mesenchymal layer
     * @param   protein 0:Act, 1:Inh, 2:Sec1, 3:Sec2
     * @param   pCellArea   diffusion area (cell area, relative to total diffusion area)
     */
    static void
    downDiffusion(Cell (&cells)[maxNrOfCells], int cell, int layer, int protein, double relativeDiffusionArea);

    /**
     * @brief   Calculates protein concentration differences due to a sink (for cells at the border)
     * @param   cells   vector containing all cells
     * @param   cell    ID of cell in question
     * @param   layer   0 if in epithelium, >0 if in mesenchymal layer
     * @param   protein 0:Act, 1:Inh, 2:Sec1, 3:Sec2
     * @param   contactArea     diffusion area (relative cell area or perimeter part)
     */
    static void
    sink(Cell (&cells)[maxNrOfCells], int cell, int layer, int protein, double relativeDiffusionArea,
         Parameters &params);

    /**
     * @brief   Calculates protein concentration differences due to diffusion in horizontal direction
     * @param   cells   vector containing all cells
     * @param   cell    ID of cell in question
     * @param   layer   0 if in epithelium, >0 if in mesenchymal layer
     * @param   protein 0:Act, 1:Inh, 2:Sec1, 3:Sec2
     * @param   diffusionArea   pDiffusionArea for non-epithelial and eDiffusionArea for epithelial diffusion
     */
    static void
    horizontalDiffusion(Cell (&cells)[maxNrOfCells], int cell, int layer, int protein, double totalDiffusionArea,
                        Parameters &params);

    /**
     * @brief   Calls all methods that implement the reaction (Activation, Inhibition, Expression, Degradation) of the proteins
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     */
    static void reaction(Cell (&cells)[maxNrOfCells], Parameters &params);

    /**
     * @brief   Cell becomes an enamel knot cell if Act concentration is >1 and if it is in the center
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     * @param   cell    ID of cell in question
     */
    static void EKDifferentiation(Cell (&cells)[maxNrOfCells], Parameters &params, int cell);

    /**
     * @brief   Reaction (Self-activation and inhibition by Inh) and Degradation of Act
     * @details Reaction: positive Term (Self-activation of Act) divided by negative term (Inhibition by Inh)
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     * @param   cell    ID of cell in question
     */
    static void ActReactionAndDegradation(Cell (&cells)[maxNrOfCells], Parameters &params, int cell);

    /**
     * @brief   Inh is produced if the differentiation state is higher than a threshold and if the cell is an EK cell
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     * @param   cell    ID of cell in question
     */
    static void InhReactionAndDegradation(Cell (&cells)[maxNrOfCells], Parameters &params, int cell);

    /**
     * @brief   Sec1 is produced if differentiation state is higher than a threshold or if the cell is an EK cell
     * @details The production is proportional to a secretion rate (sec) and to the differentiation state minus the degradation
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     * @param   cell    ID of cell in question
     */
    static void Sec1ReactionAndDegradation(Cell (&cells)[maxNrOfCells], Parameters &params, int cell);

    /**
     * @brief   Sec2 is produced proportionally to Act concentration minus inhibition by Sec1 and minus degradation
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     * @param   cell    ID of cell in question
     */
    static void Sec2ReactionAndDegradation(Cell (&cells)[maxNrOfCells], Parameters &params, int cell);

    /**
     * @brief   If a center cell deviates too much in buccal or lingual direction (y), then its Act concentration is set to a certain value
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     */
    static void buccalLingualBias(Cell (&cells)[maxNrOfCells], Parameters &params);

    /**
     * @brief   Increases the differentiation state of each cell proportionally to Sec1 concentration
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     */
    static void differentiation(Cell (&cells)[maxNrOfCells], Parameters &params);

    /**
     * @brief   Cells are drifting away from the center proportional to a proliferation rate and inverse proportional
     * to their differentiation state. It implements also downgrowth of the cervical loop
     * @param   cells   vector containing all cells
     * @param   params  struct containing all parameters
     */
    static void epithelialProliferation(Cell (&cells)[maxNrOfCells], Parameters &params);

    /**
     * @brief   A force that is normal to the epithelial cell surface and proportional to Sec1 concentration
     * @param   cells   vector containing all cells
     * @param   params  struct containing all cells
     */
    static void buoyancy(Cell (&cells)[maxNrOfCells], Parameters &params);

    /**
     * @brief   if two cells are too close there is a force that pushes them away from each other (repulsion)
     * @param   dx  difference in x values
     * @param   dy  difference in y values
     * @param   dz  difference in z values
     * @param   distance3D  distance between the cells in xyz plane
     * @param   compressionMatrixNonNeighbours
     */
    static void repulsionBetweenNonNeighbours(double dx, double dy, double dz, double currentDistance,
                                              std::vector<std::vector<double>> &compressionMatrixNonNeighbours,
                                              Parameters &params);

    /**
     *
     * @param cells
     * @param params
     */
    static void repulsionAndAdhesion(Cell (&cells)[maxNrOfCells], Parameters &params);

    static bool isNeighbourOf(Cell (&cells)[maxNrOfCells], int cell, int potentialNeighbour);

    static void
    repulsionAndAdhesionBetweenNeighbours(double dx, double dy, double dz, double currentDistance,
                                          double originalDistance,
                                          std::vector<std::vector<double>> &compressionMatrixNeighbours,
                                          bool cell1IsEKCell, bool cell2IsEKCell, bool cell1IsInCenter,
                                          Parameters &params);

    static std::vector<std::vector<double>> setUpCompressionMatrix();

    static void resetCompressionMatrix(std::vector<std::vector<double>> &compressionMatrix, Parameters &params);

    static void updateTempPositions(Cell (&cells)[maxNrOfCells], Parameters &params, int cell,
                                    std::vector<std::vector<double>> compressionMatrix, bool isNeighbour);

    static void nucleusTraction(Cell (&cells)[maxNrOfCells], Parameters &params);

    static void anteriorPosteriorBias(Cell (&cells)[maxNrOfCells], Parameters &params);

    static void applyForces(Cell (&cells)[maxNrOfCells], Parameters &params);

    static void cellDivision(Cell (&cells)[maxNrOfCells], Parameters &params);

    static std::vector<std::vector<int>> searchMotherCells(Cell (&cells)[maxNrOfCells], Parameters &params);

    static std::vector<int> findCommonNeighbours(int M1, int M2, Cell (&cells)[maxNrOfCells], Parameters &params);

    static void updateNeighbourRelations(int M1, int M2, int N1, int N2, Cell &newCell, Cell (&cells)[maxNrOfCells],
                                         Parameters &params);

    static void setMeanProteinConcentrations(int M1, int M2, Cell &newCell, Cell (&cells)[maxNrOfCells],
                                             Parameters &params);

    static void defineIfNewCellInCentre(int N1, int N2, Cell &newCell, Cell (&cells)[maxNrOfCells], Parameters &params);

    static void errorTesting(Cell cells[maxNrOfCells], Parameters &params);

    static void
    calculateNewOriginalDistances(Cell (&cells)[maxNrOfCells], Parameters &params, Cell &newCell, int M1, int M2,
                                  int N1,
                                  int N2);

    static void newEpithelialProliferation(Cell (&cells)[maxNrOfCells], Parameters &params);

    static void downGrowth(Cell (&cells)[maxNrOfCells], Parameters &params, double xShift, double yShift, int cell);

    static void printMaximumNrOfNeighbours(Cell (&cells)[maxNrOfCells], Parameters &params);
};


#endif //TOOTHMAKER_MODEL_H
