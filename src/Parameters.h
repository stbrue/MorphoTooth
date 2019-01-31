//
// Created by Stefanie on 15.08.2018.
//

#ifndef TOOTHMAKER_PARAMETERS_H
#define TOOTHMAKER_PARAMETERS_H


#include <vector>
#include <string>

/**
 * Contains all parameter (values that are set in the beginning or that have to be accessed globally)
 */
struct Parameters {
public:
    /**
     * @brief   Defines the initial amount of total cells and cells that are in the center
     */
    int initialRadius;

    /**
     * @brief   How many cells are included in the calculations.
     * Only cells that have a closed sequence of neighbours (that are not at the border) are included
     */
    int nrCellsInSimulation;

    /**
     * @brief   This factor is multiplied with the forces to reduce their impact. To avoid too big fluctuations
     */
    double delta;

    /**
     * @brief   How strong the effect of Act activating itself is
     */
    double act;

    /**
     * @brief   How strong the effect of Inh inhibiting Act is
     */
    double inh;

    /**
     * @brief   Degradation rates of gene products
     */
    double mu;

    /**
     * @brief   An inductive threshold. If the concentration of Act is higher than this threshold then Inh is produced
     */
    double inT;

    /**
     * @brief   Fgf threshold. If the concentration of Act is higher than this threshold, then Sec1 (ECM) is produced
     */
    double set;

    /**
     * @brief   Sec1 (ECM) production rate
     */
    double sec;

    /**
     * @brief   Same as inT?
     */
    double sec2Inhibition;

    /**
     * @brief   Act concentration beyond swi (distance of initial BMP from midline)
     * Bias by initial BMP distribution in buccal direction
     */
    double lbi;

    /**
     * @brief   Act concentration beyond swi (distance of initial BMP from midline)
     * Bias by initial BMP distribution in lingual direction
     */
    double bbi;

    /**
     * @brief   Distance of initial BMP from midline
     * bucco-lingual bias
     */
    double swi;

    /**
     * @brief   Differentiation rate
     */
    double dff;

    /**
     * @brief   Epithelial proliferation rate
     */
    double egr;

    /**
     * @brief   Mesenchymal proliferation rate
     */
    double mgr;

    /**
     * @brief   Downgrowth (cervical loop)
     */
    double dgr;

    /**
     * @brief   Buoyancy, determined by the expression of Inh
     */
    double boy;

    /**
     * @brief   Repulsion between different tissues and different morphology parts
     */
    double rep;

    /**
     * @brief   Neighbour traction (effect of adhesion and repulsion between neighbours)
     */
    double adh;

    /**
     * @brief   Nuclear traction
     * Affects cell size
     */
    double ntr;

    /**
     * @brief   distance at which anterior-posterior bias applies
     */
    double bwi;

    /**
     * @brief   anterior bias by mechanical asymmetries
     */
    double abi;

    /**
     * @brief   posterior bias by mechanical asymmetries
     */
    double pbi;

    /**
     * @brief   Border growth: strength of BMP effect
     * Bias in z-direction
     */
    double bgr;

    /**
     * is true if somewhere something goes wrong and is used to stop the big loop at this iteration
     */
    bool error;

    /**
     * this integer can be used to stop the loop after a specific number of cell divisions
     */
    int cellDivisionCount;

    int currentIteration;

    double distanceCellDivision;

    double EKThreshold;

    int powerOfRep;

    double repDistance;

    double zDiff;

    double sinkAmount;

    double ActDiffusion;

    double InhDiffusion;

    double Sec1Diffusion;

    double Sec2Diffusion;

    int maxNrOfIterations;

    int maxNrOfCells;

    int outputInterval;

    int printInterval;

    int outputPrecision;

    double round1;

    double round2;

    double round3;

    int nrOfProteins;

    double firstX;

    double firstY;

    double firstZ;

    int dimensions;

    int nrOfParametersToChange;

    std::vector<std::vector<double>> parameterToChangeValues;

    int parameterToChange;

    double totalPlusMinusScope;

    double percentageSteps;

    double valueOfParameterToChange;

    int nrOfConditions;

    int newInhAndSecProduction;

    int parameterWithNoise;

    double sdPercentage;

    int repetitions;

    double valueOfParameterAffectedByNoise;
};


#endif //TOOTHMAKER_PARAMETERS_H
