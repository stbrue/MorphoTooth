//
// Created by Stefanie on 17.12.2018.
//

#include <random>
#include <iostream>
#include <chrono>
#include "Noise.h"
#include "Input.h"

void Noise::doNoise(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {
    // If the noise type is set to 0, no noise is calculated
    if (implementParams.noiseType == 0) {
        return;
    }
        // and do noise calculation only every "noiseDuration"th-iteration
    else if (implementParams.currentIteration % implementParams.noiseDuration != 0) {
        return;
    }

    // else calculate noise
    if (implementParams.noiseType == 1) {
        // noise on one parameter -> change in all cells the parameter value accordingly
        // get noise value (mean = 0)
        double valueOfParameterAffectedByNoise = implementParams.valueOfParameterAffectedByNoise;
        double sd = implementParams.valueOfParameterAffectedByNoise * implementParams.sdPercentage;
        double noiseValue = Noise::generateNoiseValue(0, sd);
        double newValue = valueOfParameterAffectedByNoise + noiseValue;

        // Change parameter in all cells accordingly
        for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
            cells[cell].changeModelParameter(implementParams.parameterWithNoise, newValue);
        }
    } else if (implementParams.noiseType == 2) {
        // the position of each cell is affected by noise (in all 3 dimensions randomly)
        for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
            double noiseX = generateNoiseValue(0, implementParams.sdPercentage);
            double noiseY = generateNoiseValue(0, implementParams.sdPercentage);
            double noiseZ = generateNoiseValue(0, implementParams.sdPercentage);
            cells[cell].addX(noiseX);
            cells[cell].addY(noiseY);
            cells[cell].addZ(noiseZ);
        }
    }

}

void Noise::getValueOfParameterAffectedByNoise(ImplementParams &implementParams, Cell const &cell) {
    // only if noise is only on one parameter (noiseType == 2)
    if (implementParams.noiseType == 1) {
        double valueOfParameterAffectedByNoise = cell.getModelParamValue(implementParams.parameterWithNoise);
        implementParams.valueOfParameterAffectedByNoise = valueOfParameterAffectedByNoise;
    }
}

double Noise::generateNoiseValue(double mean, double sd) {
    //Instantiation of pseudo random number generator
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::normal_distribution<double> distribution(mean, sd);

    double noiseValue = distribution(generator);
    return noiseValue;
}
