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
        double valueOfParameterAffectedByNoise = cells[first]
                .getOriginalModelParamValue(implementParams.parameterWithNoise);
        double sd = valueOfParameterAffectedByNoise * implementParams.sdPercentage;
        double noiseValue = Noise::generateNoiseValue(0, sd);
        double newValue = valueOfParameterAffectedByNoise + noiseValue;

        // Change parameter in all cells accordingly
        for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
            cells[cell].changeModelParameter(implementParams.parameterWithNoise, newValue);
        }
    } else if (implementParams.noiseType == 2) {
        // global noise on all parameters
        for (int parameter = 0; parameter < nrOfModelParams; ++parameter) {
            double valueOfParameterAffectedByNoise = cells[first].getOriginalModelParamValue(parameter);
            double sd = valueOfParameterAffectedByNoise * implementParams.sdPercentage;
            double noiseValue = Noise::generateNoiseValue(0, sd);
            double newValue = valueOfParameterAffectedByNoise + noiseValue;

            // Change parameter in all cells accordingly
            for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
                cells[cell].changeModelParameter(implementParams.parameterWithNoise, newValue);
            }
        }
    } else if (implementParams.noiseType == 3) {
        // cell-specific noise on all parameters
        for (int parameter = 0; parameter < nrOfModelParams; ++parameter) {
            double valueOfParameterAffectedByNoise = cells[first].getOriginalModelParamValue(parameter);
            double sd = valueOfParameterAffectedByNoise * implementParams.sdPercentage;
            double noiseValue = Noise::generateNoiseValue(0, sd);
            double newValue = valueOfParameterAffectedByNoise + noiseValue;

            // Change parameter in all cells accordingly
            for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
                // only for border cells
                if (!cells[cell].isInCentre()) {
                    cells[cell].changeModelParameter(implementParams.parameterWithNoise, newValue);
                }
            }
        }
    } else if (implementParams.noiseType == 4) {
        // the position of each cell is affected by noise (in all 3 dimensions randomly)
        for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
            double noiseX = generateNoiseValue(0, implementParams.sdPercentage);
            double noiseY = generateNoiseValue(0, implementParams.sdPercentage);
            double noiseZ = generateNoiseValue(0, implementParams.sdPercentage);
            cells[cell].addX(noiseX);
            cells[cell].addY(noiseY);
            cells[cell].addZ(noiseZ);
        }
    } else if (implementParams.noiseType == 5) {
        // cell-specific noise on position
        for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
            // only on border cells
            if (!cells[cell].isInCentre()) {
                double noiseX = generateNoiseValue(0, implementParams.sdPercentage);
                double noiseY = generateNoiseValue(0, implementParams.sdPercentage);
                double noiseZ = generateNoiseValue(0, implementParams.sdPercentage);
                cells[cell].addX(noiseX);
                cells[cell].addY(noiseY);
                cells[cell].addZ(noiseZ);
            }
        }
    } else if (implementParams.noiseType == 6) {
        // global noise on protein concentrations
        for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
            for (int protein = 0; protein < nrOfProteins; ++protein) {
                for (int layer = 0; layer < cells[first].getMesenchymeThickness(); ++layer) {
                    double concentration = cells[cell].getProteinConcentrations()[protein][layer];
                    double noiseValue = Noise::generateNoiseValue(0, implementParams.sdPercentage);
                    double newValue = concentration + noiseValue;

                    cells[cell].addProteinConcentration(protein, layer, newValue);
                }
            }
        }
    } else if (implementParams.noiseType == 7) {
        // cell specific noise on protein concentrations
        for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
            if (!cells[cell].isInCentre()) { // only for border cells
                for (int protein = 0; protein < nrOfProteins; ++protein) {
                    for (int layer = 0; layer < cells[first].getMesenchymeThickness(); ++layer) {
                        double concentration = cells[cell].getProteinConcentrations()[protein][layer];
                        double noiseValue = Noise::generateNoiseValue(0, implementParams.sdPercentage);
                        double newValue = concentration + noiseValue;

                        cells[cell].addProteinConcentration(protein, layer, newValue);
                    }
                }
            }
        }
    }
}

double Noise::generateNoiseValue(double mean, double sd) {
    //Instantiation of pseudo random number generator
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::normal_distribution<double> distribution(mean, sd);

    double noiseValue = distribution(generator);
    return noiseValue;
}
