//
// Created by Stefanie on 21.02.2019.
//

#ifndef MORPHOTOOTH_MODELPARAMS_H
#define MORPHOTOOTH_MODELPARAMS_H

#include <string>

struct ModelParams {
public:
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
     * @brief   Fgf threshold. If the concentration of Act is higher than this threshold, then Sec (ECM) is produced
     */
    double set;

    /**
     * @brief   Sec (ECM) production rate
     */
    double sec;

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
     * protein-specific diffusion rate of Act
     */
    double ActDiffusion;

    /**
     * protein-specific diffusion rate of Inh
     */
    double InhDiffusion;

    /**
     * protein-specific diffusion rate of Sec
     */
    double SecDiffusion;
};

std::vector<std::string> getModelParameterNamesList();

#endif //MORPHOTOOTH_MODELPARAMS_H
