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

void ProgramMorphoTooth::runProgram(ImplementParams &implementParams, ModelParams &modelParams, int repetition) {
    int success = 0;

    //Print information that program has started with value of parameter to change or parameter with Noise
    Print::printStartOfSimulation(implementParams, repetition);

    //Vector containing all cells
    Cell cells[totalNrOfCells];

    //Construct the initial grid of cells
    Initial::makeInitialGrid(implementParams, modelParams, cells);

    // A struct that holds the parameter values with noise added
    //ImplementParams noiseParams = params;

    //The big loop
    //In each iteration mechanisms as diffusion, reaction, growth, and cell division take place
    for (int step = 0; step < implementParams.maxNrOfIterations + 1; ++step) {
        implementParams.currentIteration = step;
        Model::iterationStep(cells, implementParams, modelParams);

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
        if (implementParams.currentIteration == 9751) {
            int a = 0;
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
 /*
void ProgramMorphoTooth::runProgramWithDifferentConditions(ImplementParams &paramsInitial, std::string nameInputFileTemp) {
    //Calculate how many conditions there are
    double conditionsDouble;
    int conditions;

    if (paramsInitial.totalPlusMinusScope == 0) {
        conditions = 1;
    } else {
        conditionsDouble =
                (2 * paramsInitial.totalPlusMinusScope / paramsInitial.percentageSteps) + 1; // in both directions -> *2
        conditions = static_cast<int>(std::floor(conditionsDouble + 0.5));
    }

    paramsInitial.nrOfConditions = conditions;

    //Calculate starting condition
    double startingValueDouble = paramsInitial.valueOfParameterToChange -
                                 (paramsInitial.valueOfParameterToChange * paramsInitial.totalPlusMinusScope);

    // Calculate the change per step (per condition)
    double changePerConditionDouble = paramsInitial.valueOfParameterToChange * paramsInitial.percentageSteps;

    //Set starting conditions
    Input::changeInputFileTemp(paramsInitial, startingValueDouble, nameInputFileTemp);

    //Loop that starts the program with different conditions (input parameters)
    for (int condition = 0; condition < paramsInitial.nrOfConditions; ++condition) {
        //Re-read the InputFileTemp
        ImplementParams params = Input::setParameters(nameInputFileTemp);

        // run the program with current conditions
        ProgramMorphoTooth::runProgram(params, 0);

        // change the conditions
        double newValue = ((condition + 1) * changePerConditionDouble) + startingValueDouble;
        Input::changeInputFileTemp(params, newValue, nameInputFileTemp);

    }
}
  */




