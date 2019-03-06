//
// Created by Stefanie on 26.11.2018.
//

#include <iostream>
#include <cmath>
#include <random>
#include "ProgramMorphoTooth.h"
#include "Input.h"
#include "Initial.h"
#include "Output.h"
#include "Geometrics.h"
#include "Model.h"
#include "ImplementParams.h"
#include "consts.h"
#include "Print.h"
#include "Utility.h"
#include "Noise.h"
#include "Cell.h"

void ProgramMorphoTooth::runProgram(ImplementParams &implementParams, ModelParams &modelParams, int repetition) {
    int success = 0;

    //Vector containing all cells
    Cell cells[totalNrOfCells];

    //Construct the initial grid of cells
    Initial::makeInitialGrid(implementParams, modelParams, cells);

    // If parameter have to be changed, do it
    ProgramMorphoTooth::changeModelParameter(cells, implementParams, repetition);

    // Save in each cell the original model parameter values
    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
        cells[cell].setOriginalModelParams(modelParams);
    }

    //Print information that program has started with value of parameter to change or parameter with Noise
    Print::printStartOfSimulation(implementParams, repetition);

    //The big loop
    //In each iteration mechanisms as diffusion, reaction, growth, and cell division take place
    for (int step = 0; step < implementParams.maxNrOfIterations + 1; ++step) {
        implementParams.currentIteration = step;
        Model::iterationStep(cells, implementParams, modelParams);

        // Check if they were any errors
        Utility::errorTesting(cells, implementParams);

        //Abort the loop if there is an error or if the simulation has to be ended because some bounderies are reached
        if (Utility::errorTesting(cells, implementParams)) {
            break;
        } else if (implementParams.endOfSimulation) {
            break;
        }

        //Abort the loop if maxNrOfIterations or maxNrOfCells is reached (success = 1), make an output if a multiple of minNrOfCells is
        //achieved (success = 2 or greater) or just continue with the simulation (success = 0)
        success = Utility::endOfSimulation(implementParams, step, success);
        if (success == 1) {
            break;
        } else if (success >= 2) {
            Output::plyOutput(cells, implementParams, repetition, success);
            Output::ROutput(cells, implementParams, repetition, success);
            Output::XYZOutputSimple(cells, implementParams, repetition, success);
        }
        // not yet finished (success == 0) --> go on with simulation

        //For debugging
        if (implementParams.currentIteration == 5831) {
            int a = 0;
            Output::ROutput(cells, implementParams, repetition, success);
        }

        //Print every "printInterval" iteration the count
        if (step % implementParams.printInterval == 0) {
            std::cout << step << std::endl;
            std::cout << "Cells in simulation: " << implementParams.nrCellsInSimulation << std::endl;
            std::cout.flush();
        }

        //All x iterations do an output
        if (implementParams.outputInterval != 0) {
            if (step % implementParams.outputInterval == 0) {
                Output::ROutput(cells, implementParams, repetition, success);
            }
        }
    }

    Print::printEndOfSimulation();
}

void ProgramMorphoTooth::changeModelParameter(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams,
                                              int condition) {
    // if no parameter has to be changed (parameterToChange = -1), skip this
    if (implementParams.parameterToChange == "") {
        return;
    }

    //Calculate starting condition
    double valueOfParameterToChange = cells[first].getModelParamValue(implementParams.parameterToChange);
    double startingValueDouble = valueOfParameterToChange -
                                 (valueOfParameterToChange * implementParams.totalPlusMinusScope);

    // Calculate the change per step (per condition)
    double changePerConditionDouble = valueOfParameterToChange * implementParams.percentageSteps;

    // Calculate current value of the parameter
    double newParameterValue = (condition * changePerConditionDouble) + startingValueDouble;
    implementParams.valueOfParameterToChange = newParameterValue;

    // Change modelParams accordingly in all cells
    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
        cells[cell].changeModelParameter(implementParams.parameterToChange, newParameterValue);
    }
}

void ProgramMorphoTooth::calculateNrOfConditions(ImplementParams &implementParams) {
    double conditionsDouble;
    int conditions;

    if (implementParams.totalPlusMinusScope == 0 || implementParams.parameterToChange == "") {
        conditions = 1;
    } else {
        conditionsDouble =
                (2 * implementParams.totalPlusMinusScope / implementParams.percentageSteps) +
                1; // in both directions -> *2
        conditions = static_cast<int>(std::floor(conditionsDouble + 0.5));
    }

    implementParams.nrOfConditions = conditions;
}





