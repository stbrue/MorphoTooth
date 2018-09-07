//
// Created by Stefanie on 15.08.2018.
//

#ifndef TOOTHMAKER_PARAMETERS_H
#define TOOTHMAKER_PARAMETERS_H


#include <vector>

/**
 * Contains all parameter (values that are set in the beginning or that have to be accessed globally)
 */
struct Parameters {
public:
    /**
     * Defines the initial amount of total cells and cells that are in the center
     */
    int initialRadius;

    /**
     * How often the forces and reactions are applied and calculated in total
     */
    int iterations;

    /**
     * Each protein has its own diffusion rate. The higher the rate the more of this protein diffuses
     */
    std::vector<double> diffusionRates;

    /**
     * How many cells are included in the calculations.
     * Only cells that have a closed sequence of neighbours (that are not at the border) are included
     */
    int nrCellsInSimulation;

    /**
     * How many cells are in the center
     * Depends on InitialRadius
     */
    int nrCellsInCenter;

    /**
     * This factor is multiplied with the forces to reduce their impact. To avoid too big fluctuations
     */
    double delta;

    /**
     * How strong the effect of Act activating itself is
     */
    double act;

    /**
     * How strong the effect of Inh inhibiting Act is
     */
    double inh;

    /**
     * Degradation rates of gene products
     */
    double mu;

    /**
     * An inductive threshold. If the concentration of Act is higher than this threshold then Inh is produced
     */
    double inT;

    /**
     * Fgf threshold. If the concentration of Act is higher than this threshold, then Sec1 (ECM) is produced
     */
    double set;

    /**
     * Sec1 (ECM) production rate
     */
    double sec;

    /**
     * Same as inT?
     */
    double sec2Inhibition;

    /**
     * Act concentration beyond swi (distance of initial BMP from midline)
     * Bias by initial BMP distribution in buccal direction
     */
    double lbi;

    /**
     * Act concentration beyond swi (distance of initial BMP from midline)
     * Bias by initial BMP distribution in lingual direction
     */
    double bbi;

    /**
     * Distance of initial BMP from midline
     * bucco-lingual bias
     */
    double swi;

    /**
     * Differentiation rate
     */
    double dff;

    /**
     * Epithelial proliferation rate
     */
    double egr;

    /**
     * Mesenchymal proliferation rate
     */
    double mgr;

    /**
     * Downgrowth (cervical loop)
     */
    double dgr;

    /**
     * Buoyancy, determined by the expression of Inh
     */
    double boy;

    /**
     * Repulsion between different tissues and different morphology parts
     */
    double rep;

    /**
     * Neighbour traction (effect of adhesion and repulsion between neighbours)
     */
    double adh;

    /**
     * Nuclear traction
     * Affects cell size
     */
    double ntr;

    /**
     * distance at which anterior-posterior bias applies
     */
    double bwi;

    /**
     * anterior bias by mechanical asymmetries
     */
    double abi;

    /**
     * posterior bias by mechanical asymmetries
     */
    double pbi;

    /**
     * Border growth: strength of BMP effect
     * Bias in z-direction
     */
    double bgr;

public:
    //Constructor
    //Parameters();

    //Getters
    /*
    int getInitialRadius() const;

    std::vector<double> getDiffusionRates();

    int getNrCellsInSimulation() const;

    int getNrCellsInCenter() const;

    double getDelta() const;

    double getAct() const;

    double getInh() const;

    double getMu() const;

    double getInT() const;

    double getSet() const;

    double getSec() const;

    double getSec2Inhibition() const;

    double getLbi() const;

    double getBbi() const;

    double getSwi() const;

    double getDff() const;

    double getEgr() const;

    double getMgr() const;

    double getDgr() const;

    double getBoy() const;

    double getRep() const;

    double getAdh() const;

    double getNtr() const;

    double getBwi() const;

    double getAbi() const;

    double getPbi() const;

    double getBgr() const;
     */

    //Setters
    //void setNrCellsInSimulation(int nrCellsInSimulation);

    //void setNrCellsInCenter(int nrCellsInCenter);
};


#endif //TOOTHMAKER_PARAMETERS_H
