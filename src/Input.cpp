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
    //params.diffusionRates = {0.2, 0.2, 0.2, 0};
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

Parameters Input::setParameters(std::string InputFileName) {
    Parameters params;

    // Set initial values independent of inputFile
    params.error = false;
    params.cellDivisionCount = 0;
    params.currentIteration = 0;
    params.dimensions = 3;
    params.nrOfConditions = 1;
    params.powerOfRep = 8;
    params.initialRadius = 2;
    params.round4 = 1000;

    // Read in values from inputFile

    double parameter[48] = {0};

    std::string line;
    int counter = 0;

    std::ifstream InputFile(InputFileName);
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
    params.repDistance = parameter[3];
    params.zDiff = parameter[4];
    params.sinkAmount = parameter[5];
    params.ActDiffusion = parameter[6];
    params.InhDiffusion = parameter[7];
    params.Sec1Diffusion = parameter[8];
    params.Sec2Diffusion = parameter[9];
    params.delta = parameter[10];
    params.act = parameter[11];
    params.inh = parameter[12];
    params.mu = parameter[13];
    params.inT = parameter[14];
    params.set = parameter[15];
    params.sec = parameter[16];
    params.sec2Inhibition = parameter[17];
    params.lbi = parameter[18];
    params.bbi = parameter[19];
    params.swi = parameter[20];
    params.dff = parameter[21];
    params.egr = parameter[22];
    params.mgr = parameter[23];
    params.dgr = parameter[24];
    params.boy = parameter[25];
    params.rep = parameter[26];
    params.adh = parameter[27];
    params.ntr = parameter[28];
    params.bwi = parameter[29];
    params.abi = parameter[30];
    params.pbi = parameter[31];
    params.bgr = parameter[32];

    //Implementation parameters
    params.maxNrOfIterations = static_cast<int>(parameter[33]);
    params.maxCellDivisionCount = static_cast<int>(parameter[34]);
    params.outputInterval = static_cast<int>(parameter[35]);
    params.printInterval = static_cast<int>(parameter[36]);
    params.outputPrecision = static_cast<int>(parameter[37]);
    params.round1 = parameter[38];
    params.round2 = parameter[39];
    params.round3 = parameter[40];
    params.nrOfProteins = static_cast<int>(parameter[41]);
    params.firstX = parameter[42];
    params.firstY = parameter[43];
    params.firstZ = parameter[44];
    params.parameterToChange = static_cast<int>(parameter[45]);
    params.totalPlusMinusScope = parameter[46];
    params.percentageSteps = parameter[47];
    params.newInhAndSecProduction = static_cast<int>(parameter[48]);

    params.valueOfParameterToChange = parameter[params.parameterToChange];
    //params.parameterToChangeIsInt = Input::isInteger(params.valueOfParameterToChange);

    return params;
}

void Input::changeInputFileTemp(Parameters params, double newValue) {
    // Delete old InputFileTemp
    remove("InputFileTemp.txt");

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
    if (InputFile.is_open() && InputFileout.is_open()) {
        while (getline(InputFile, lineTemp)) {
            if (counter == params.parameterToChange) {
                lineTemp = newValueString;
            }
            counter += 1;
            lineTemp += "\n";
            InputFileout << lineTemp;
        }
        InputFile.close();
        InputFileout.close();
    } else {
        std::cout << "Unable to open file";
    }

    //Rename the InputFileout to IntputFileTemp
    rename("InputFileout.txt", "InputFileTemp.txt");

}

/*void Input::changeInputFileTemp(Parameters params, int newValue) {
    // Delete old InputFileTemp
    remove("InputFileTemp.txt");

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
    if (InputFile.is_open() && InputFileout.is_open()) {
        while (getline(InputFile, lineTemp)) {
            if (counter == params.parameterToChange) {
                lineTemp = newValueString;
            }
            counter += 1;
            lineTemp += "\n";
            InputFileout << lineTemp;
        }
        InputFile.close();
        InputFileout.close();
    } else {
        std::cout << "Unable to open file";
    }

    //Rename the InputFileout IntputFileTemp
    rename("InputFileout.txt", "InputFileTemp.txt");

}*/

void Input::changeInputFile(int nrOfParameter) {
    // Read in "ParametersToChange.txt" to know the parameterToChange
    std::string line;
    int counter = 0;
    double parameterToChange = 0;

    std::ifstream ParameterToChangeFile("ParametersToChange.txt");

    // Read in the file and save the parameterToChange
    if (ParameterToChangeFile.is_open()) {
        while (getline(ParameterToChangeFile, line)) {
            if (counter == nrOfParameter) {
                parameterToChange = std::stod(line);
                break;
            }
            counter += 1;
        }
        ParameterToChangeFile.close();
    } else {
        std::cout << "Unable to open file ParametersToChange.txt" << std::endl;
    }

    // Read in the InputFile to change the parameter "parameterToChange"
    std::string lineTemp;
    counter = 0;
    int lineOfParameterToChange = 45; // The parameter "parameterToChange" is on the 47th line of the inputFile

    std::ifstream InputFile("InputFile.txt");
    std::ofstream InputFileout("InputFileout.txt");

    // Convert the parameterToChange into a string
    std::ostringstream parameterToChangeS;
    parameterToChangeS << parameterToChange;
    std::string parameterToChangeString = parameterToChangeS.str();

    // Read in the file and write each line (possibly changed) into the InputFileout
    if (InputFile.is_open() && InputFileout.is_open()) {
        while (getline(InputFile, lineTemp)) {
            if (counter == lineOfParameterToChange) {
                lineTemp = parameterToChangeString;
            }
            counter += 1;
            lineTemp += "\n";
            InputFileout << lineTemp;
        }
        InputFile.close();
        InputFileout.close();
    } else {
        std::cout << "Unable to open InputFile.txt" << std::endl;
    }

    //Overwrite InputFile.txt with InputFileout.txt
    remove("InputFile.txt");
    rename("InputFileout.txt", "InputFile.txt");

}

/*bool Input::isInteger(int value) {
    if (value == std::floor(value))
        return true;
    return false;
}

bool Input::isInteger(double value) {
    if (value == std::floor(value))
        return true;
    return false;
}
*/

int Input::defineNrOfParametersToChange() {
    // Read in the File
    std::string lineTemp;
    int counter = 0;

    std::ifstream InputFile("ParametersToChange.txt");

    // Read in the file and count the number of lines
    if (InputFile.is_open()) {
        while (getline(InputFile, lineTemp)) {
            counter += 1;
        }
        InputFile.close();
    } else {
        std::cout << "Unable to open file";
    }
    return counter;
}