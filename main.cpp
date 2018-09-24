#include <iostream>
#include "Input.h"
#include "Initial.h"
#include "Output.h"
#include "Geometrics.h"
#include "Model.h"
#include "Parameters.h"


int main() {

    //Make instance of Parameters
    Parameters params = Input::defineParametersSealTest();

    //Construct the initial grid of cells
    std::vector<Cell> cells = Initial::makeInitialGrid(params);

    for (int cell = 0; cell < 19; ++cell) {
        cells[cell].resetTempCoordinates();
    }

    Model::diffusion(cells, params);
    Model::reaction(cells, params);
    Model::buccalLingualBias(cells, params);
    Model::differentiation(cells, params);
    Model::epithelialProliferation(cells, params);
    Model::buoyancy(cells, params);
    Model::repulsion(cells, params);
    Model::nucleusTraction(cells, params);
    Model::anteriorPosteriorBias(cells, params);
    Model::applyForces(cells, params);

    for (int cell = 0; cell < 7; ++cell) {
        std::vector<double> xBorders = cells[cell].getBorderPointsX();
        std::vector<double> yBorders = cells[cell].getBorderPointsY();
        std::vector<double> zBorders = cells[cell].getBorderPointsZ();

        std::cout << "Cell Nr.:" << cell << std::endl;

        for (int borderPoint = 0; borderPoint < xBorders.size(); ++borderPoint) {
            std::cout << xBorders[borderPoint] << std::endl;
            std::cout << yBorders[borderPoint] << std::endl;
            std::cout << zBorders[borderPoint] << std::endl;
        }
    }

    Output::initialCellCentersXY(cells, params.nrCellsInSimulation);
    Output::initialCellBordersXY(cells, params.nrCellsInSimulation);

    return 0;
}