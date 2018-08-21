//
// Created by Stefanie on 15.08.2018.
//

#ifndef TOOTHMAKER_PARAMETERS_H
#define TOOTHMAKER_PARAMETERS_H


#include <vector>

class Parameters {
private:
    int InitialRadius;

    int iterations;

    std::vector<double> diffusionRates;

    int cellsInSimulation;

    int cellsInCenter;

    double delta;

    double Act;

    double Inh;

    double mu;

    double inT;

    double set;

    double sec;

    double sec2Inhibition;

    double lbi;

    double bbi;

    double swi;

    double dff;

    double egr;

    double mgr;

    double dgr;

    double boy;

public:
    //Constructor
    Parameters();

    //Getters
    int getInitialRadius() const;

    std::vector<double> getDiffusionRates();

    int getCellsInSimulation() const;

    int getCellsInCenter() const;

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

    //Setters
    void setCellsInSimulation(int cellsInSimulation);

    void setCellsInCenter(int cellsInCenter);
};


#endif //TOOTHMAKER_PARAMETERS_H
