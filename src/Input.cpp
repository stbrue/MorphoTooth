//
// Created by Stefanie on 07.09.2018.
//

#include "Input.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cctype>

void Input::trimString(std::string &str) {
    Input::leftTrim(str);
    Input::rightTrim(str);
}

void Input::leftTrim(std::string &str) {
    // trim from start to first occurence that is not a space
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

void Input::rightTrim(std::string &str) {
    // trim from last occurence that is not a space to end
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}

Parameters Input::setParametersInitial(std::string InputFileName) {
    // Set up vector and struct
    Parameters params;
    double parameter[60] = {0};

    // Read in values from inputFile
    std::string line;
    int counter = 0;

    std::ifstream InputFile(InputFileName);
    std::string delimiter = ":";

    if (InputFile.is_open()) {
        while (getline(InputFile, line)) {
            Input::trimString(line);
            if (line.length() > 0) {
                std::string token = line.substr(line.find(delimiter) + 1, line.length());
                parameter[counter] = std::stod(token);
                counter += 1;
            } else {
                std::cout << "There was an empty line in InputFile.txt at line " << counter << std::endl;
                std::cout << "Therefore the reading in was stopped" << std::endl;
                break;
            }
        }
        InputFile.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }

    // Initialize parameters with values from the file
    //Model parameters
    params.initialRadius = parameter[0];
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
    params.newInhAndSecProduction = static_cast<int>(parameter[38]);
    params.parameterWithNoise = static_cast<int>(parameter[39]);
    params.sdPercentage = parameter[40];

    // Manage the parameters to change
    params.nrOfParametersToChange = static_cast<int>(parameter[41]);
    int indexOfParameter = 42;
    for (int parameterToChange = 0; parameterToChange < params.nrOfParametersToChange; ++parameterToChange) {
        double dParameterToChange = parameter[indexOfParameter];
        double totalPlusMinusScope = parameter[indexOfParameter + 1];
        double percentageSteps = parameter[indexOfParameter + 2];
        double valueOfParameterToChange = parameter[static_cast<int>(dParameterToChange)];
        indexOfParameter += 3;

        std::vector<double> currentValuesOfParameterToChange = {dParameterToChange, totalPlusMinusScope,
                                                                percentageSteps, valueOfParameterToChange};
        params.parameterToChangeValues.push_back(currentValuesOfParameterToChange);
    }

    return params;
}

void Input::createInputFileTemp(int parameter, Parameters params, std::string fileName) {
    std::ofstream InputFileTemp(fileName);
    std::string line;

    if (InputFileTemp.is_open()) {
        InputFileTemp << params.initialRadius << "\n";
        InputFileTemp << params.distanceCellDivision << "\n";
        InputFileTemp << params.EKThreshold << "\n";
        InputFileTemp << params.repDistance << "\n";
        InputFileTemp << params.zDiff << "\n";
        InputFileTemp << params.sinkAmount << "\n";
        InputFileTemp << params.ActDiffusion << "\n";
        InputFileTemp << params.InhDiffusion << "\n";
        InputFileTemp << params.Sec1Diffusion << "\n";
        InputFileTemp << params.Sec2Diffusion << "\n";
        InputFileTemp << params.delta << "\n";
        InputFileTemp << params.act << "\n";
        InputFileTemp << params.inh << "\n";
        InputFileTemp << params.mu << "\n";
        InputFileTemp << params.inT << "\n";
        InputFileTemp << params.set << "\n";
        InputFileTemp << params.sec << "\n";
        InputFileTemp << params.sec2Inhibition << "\n";
        InputFileTemp << params.lbi << "\n";
        InputFileTemp << params.bbi << "\n";
        InputFileTemp << params.swi << "\n";
        InputFileTemp << params.dff << "\n";
        InputFileTemp << params.egr << "\n";
        InputFileTemp << params.mgr << "\n";
        InputFileTemp << params.dgr << "\n";
        InputFileTemp << params.boy << "\n";
        InputFileTemp << params.rep << "\n";
        InputFileTemp << params.adh << "\n";
        InputFileTemp << params.ntr << "\n";
        InputFileTemp << params.bwi << "\n";
        InputFileTemp << params.abi << "\n";
        InputFileTemp << params.pbi << "\n";
        InputFileTemp << params.bgr << "\n";
        InputFileTemp << params.maxNrOfIterations << "\n";
        InputFileTemp << params.maxCellDivisionCount << "\n";
        InputFileTemp << params.outputInterval << "\n";
        InputFileTemp << params.printInterval << "\n";
        InputFileTemp << params.outputPrecision << "\n";
        InputFileTemp << params.newInhAndSecProduction << "\n";
        InputFileTemp << params.parameterWithNoise << "\n";
        InputFileTemp << params.sdPercentage << "\n";
        InputFileTemp << params.parameterToChangeValues[parameter][0] << "\n";
        InputFileTemp << params.parameterToChangeValues[parameter][1] << "\n";
        InputFileTemp << params.parameterToChangeValues[parameter][2] << "\n";
        InputFileTemp << params.parameterToChangeValues[parameter][3] << "\n";
    }

    InputFileTemp.close();
}

Parameters Input::setParameters(std::string InputFileName) {
    // Set up vector and struct
    Parameters params;
    double parameter[60] = {0};

    // Set initial values independent of inputFile
    params.error = false;
    params.cellDivisionCount = 0;
    params.currentIteration = 0;
    params.dimensions = 3;
    params.nrOfConditions = 1;
    params.powerOfRep = 8;
    params.round1 = 1.00e-15;
    params.round2 = 1.00e-8;
    params.round3 = 1.00e+6;
    params.nrOfProteins = 3;
    params.firstX = 0;
    params.firstY = 0;
    params.firstZ = 1;

    // Read in values from inputFile
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

    // Initialize parameters with values from the file
    //Model parameters
    params.initialRadius = parameter[0];
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
    params.newInhAndSecProduction = static_cast<int>(parameter[38]);
    params.parameterWithNoise = static_cast<int>(parameter[39]);
    params.sdPercentage = parameter[40];

    // Parameters to change
    params.parameterToChange = parameter[41];
    params.totalPlusMinusScope = parameter[42];
    params.percentageSteps = parameter[43];
    params.valueOfParameterToChange = parameter[params.parameterToChange];

    return params;
}

void Input::changeInputFileTemp(Parameters params, double newValue, std::string nameInputFileTemp) {
    // Read in the InputFileTemp
    std::string lineTemp;
    int counter = 0;

    // Create name for output (only temporary)
    std::stringstream outFileS;
    outFileS << "TempOut" << nameInputFileTemp.substr(13, 2) << ".txt";
    std::string outFileString = outFileS.str();


    std::ifstream InputFile(nameInputFileTemp);
    std::ofstream InputFileout(outFileString);

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

    // Convert the std::strings into const chars*
    const char *cInputFileTemp = nameInputFileTemp.c_str();
    const char *cInputFileOut = outFileString.c_str();

    // Delete old InputFileTemp
    remove(cInputFileTemp);

    //Rename the InputFileout to InputFileTemp
    rename(cInputFileOut, cInputFileTemp);

}

void Input::changeInputFile(int nrOfParameter) {
    // Read in "ParametersToChange.txt" to know the parameterToChange
    std::string line;
    int counter = 1;
    double parameterToChange = 0;
    double plusMinusScope = 0;
    double percentageStep = 0;

    int lineOfParameterToChange = (nrOfParameter * 3) - 2;
    int lineOfPlusMinusScope = (nrOfParameter * 3) - 1;
    int lineOfPercentageStep = (nrOfParameter * 3);

    std::ifstream ParameterToChangeFile("ParametersToChange.txt");

    // Read in the file and save the parameterToChange
    if (ParameterToChangeFile.is_open()) {
        while (getline(ParameterToChangeFile, line)) {
            if (counter == lineOfParameterToChange) {
                parameterToChange = std::stod(line);
            } else if (counter == lineOfPlusMinusScope) {
                plusMinusScope = std::stod(line);
            } else if (counter == lineOfPercentageStep) {
                percentageStep = std::stod(line);
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
    int lineOfParameterToChangeInInputFile = 37; // The parameter "parameterToChange" is on the 37th line of the inputFile
    int lineOfPlusMinusScopeInInputFile = 38;
    int lineOfPercentageStepInInputFile = 39;

    std::ifstream InputFile("InputFile.txt");
    std::ofstream InputFileout("InputFileout.txt");

    // Convert the parameterToChange into a string
    std::ostringstream parameterToChangeS;
    parameterToChangeS << parameterToChange;
    std::string parameterToChangeString = parameterToChangeS.str();

    std::string plusMinusScopeString = Input::doubleToString(plusMinusScope);
    std::string percentageStepString = Input::doubleToString(percentageStep);

    // Read in the file and write each line (possibly changed) into the InputFileout
    if (InputFile.is_open() && InputFileout.is_open()) {
        while (getline(InputFile, lineTemp)) {
            if (counter == lineOfParameterToChangeInInputFile) {
                lineTemp = parameterToChangeString;
            } else if (counter == lineOfPlusMinusScopeInInputFile) {
                lineTemp = plusMinusScopeString;
            } else if (counter == lineOfPercentageStepInInputFile) {
                lineTemp = percentageStepString;
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
    return counter / 3;
}

double Input::getParameterAffectedByNoise(Parameters &params) {
    // The parameterWithNoise'th line of the file holds the value of the parameter
    // Read in the File
    std::string lineTemp;
    int counter = 0;
    double parameterAffectedByNoiseValue;

    std::ifstream InputFile("InputFile.txt");

    // Read in the file and return the value of the parameterWithNoise'th line
    if (InputFile.is_open()) {
        while (getline(InputFile, lineTemp)) {
            if (counter == params.parameterWithNoise) {
                parameterAffectedByNoiseValue = std::stod(lineTemp);
                InputFile.close();
                return parameterAffectedByNoiseValue;
            }
            counter += 1;
        }
        InputFile.close();
        std::cout << "ParameterWithNoise was not found." << std::endl;
        params.error = true;
        return 2;
    } else {
        std::cout << "Unable to open file";
        params.error = true;
        return 1;
    }

}

std::string Input::doubleToString(double value) {
    std::ostringstream strs;
    strs << value;
    std::string str = strs.str();
    return str;
}