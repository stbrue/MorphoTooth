#include <iostream>
#include "Input.h"
#include "Initial.h"
#include "Output.h"
#include "Geometrics.h"
#include "Model.h"
#include "Parameters.h"


int main() {

    //Make instance of Parameters
    Parameters params = Input::defineParameters();

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
        std::cout << "Cell Nr.:" << cell << std::endl;
        std::cout << cells[cell].getX() << std::endl;
        std::cout << cells[cell].getY() << std::endl;
        std::cout << cells[cell].getZ() << std::endl;
    }

    return 0;
}