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

std::vector<double> Parameters::getDiffusionRates() {
    return diffusionRates;
}

int Parameters::getCellsInSimulation() const {
    return cellsInSimulation;
}

int Parameters::getCellsInCenter() const {
    return cellsInCenter;
}

double Parameters::getDelta() const {
    return delta;
}

double Parameters::getAct() const {
    return Act;
}

double Parameters::getInh() const {
    return Inh;
}

double Parameters::getMu() const {
    return mu;
}

double Parameters::getInT() const {
    return inT;
}

double Parameters::getSet() const {
    return set;
}

double Parameters::getSec() const {
    return sec;
}

double Parameters::getSec2Inhibition() const {
    return sec2Inhibition;
}

double Parameters::getLbi() const {
    return lbi;
}

double Parameters::getBbi() const {
    return bbi;
}

double Parameters::getSwi() const {
    return swi;
}

double Parameters::getDff() const {
    return dff;
}

//Setters
void Parameters::setCellsInSimulation(int cellsInSimulation) {
    Parameters::cellsInSimulation = cellsInSimulation;
}

void Parameters::setCellsInCenter(int cellsInCenter) {
    Parameters::cellsInCenter = cellsInCenter;
}










