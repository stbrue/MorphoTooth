//
// Created by Stefanie on 26.11.2018.
//

#include <iostream>
#include "ProgramMorphoTooth.h"
#include "Input.h"
#include "Initial.h"
#include "Output.h"
#include "Geometrics.h"
#include "Model.h"
#include "Parameters.h"

void ProgramMorphoTooth::runProgram() {
    //Make instance of Parameters by reading in the parameters from input file
    Parameters params = Input::setParameters();

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