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

public:
    //Constructor
    Parameters();

    //Getters
    int getInitialRadius() const;
    std::vector<double> getDiffusionRates();
    int getCellsInSimulation() const;
    double getDelta() const;

    //Setters
    void setCellsInSimulation(int cellsInSimulation);
};


#endif //TOOTHMAKER_PARAMETERS_H
