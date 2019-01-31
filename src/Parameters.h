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
     * @brief   Defines the initial amount of circles/rows of cells. For seals 2 is appropriate
     */
    int initialRadius;

    /**
     * @brief   How many cells are included in the calculations.
     * Its increased only by cell division
     */
    int nrCellsInSimulation;

    /**
     * @brief   Force vectors are multiplied by delta to reduce their impact i.e. to avoid too large fluctuations
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
     * @brief   not needed
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
     * @brief   Distance of initial BMP from midline, i.e. range where buccal-lingual-bias does apply
     */
    double swi;

    /**
     * @brief   Differentiation rate of the cells
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
     * @brief   Neighbour traction (effect of adhesion AND repulsion between neighbours)
     */
    double adh;

    /**
     * @brief   Nuclear traction
     * Affects cell size, leads to roundening of cells
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

    /**
     * counter of the big loop. Can be used for example by output functions or for debugging
     */
    int currentIteration;

    /**
     * Defines the distance that two cells must have minimally that cell division takes place
     */
    double distanceCellDivision;

    /**
     * Defines the Act Concentration that a cell must reach to become a EK cell
     */
    double EKThreshold;

    /**
     * How strong the effect of repulsion between non-neighbours is reduced (the effect is divided by a number to the power of "powerOfRep"
     */
    int powerOfRep;

    /**
     * Defines the distance two non-neighbouring cells have to deceed that repulsion between them acts
     */
    double repDistance;

    double zDiff;

    /**
     * This represents how strong the protein sink at the tissue borders is. The protein concentrations of the border cells get multiplied by this parameter
     */
    double sinkAmount;

    /**
     * protein-specific diffusion rate of Act
     */
    double ActDiffusion;

    /**
     * protein-specific diffusion rate of Inh
     */
    double InhDiffusion;

    /**
     * protein-specific diffusion rate of Sec1
     */
    double Sec1Diffusion;

    double Sec2Diffusion;

    /**
     * How many iterations are to be done
     */
    int maxNrOfIterations;

    /**
     * The maximum number of cells in the simulation. If this number is reached, the simulation stops
     */
    int maxNrOfCells;

    /**
     * Every x-iteration Outputfiles are generated
     */
    int outputInterval;

    /**
     * Every x-iteration the iteration and nrCellsInSimulation is printed in the console
     */
    int printInterval;

    /**
     * How many decimal places are written into the output files
     */
    int outputPrecision;

    /**
     * States how many parameter-screens should be done. The screenings however happen sequentially.
     */
    int nrOfParametersToChange;

    /**
     * For implementation reasons this vector holds the values related to parameter scanning that are read initially
     */
    std::vector<std::vector<double>> parameterToChangeValues;

    /**
     * Defines which parameter is changed between several simulations. This can be used to do a parameter screening.
     */
    int parameterToChange;

    /**
     * Used for parameter screening. Defines the range in which the parameter takes values -> default value plus/minus x
     * This value is read as a decimal representation of percentage. -> E.g. 0.5 for plus minus 50% around the default value
     */
    double totalPlusMinusScope;

    /**
     * Used for parameter screening. Defines the step size in the screening (in percent) -> E.g. 0.2 means that the differences
     * between the parameter value of two simulations is 20% of the default value
     */
    double percentageSteps;

    /**
     * Holds the default value of the parameter which is changed during the parameter screening.
     */
    double valueOfParameterToChange;

    /**
     * Results from totalPlusMinusScope and percentageSteps and states how many simulations in the parameter screening have to be done
     */
    int nrOfConditions;

    /**
     * If 0 the reaction function of Inh and Sec are as in the original version (ToothMaker)
     * If 1 the reaction function of Inh and Sec are in a binary way (either on or off) depending on the differentiation state of a cell
     */
    int newInhAndSecProduction;

    /**
     * Which parameter is affected by noise during the simulation. The value is the position of the parameter in the input file
     */
    int parameterWithNoise;

    /**
     * To define the amplitude of noise. The standard deviation of the distribution from which the noise values are taken
     * is: the default value of the parameter * "sdPercentage".
     */
    double sdPercentage;

    /**
     * How many times the simulation with the same parameters has to be repeated
     */
    int repetitions;

    /**
     * Holds the value of the parameter that is affected by noise
     */
    double valueOfParameterAffectedByNoise;
};


#endif //TOOTHMAKER_PARAMETERS_H
