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

    double delta;

    double Act;

    double Inh;

    double mu;

    double inT;

    double set;

    double sec;

    double sec2Inhibition;

public:
    //Constructor
    Parameters();

    //Getters
    int getInitialRadius() const;

    std::vector<double> getDiffusionRates();

    int getCellsInSimulation() const;

    double getDelta() const;

    double getAct() const;

    double getInh() const;

    double getMu() const;

    double getInT() const;

    double getSet() const;

    double getSec() const;

    double getSec2Inhibition() const;

    //Setters
    void setCellsInSimulation(int cellsInSimulation);
};


#endif //TOOTHMAKER_PARAMETERS_H
