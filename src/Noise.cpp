//
// Created by Stefanie on 17.12.2018.
//

#include <random>
#include <iostream>
#include "Noise.h"
#include "Input.h"

Parameters Noise::setNoiseParameter(Parameters params) {
    // If the noise parameter is set to 0, no noise is calculated
    if (params.parameterWithNoise == 0) {
        return params;
    }

    // get noise value (mean = 0)
    double sd = params.valueOfParameterAffectedByNoise * params.sdPercentage;
    double noiseValue = Noise::generateNoiseValue(0, sd);

    // Create new struct Parameters with NoiseValues
    Parameters noiseParams = params;
    Noise::addToParameter(params.parameterWithNoise, noiseParams, noiseValue);

    return noiseParams;
}

double Noise::generateNoiseValue(double mean, double sd) {
    std::default_random_engine generator;   //Instantiation of pseudo random number generator
    std::normal_distribution<double> distribution(mean, sd);

    double noiseValue = distribution(generator);
    return noiseValue;
}

void Noise::addToParameter(int parameterIndex, Parameters &params, double value) {
    switch (parameterIndex) {
        case 1: {
            params.distanceCellDivision += value;
            break;
        }
        case 2: {
            params.EKThreshold += value;
            break;
        }
        case 3: {
            params.repDistance += value;
            break;
        }
        case 4: {
            params.powerOfRep += value;
            break;
        }
        case 5: {
            params.sinkAmount += value;
            break;
        }
        case 6: {
            params.ActDiffusion += value;
            break;
        }
        case 7: {
            params.InhDiffusion += value;
            break;
        }
        case 8: {
            params.SecDiffusion += value;
            break;
        }
        case 9: {
            params.delta += value;
            break;
        }
        case 10: {
            params.act += value;
            break;
        }
        case 11: {
            params.inh += value;
            break;
        }
        case 12: {
            params.mu += value;
            break;
        }
        case 13: {
            params.inT += value;
            break;
        }
        case 14: {
            params.set += value;
            break;
        }
        case 15: {
            params.sec += value;
            break;
        }
        case 16: {
            params.lbi += value;
            break;
        }
        case 17: {
            params.bbi += value;
            break;
        }
        case 18: {
            params.swi += value;
            break;
        }
        case 19: {
            params.dff += value;
            break;
        }
        case 20: {
            params.egr += value;
            break;
        }
        case 21: {
            params.mgr += value;
            break;
        }
        case 22: {
            params.dgr += value;
            break;
        }
        case 23: {
            params.boy += value;
            break;
        }
        case 24: {
            params.rep += value;
            break;
        }
        case 25: {
            params.adh += value;
            break;
        }
        case 26: {
            params.ntr += value;
            break;
        }
        case 27: {
            params.bwi += value;
            break;
        }
        case 28: {
            params.abi += value;
            break;
        }
        case 29: {
            params.pbi += value;
            break;
        }
        case 30: {
            params.bgr += value;
            break;
        }
        default: {
            std::cout << "Parameter could not be added" << std::endl;
            params.error = true;
        }
    }
}

void Noise::updateParams(Parameters noiseParams, Parameters &params) {
    params.error = noiseParams.error;
    params.nrCellsInSimulation = noiseParams.nrCellsInSimulation;
}