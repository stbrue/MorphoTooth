//
// Created by Stefanie on 15.08.2018.
//

#include "Parameters.h"

//Constructor
Parameters::Parameters() {
    InitialRadius = 2;
    iterations = 3;
    diffusionRates = {0.2, 0.2, 0.2, 0};
    cellsInSimulation = 0;
    delta = 0.05;
    egr = 0.017;
    mgr = 200;
    dgr = 10000;
    boy = 0.1;
    Act = 1.1;
    Inh = 26;
    mu = 0.1;
    inT = 0.19;
    set = 0.95;
    sec = 0.03;
    sec2Inhibition = 0.19;
    lbi = 1;
    bbi = 1;
    swi = 0;
    dff = 0.0002;
    rep = 1;
    adh = 0.001;
    ntr = 0.00001;
    bwi = 0.8;
    abi = 18;
    pbi = 15;
    bgr = 1;
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

double Parameters::getEgr() const {
    return egr;
}

double Parameters::getMgr() const {
    return mgr;
}

double Parameters::getDgr() const {
    return dgr;
}

double Parameters::getBoy() const {
    return boy;
}

double Parameters::getRep() const {
    return rep;
}

double Parameters::getAdh() const {
    return adh;
}

double Parameters::getNtr() const {
    return ntr;
}

double Parameters::getBwi() const {
    return bwi;
}

double Parameters::getAbi() const {
    return abi;
}

double Parameters::getPbi() const {
    return pbi;
}

double Parameters::getBgr() const {
    return bgr;
}

//Setters
void Parameters::setCellsInSimulation(int cellsInSimulation) {
    Parameters::cellsInSimulation = cellsInSimulation;
}

void Parameters::setCellsInCenter(int cellsInCenter) {
    Parameters::cellsInCenter = cellsInCenter;
}










