//
// Created by Stefanie on 15.08.2018.
//

#include "Parameters.h"

//Constructor
Parameters::Parameters() {
    InitialRadius = 3;
    iterations = 3;
    diffusionRates = {0.2, 0.2, 0.2, 0};
    cellsInSimulation = 0;
    delta = 0.05;
}


//Getters
int Parameters::getInitialRadius() const {
    return InitialRadius;
}

std::vector<double> Parameters::getDiffusionRates()  {
    return diffusionRates;
}

int Parameters::getCellsInSimulation() const {
    return cellsInSimulation;
}

double Parameters::getDelta() const {
    return delta;
}

//Setters
void Parameters::setCellsInSimulation(int cellsInSimulation) {
    Parameters::cellsInSimulation = cellsInSimulation;
}


