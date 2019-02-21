//
// Created by Stefanie on 17.12.2018.
//

#include <random>
#include <iostream>
#include <chrono>
#include "Noise.h"
#include "Input.h"
/*
void Noise::doNoise(Cell (&cells)[totalNrOfCells], ImplementParams params, ImplementParams &noiseParams) {
    // If the noise type is set to 0, no noise is calculated
    if (params.noiseType == 0) {
        return;
    }
    // and do noise calculation only every "noiseDuration"th-iteration
    else if (params.currentIteration % params.noiseDuration != 0) {
        return;
    }

    // else calculate do noise
    if (params.noiseType == 1){
        // noise on one parameter -> change the noiseParams struct accordingly
        // get noise value (mean = 0)
        double sd = params.valueOfParameterAffectedByNoise * params.sdPercentage;
        double noiseValue = Noise::generateNoiseValue(params, 0, sd);

        // Create new struct ImplementParams with NoiseValues
        Noise::addToParameter(params.parameterWithNoise, noiseParams, noiseValue);
    } else if (params.noiseType == 2) {
        // the position of each cell is affected by noise (in all 3 dimensions randomly)
        for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
            double noiseX = generateNoiseValue(params, 0, params.sdPercentage);
            double noiseY = generateNoiseValue(params, 0, params.sdPercentage);
            double noiseZ = generateNoiseValue(params, 0, params.sdPercentage);
            cells[cell].addX(noiseX);
            cells[cell].addY(noiseY);
            cells[cell].addZ(noiseZ);
        }
    }

}


double Noise::generateNoiseValue(ImplementParams &params, double mean, double sd) {
    //Instantiation of pseudo random number generator
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::normal_distribution<double> distribution(mean, sd);

    double noiseValue = distribution(generator);
    return noiseValue;
}

void Noise::addToParameter(int parameterIndex, ImplementParams &params, double value) {
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

void Noise::updateParams(ImplementParams &noiseParams, ImplementParams &params) {
    params.error = noiseParams.error;
    params.nrCellsInSimulation = noiseParams.nrCellsInSimulation;
    params.currentIteration = noiseParams.currentIteration;
}
 */