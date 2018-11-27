//
// Created by Stefanie on 07.09.2018.
//

#include "Input.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

Parameters Input::defineParametersSealTest() {
    Parameters params;

    params.initialRadius = 2;
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

Parameters Input::setParameters() {
    Parameters params;

    // Set initial values independent of inputFile
    params.error = false;
    params.cellDivisionCount = 0;
    params.currentIteration = 0;
    params.dimensions = 3;
    params.nrOfConditions = 1;

    // Read in values from inputFile

    double parameter[49] = {0};

    // Read in values from inputFile
    std::string line;
    int counter = 0;

    std::ifstream InputFile("InputFile.txt");
    if (InputFile.is_open()) {
        while (getline(InputFile, line)) {
            parameter[counter] = std::stod(line);
            counter += 1;
        }
        InputFile.close();
    } else {
        std::cout << "Unable to open file";
    }

    parameter[0] = 0;

    // Initialize parameters with values from the file
    //Model parameters
    params.distanceCellDivision = parameter[1];
    params.EKThreshold = parameter[2];
    params.powerOfRep = static_cast<int>(parameter[3]);
    params.repDistance = parameter[4];
    params.zDiff = parameter[5];
    params.sinkAmount = parameter[6];
    params.initialRadius = static_cast<int>(parameter[7]);
    params.ActDiffusion = parameter[8];
    params.InhDiffusion = parameter[9];
    params.Sec1Diffusion = parameter[10];
    params.Sec2Diffusion = parameter[11];
    params.delta = parameter[12];
    params.act = parameter[13];
    params.inh = parameter[14];
    params.mu = parameter[15];
    params.inT = parameter[16];
    params.set = parameter[17];
    params.sec = parameter[18];
    params.sec2Inhibition = parameter[19];
    params.lbi = parameter[20];
    params.bbi = parameter[21];
    params.swi = parameter[22];
    params.dff = parameter[23];
    params.egr = parameter[24];
    params.mgr = parameter[25];
    params.dgr = parameter[26];
    params.boy = parameter[27];
    params.rep = parameter[28];
    params.adh = parameter[29];
    params.ntr = parameter[30];
    params.bwi = parameter[31];
    params.abi = parameter[32];
    params.pbi = parameter[33];
    params.bgr = parameter[34];

    //Implementation parameters
    params.maxNrOfIterations = static_cast<int>(parameter[35]);
    params.maxCellDivisionCount = static_cast<int>(parameter[36]);
    params.outputInterval = static_cast<int>(parameter[37]);
    params.printInterval = static_cast<int>(parameter[38]);
    params.outputPrecision = static_cast<int>(parameter[39]);
    params.round1 = parameter[40];
    params.round2 = parameter[41];
    params.round3 = parameter[42];
    params.nrOfProteins = static_cast<int>(parameter[43]);
    params.firstX = parameter[44];
    params.firstY = parameter[45];
    params.firstZ = parameter[46];
    params.parameterToChange = static_cast<int>(parameter[47]);
    params.totalPlusMinusScope = parameter[48];
    params.percentageSteps = parameter[49];

    params.valueOfParameterToChange = parameter[params.parameterToChange];
    params.parameterToChangeIsInt = Input::isInteger(params.valueOfParameterToChange);

    return params;
}

void Input::changeInputFile(Parameters params, double newValue) {
    // Read in the InputFile
    std::string lineTemp;
    int counter = 0;

    std::ifstream InputFile("InputFile.txt");
    std::ofstream InputFileout("InputFileout.txt");

    // Convert the newValue into a string
    std::ostringstream newValueS;
    newValueS << newValue;
    std::string newValueString = newValueS.str();

    // Read in the file and write each line (possibly changed) into the InputFileout
    if (InputFile.is_open()) {
        while (getline(InputFile, lineTemp)) {
            if (counter == params.parameterToChange) {
                lineTemp = newValueString;
            }
            counter += 1;
            lineTemp += "\n";
            InputFileout << lineTemp;
        }
        InputFile.close();
    } else {
        std::cout << "Unable to open file";
    }

    //Rename the InputFileout to "IntputFile" to overwrite the InputFile
    rename("InputFileout.txt", "InputFile.txt");

}

void Input::changeInputFile(Parameters params, int newValue) {
    // Read in the InputFile
    std::string lineTemp;
    int counter = 0;

    std::ifstream InputFile("InputFile.txt");
    std::ofstream InputFileout("InputFileout.txt");

    // Convert the newValue into a string
    std::ostringstream newValueS;
    newValueS << newValue;
    std::string newValueString = newValueS.str();

    // Read in the file and write each line (possibly changed) into the InputFileout
    if (InputFile.is_open()) {
        while (getline(InputFile, lineTemp)) {
            if (counter == params.parameterToChange) {
                lineTemp = newValueString;
            }
            counter += 1;
            lineTemp += "\n";
            InputFileout << lineTemp;
        }
        InputFile.close();
    } else {
        std::cout << "Unable to open file";
    }

    //Rename the InputFileout to "IntputFile" to overwrite the InputFile
    rename("InputFileout.txt", "InputFile.txt");

}

bool Input::isInteger(int value) {
    if (value == std::floor(value))
        return true;
    return false;
}

bool Input::isInteger(double value) {
    if (value == std::floor(value))
        return true;
    return false;
}

