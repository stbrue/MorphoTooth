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

    // do noise only between noiseStart and noiseEnd
    if (implementParams.currentIteration < implementParams.noiseStart
        || implementParams.currentIteration > implementParams.noiseEnd) {
        return;
    }

        // and do noise calculation only every "noiseInterval"th-iteration
    else if (implementParams.currentIteration % implementParams.noiseInterval != 0) {
        return;
    }

    // else calculate noise
    unsigned seed = implementParams.noiseSeed;
    if (implementParams.noiseType == 1) {
        // noise on one parameter -> change in all cells the parameter value accordingly
        // get noise value (mean = 0)
        double valueOfParameterAffectedByNoise = cells[first]
                .getOriginalModelParamValue(implementParams.parameterWithNoise);
        double sd = valueOfParameterAffectedByNoise * implementParams.sd;
        double noiseValue = Noise::generateNoiseValue(0, sd, seed);
        double newValue = valueOfParameterAffectedByNoise + noiseValue;

        // Change parameter in all cells accordingly
        for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
            cells[cell].changeModelParameter(implementParams.parameterWithNoise, newValue);
        }
    } else if (implementParams.noiseType == 2) {
        // global noise on all parameters
        std::vector<std::string> paramNames = getModelParameterNamesList();
        for (int parameter = 0; parameter < paramNames.size(); ++parameter) {
            double valueOfParameterAffectedByNoise = cells[first].getOriginalModelParamValue(paramNames[parameter]);
            double sd = valueOfParameterAffectedByNoise * implementParams.sd;
            double noiseValue = Noise::generateNoiseValue(0, sd, seed);
            double newValue = valueOfParameterAffectedByNoise + noiseValue;

            // Change parameter in all cells accordingly
            for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
                cells[cell].changeModelParameter(paramNames[parameter], newValue);
            }
        }
    } else if (implementParams.noiseType == 3) {
        // cell-specific noise on all parameters
        std::vector<std::string> paramNames = getModelParameterNamesList();
        for (int parameter = 0; parameter < paramNames.size(); ++parameter) {
            double valueOfParameterAffectedByNoise = cells[first].getOriginalModelParamValue(paramNames[parameter]);
            double sd = valueOfParameterAffectedByNoise * implementParams.sd;
            double noiseValue = Noise::generateNoiseValue(0, sd, seed);
            double newValue = valueOfParameterAffectedByNoise + noiseValue;

            // Change parameter in all cells accordingly
            for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
                // only for border cells
                if (!cells[cell].isInCentre()) {
                    cells[cell].changeModelParameter(paramNames[parameter], newValue);
                }
            }
        }
    } else if (implementParams.noiseType == 4) {
        // the position of each cell is affected by noise (in all 3 dimensions randomly)
        for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
            double noiseX = generateNoiseValue(0, implementParams.sd, seed);
            double noiseY = generateNoiseValue(0, implementParams.sd, seed);
            double noiseZ = generateNoiseValue(0, implementParams.sd, seed);
            cells[cell].addTempX(noiseX);
            cells[cell].addTempY(noiseY);
            cells[cell].addTempZ(noiseZ);
        }
    } else if (implementParams.noiseType == 5) {
        // cell-specific noise on position
        for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
            // only on border cells
            if (!cells[cell].isInCentre()) {
                double noiseX = generateNoiseValue(0, implementParams.sd, seed);
                double noiseY = generateNoiseValue(0, implementParams.sd, seed);
                double noiseZ = generateNoiseValue(0, implementParams.sd, seed);
                cells[cell].addTempX(noiseX);
                cells[cell].addTempY(noiseY);
                cells[cell].addTempZ(noiseZ);
            }
        }
    } else if (implementParams.noiseType == 6) {
        // global noise on protein concentrations
        for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
            for (int protein = 0; protein < nrOfProteins; ++protein) {
                for (int layer = 0; layer < cells[first].getMesenchymeThickness(); ++layer) {
                    double concentration = cells[cell].getProteinConcentrations()[protein][layer];
                    double sd = concentration * implementParams.sd;
                    double noiseValue = Noise::generateNoiseValue(0, sd, seed);

                    cells[cell].addProteinConcentration(protein, layer, noiseValue);
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
                        double noiseValue = Noise::generateNoiseValue(0, implementParams.sd, seed);

                        cells[cell].addProteinConcentration(protein, layer, noiseValue);
                    }
                }
            }
        }
    }
}

double Noise::generateNoiseValue(double mean, double sd, unsigned seed) {
    // Set seed to clock time if not given by input (if seed < 0)
    if (seed < 1) {
        seed = std::chrono::system_clock::now().time_since_epoch().count();
    }
    //Instantiation of pseudo random number generator
    std::default_random_engine generator(seed);
    std::normal_distribution<double> distribution(mean, sd);

    // Generation of random value
    double noiseValue = distribution(generator);
    return noiseValue;
}
