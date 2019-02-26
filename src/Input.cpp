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
    ModelParams modelParams = {0};
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
    ImplementParams params = {0};
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
    params.noiseType = static_cast<int>(parameter[12]);
    params.sd = parameter[13];
    params.noiseDuration = static_cast<int>(parameter[14]);
    params.repetitions = static_cast<int>(parameter[15]);
    params.parameterWithNoise = static_cast<int>(parameter[16]);

    // Params to change
    params.parameterToChange = static_cast<int>(parameter[17]);
    params.totalPlusMinusScope = parameter[18];
    params.percentageSteps = parameter[19];

    return params;
}
