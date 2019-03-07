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
    modelParams.epithelialDegradation = parsed_json["ModelParams"]["EpithelialDegradation"].get<double>();
    modelParams.mesenchymeDegradation = parsed_json["ModelParams"]["MesenchymeDegradation"].get<double>();
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
    modelParams.rep = parsed_json["ModelParams"]["Rep"].get<double>();
    modelParams.adh = parsed_json["ModelParams"]["Adh"].get<double>();
    modelParams.ntr = parsed_json["ModelParams"]["Ntr"].get<double>();
    modelParams.bwi = parsed_json["ModelParams"]["Bwi"].get<double>();
    modelParams.abi = parsed_json["ModelParams"]["Abi"].get<double>();
    modelParams.pbi = parsed_json["ModelParams"]["Pbi"].get<double>();
    modelParams.bgr = parsed_json["ModelParams"]["Bgr"].get<double>();
    modelParams.boy = parsed_json["ModelParams"]["Boy"].get<double>();

    return modelParams;
}


ImplementParams Input::setImplementParamsInitial(std::string InputFileName) {
    // Set up vector and struct
    ImplementParams params = {0};

    // Set initial values independent of inputFile
    params.error = false;
    params.endOfSimulation = false;
    params.currentIteration = 0;
    params.nrOfConditions = 1;
    params.powerOfRep = 8;
    params.seed = std::chrono::system_clock::now().time_since_epoch().count();

    // read a JSON file
    // read here: https://github.com/nlohmann/json
    std::ifstream ifs{InputFileName};

    auto parsed_json = json::parse(ifs);
    //    std::cout << parsed_json.dump() << std::endl;

    // Initialize parameters with values from the file
    // Model
    params.initialRadius = parsed_json["ImplementParams"]["initialRadius"].get<double>();
    params.distanceCellDivision = parsed_json["ImplementParams"]["distanceCellDivision"].get<double>();
    params.EKThreshold = parsed_json["ImplementParams"]["EKThreshold"].get<double>();
    params.repDistance = parsed_json["ImplementParams"]["repDistance"].get<double>();
    params.powerOfRep = parsed_json["ImplementParams"]["powerOfRep"].get<int>();
    params.sinkAmount = parsed_json["ImplementParams"]["sinkAmount"].get<double>();
    params.newInhAndSecProduction = parsed_json["ImplementParams"]["newInhAndSecProduction"].get<int>();
    params.maxMovement = parsed_json["ImplementParams"]["maxMovement"].get<double>();

    // Simulation
    params.maxNrOfIterations = parsed_json["ImplementParams"]["maxNrOfIterations"].get<int>();
    params.minNrOfCells = parsed_json["ImplementParams"]["minNrOfCells"].get<int>();
    params.outputInterval = parsed_json["ImplementParams"]["OutputInterval"].get<int>();
    params.printInterval = parsed_json["ImplementParams"]["PrintInterval"].get<int>();
    params.outputPrecision = parsed_json["ImplementParams"]["outputPrecision"].get<int>();

    // Noise
    params.noiseType = parsed_json["ImplementParams"]["noiseType"].get<int>();
    params.sd = parsed_json["ImplementParams"]["sd"].get<double>();
    params.noiseDuration = parsed_json["ImplementParams"]["noiseDuration"].get<int>();
    params.repetitions = parsed_json["ImplementParams"]["repetitions"].get<int>();
    params.parameterWithNoise = parsed_json["ImplementParams"]["parameterWithNoise"].get<std::string>();
    params.noiseStart = parsed_json["ImplementParams"]["noiseStart"].get<int>();
    params.noiseEnd = parsed_json["ImplementParams"]["noiseEnd"].get<int>();

    // Params to change
    params.parameterToChange = parsed_json["ImplementParams"]["parameterToChange"].get<std::string>();
    params.totalPlusMinusScope = parsed_json["ImplementParams"]["totalPlusMinusScope"].get<double>();
    params.percentageSteps = parsed_json["ImplementParams"]["percentageSteps"].get<double>();

    return params;
}
