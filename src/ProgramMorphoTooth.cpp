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

void ProgramMorphoTooth::runProgram(Parameters &params) {

    //Construct the initial grid of cells
    std::vector<Cell> cells = Initial::makeInitialGrid(params);

    //The big loop
    //In each iteration mechanisms as diffusion, reaction, growth, and cell division take place
    for (int step = 0; step < params.maxNrOfIterations; ++step) {
        Model::iterationStep(cells, params, step);

        //Abort the loop if there is an error
        if (params.error) {
            std::cout << "The loop is stopped because there was an error at iteration: " << step << std::endl;
            break;
        }

        if (params.cellDivisionCount >= params.maxCellDivisionCount) {
            std::cout << "The loop is stopped because this was cell division number " << params.cellDivisionCount
                      << std::endl;
            std::cout << "This was at iteration " << step << std::endl;
            break;
        }

        if (params.currentIteration == params.maxNrOfIterations) {
            break;
        }

        //Print every 100 iteration the count
        if (step % params.printInterval == 0) {
            std::cout << step << std::endl;
            std::cout << "ncels: " << params.nrCellsInSimulation << std::endl;
            std::cout.flush();
        }


        /*//All 1000 iterations do an output
        if (step % params.outputInterval == 0) {
            Output::ROutput(cells, params);
            Output::geomorphLinkOutput(cells, params);
            Output::XYZOutputSimple(cells, params);
        }*/
        params.currentIteration += 1;
    }

    Output::ROutput(cells, params);
    Output::geomorphLinkOutput(cells, params);
    Output::XYZOutputSimple(cells, params);

}

void ProgramMorphoTooth::runProgramWithDifferentConditions(Parameters &paramsInitial, bool parameterToChangeIsInt) {

    //Calculate how many conditions there are
    double conditionsDouble =
            (2 * paramsInitial.totalPlusMinusScope / paramsInitial.percentageSteps) + 1; // in both directions -> *2
    int conditions = static_cast<int>(std::floor(conditionsDouble + 0.5));
    paramsInitial.nrOfConditions = conditions;

    if (parameterToChangeIsInt) {
        //Calculate starting condition
        double startingValueDouble = paramsInitial.valueOfParameterToChange -
                                     (paramsInitial.valueOfParameterToChange * paramsInitial.totalPlusMinusScope);
        int startingValue = static_cast<int>(std::floor(startingValueDouble + 0.5));

        // Calculate the change per step (per condition)
        double changePerConditionDouble = paramsInitial.valueOfParameterToChange * paramsInitial.percentageSteps;
        int changePerCondition = static_cast<int>(std::floor(changePerConditionDouble + 0.5));

        //Set starting conditions
        Input::changeInputFile(paramsInitial, startingValue);

        //Loop that starts the program with different conditions (input parameters)
        for (int condition = 0; condition < paramsInitial.nrOfConditions; ++condition) {
            //Re-read the InputFile
            Parameters params = Input::setParameters();

            // run the program with current conditions
            ProgramMorphoTooth::runProgram(params);

            // change the conditions
            double newValueDouble = ((condition + 1) * changePerCondition) + paramsInitial.valueOfParameterToChange;
            int newValue = static_cast<int>(std::floor(newValueDouble + 0.5));
            Input::changeInputFile(params, newValue);
        }

    } else {
        //Calculate starting condition
        double startingValueDouble = paramsInitial.valueOfParameterToChange -
                                     (paramsInitial.valueOfParameterToChange * paramsInitial.totalPlusMinusScope);

        // Calculate the change per step (per condition)
        double changePerConditionDouble = paramsInitial.valueOfParameterToChange * paramsInitial.percentageSteps;

        //Set starting conditions
        Input::changeInputFile(paramsInitial, startingValueDouble);

        //Loop that starts the program with different conditions (input parameters)
        for (int condition = 0; condition < paramsInitial.nrOfConditions; ++condition) {
            //Re-read the InputFile
            Parameters params = Input::setParameters();

            // run the program with current conditions
            ProgramMorphoTooth::runProgram(params);

            // change the conditions
            double newValue = ((condition + 1) * changePerConditionDouble) + paramsInitial.valueOfParameterToChange;
            Input::changeInputFile(params, newValue);

        }
    }


}