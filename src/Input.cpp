//
// Created by Stefanie on 07.09.2018.
//

#include "Input.h"

Parameters Input::defineParametersSealTest() {
    Parameters params;

    params.initialRadius = 2;
    params.iterations = 3;
    params.diffusionRates = {0.2, 0.2, 0.2, 0};
    params.nrCellsInSimulation = 0;
    params.delta = 0.05;
    params.egr = 0.017;
    params.mgr = 200;
    params.dgr = 10000;
    params.boy = 0.1;
    params.act = 1.1;
    params.inh = 26;
    params.mu = 0.1;
    params.inT = 0.19;
    params.set = 0.95;
    params.sec = 0.03;
    params.sec2Inhibition = 0.19;
    params.lbi = 1;
    params.bbi = 1;
    params.swi = 0;
    params.dff = 0.0002;
    params.rep = 1;
    params.adh = 0.001;
    params.ntr = 0.00001;
    params.bwi = 0.8;
    params.abi = 18;
    params.pbi = 15;
    params.bgr = 1;

    return params;
}
