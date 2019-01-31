//
// Created by Stefanie on 26.11.2018.
//

#include <iostream>
#include <cmath>
#include "ProgramMorphoTooth.h"
#include "Input.h"
#include "Initial.h"
#include "Output.h"
#include "Geometrics.h"
#include "Model.h"
#include "Parameters.h"
#include "consts.h"
#include "Print.h"
#include "Utility.h"

void ProgramMorphoTooth::runProgram(Parameters &params, int repetition) {

    //Print information that program is started with value of parameter to change
    Print::printStartOfSimulation(params);

    //Vector containing all cells
    Cell cells[totalNrOfCells];

    //Construct the initial grid of cells
    Initial::makeInitialGrid(params, cells);

    //The big loop
    //In each iteration mechanisms as diffusion, reaction, growth, and cell division take place
    for (int step = 0; step < params.maxNrOfIterations + 1; ++step) {
        params.currentIteration = step;
        Model::iterationStep(cells, params);

        //Abort the loop if there is an error
        if (Utility::errorTesting(cells, params)) {
            break;
        }

        //Abort the loop if one of the end-determining variables reaches its maximum (number of cell divisions or iteration)
        if (Utility::endOfSimulation(params, step)) {
            break;
        }

        //For debugging
        if (params.currentIteration == 9751) {
            int a = 0;
        }

        //Print every "printInterval" iteration the count
        if (step % params.printInterval == 0) {
            std::cout << step << std::endl;
            std::cout << "Cells in simulation: " << params.nrCellsInSimulation << std::endl;
            std::cout.flush();
        }

        //All x iterations do an output
        if (step % params.outputInterval == 0) {
            if (params.parameterWithNoise > 0) {
                Output::RNoiseOutput(cells, params, repetition);
            }
            if (params.parameterToChange > 0){
                Output::RParameterChange(cells, params);
            }
        }
    }

    // Create OutputFiles anyway at end of simulation (also if there was an error)
    Output::plyOutput(cells, params, repetition);
    if (params.parameterWithNoise > 0) {
        Output::RNoiseOutput(cells, params, repetition);
    }
    if (params.parameterToChange > 0){
        Output::RParameterChange(cells, params);
    }

    Print::printEndOfSimulation();

}

void ProgramMorphoTooth::runProgramWithDifferentConditions(Parameters &paramsInitial, std::string nameInputFileTemp) {
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
        Parameters params = Input::setParameters(nameInputFileTemp);

        // run the program with current conditions
        ProgramMorphoTooth::runProgram(params, 0);

        // change the conditions
        double newValue = ((condition + 1) * changePerConditionDouble) + startingValueDouble;
        Input::changeInputFileTemp(params, newValue, nameInputFileTemp);

    }
}




