//
// Created by Stefanie on 07.09.2018.
//

#include "Input.h"
#include "Utility.h"
#include "json.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <chrono>

using nlohmann::json;

ModelParams Input::setModelParamsInitial(std::string InputFileName) {
    // Set up vector and struct
    ModelParams modelParams;
    double parameter[40] = {0};

    // read a JSON file
    // read here: https://github.com/nlohmann/json
    std::ifstream ifs{InputFileName};

    auto parsed_json = json::parse(ifs);
//    std::cout << parsed_json.dump() << std::endl;

    modelParams.ActDiffusion = parsed_json["ModelParams"]["ActDiffusionRate"].get<double>();
    modelParams.InhDiffusion = parsed_json["ModelParams"]["InhDiffusionRate"].get<double>();
    modelParams.SecDiffusion = parsed_json["ModelParams"]["Sec1DiffusionRate"].get<double>();
    modelParams.delta = parsed_json["ModelParams"]["Delta"].get<double>();
    modelParams.act = parsed_json["ModelParams"]["Act"].get<double>();
    modelParams.inh = parsed_json["ModelParams"]["Inh"].get<double>();
    modelParams.mu = parsed_json["ModelParams"]["DegradationRate"].get<double>();
    modelParams.inT = parsed_json["ModelParams"]["Int"].get<double>();
    modelParams.set = parsed_json["ModelParams"]["Set"].get<double>();
    modelParams.sec = parsed_json["ModelParams"]["Sec"].get<double>();
    modelParams.lbi = parsed_json["ModelParams"]["Lbi"].get<double>();
    modelParams.bbi = parsed_json["ModelParams"]["Bbi"].get<double>();
    modelParams.swi = parsed_json["ModelParams"]["Swi"].get<double>();
    modelParams.dff = parsed_json["ModelParams"]["Dff"].get<double>();
    modelParams.egr = parsed_json["ModelParams"]["Egr"].get<double>();
    modelParams.mgr = parsed_json["ModelParams"]["Mgr"].get<double>();
    modelParams.dgr = parsed_json["ModelParams"]["Dgr"].get<double>();
    modelParams.boy = parsed_json["ModelParams"]["Boy"].get<double>();
    modelParams.rep = parsed_json["ModelParams"]["Rep"].get<double>();
    modelParams.adh = parsed_json["ModelParams"]["Adh"].get<double>();
    modelParams.ntr = parsed_json["ModelParams"]["Ntr"].get<double>();
    modelParams.bwi = parsed_json["ModelParams"]["Bwi"].get<double>();
    modelParams.abi = parsed_json["ModelParams"]["Abi"].get<double>();
    modelParams.pbi = parsed_json["ModelParams"]["Pbi"].get<double>();
    modelParams.bgr = parsed_json["ModelParams"]["Bgr"].get<double>();

    return modelParams;
}


ImplementParams Input::setImplementParamsInitial(std::string InputFileName) {
    // Set up vector and struct
    ImplementParams params;
    double parameter[60] = {0};

    // Set initial values independent of inputFile
    params.error = false;
    params.endOfSimulation = false;
    params.currentIteration = 0;
    params.nrOfConditions = 1;
    params.powerOfRep = 8;
    params.seed = std::chrono::system_clock::now().time_since_epoch().count();

    // Read in values from inputFile
    std::string line;
    int counter = 0;

    std::ifstream InputFile(InputFileName);
    std::string delimiter = ":";

    if (InputFile.is_open()) {
        while (getline(InputFile, line)) {
            Utility::trimString(line);
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
    params.initialRadius = static_cast<int>(parameter[0]);
    params.distanceCellDivision = parameter[1];
    params.EKThreshold = parameter[2];
    params.repDistance = parameter[3];
    params.powerOfRep = static_cast<int>(parameter[4]);
    params.sinkAmount = parameter[5];
    params.newInhAndSecProduction = static_cast<int>(parameter[6]);
    params.maxNrOfIterations = static_cast<int>(parameter[7]);
    params.minNrOfCells = static_cast<int>(parameter[8]);
    params.outputInterval = static_cast<int>(parameter[9]);
    params.printInterval = static_cast<int>(parameter[10]);
    params.outputPrecision = static_cast<int>(parameter[11]);
    params.repetitions = static_cast<int>(parameter[12]);
    params.parameterWithNoise = static_cast<int>(parameter[13]);
    params.sdPercentage = parameter[14];
    params.noiseDuration = static_cast<int>(parameter[15]);
    params.noiseType = static_cast<int>(parameter[16]);

    // Params to change
    params.parameterToChange = static_cast<int>(parameter[17]);
    params.totalPlusMinusScope = parameter[18];
    params.percentageSteps = parameter[19];

    return params;
}

/*
ImplementParams Input::setParameters(std::string InputFileName) {
    // Set up vector and struct
    ImplementParams params;
    double parameter[60] = {0};

    // Set initial values independent of inputFile
    params.error = false;
    params.endOfSimulation = false;
    params.currentIteration = 0;
    params.nrOfConditions = 1;
    params.powerOfRep = 8;
    params.seed = std::chrono::system_clock::now().time_since_epoch().count();

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
    params.initialRadius = static_cast<int>(parameter[0]);
    params.distanceCellDivision = parameter[1];
    params.EKThreshold = parameter[2];
    params.repDistance = parameter[3];
    params.powerOfRep = static_cast<int>(parameter[4]);
    params.sinkAmount = parameter[5];
    params.ActDiffusion = parameter[6];
    params.InhDiffusion = parameter[7];
    params.SecDiffusion = parameter[8];
    params.delta = parameter[9];
    params.act = parameter[10];
    params.inh = parameter[11];
    params.mu = parameter[12];
    params.inT = parameter[13];
    params.set = parameter[14];
    params.sec = parameter[15];
    params.lbi = parameter[16];
    params.bbi = parameter[17];
    params.swi = parameter[18];
    params.dff = parameter[19];
    params.egr = parameter[20];
    params.mgr = parameter[21];
    params.dgr = parameter[22];
    params.boy = parameter[23];
    params.rep = parameter[24];
    params.adh = parameter[25];
    params.ntr = parameter[26];
    params.bwi = parameter[27];
    params.abi = parameter[28];
    params.pbi = parameter[29];
    params.bgr = parameter[30];

    //Implementation parameters
    params.newInhAndSecProduction = static_cast<int>(parameter[31]);
    params.maxNrOfIterations = static_cast<int>(parameter[32]);
    params.minNrOfCells = static_cast<int>(parameter[33]);
    params.outputInterval = static_cast<int>(parameter[34]);
    params.printInterval = static_cast<int>(parameter[35]);
    params.outputPrecision = static_cast<int>(parameter[36]);
    params.repetitions = static_cast<int>(parameter[37]);
    params.parameterWithNoise = static_cast<int>(parameter[38]);
    params.sdPercentage = parameter[39];
    params.noiseDuration = static_cast<int>(parameter[40]);
    params.noiseType = static_cast<int>(parameter[41]);

    // ImplementParams to change
    params.parameterToChange = static_cast<int>(parameter[42]);
    params.totalPlusMinusScope = parameter[43];
    params.percentageSteps = parameter[44];
    params.valueOfParameterToChange = parameter[params.parameterToChange];

    params.valueOfParameterAffectedByNoise = parameter[46];

    return params;
}
 */

/*

void Input::changeInputFileTemp(ImplementParams params, double newValue, std::string nameInputFileTemp) {
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
*/