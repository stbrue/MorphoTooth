#include <iostream>
#include "Initial.h"
#include "Output.h"
#include "Geometrics.h"
#include "Model.h"
#include "Parameters.h"


int main() {

    //Make instance of Parameters
    Parameters params;

    //Construct the initial grid of cells
    std::vector<Cell> cells = Initial::makeInitialGrid(params);

    for (int cell = 0; cell < 19; ++cell) {
        cells[cell].resetTempCoordinates();
    }

    Model::diffusion(cells, params);
    Model::reaction(cells, params);
    Model::buccalLingualBias(cells, params);
    Model::differenciation(cells, params);
    Model::epithelialProliferation(cells, params);
    Model::buoyancy(cells, params);

    for (int cell = 0; cell < 19; ++cell) {
        std::cout << "Cell Nr.:" << cell << std::endl;
        std::cout << cells[cell].getTempX() << std::endl;
        std::cout << cells[cell].getTempY() << std::endl;
        std::cout << cells[cell].getTempZ() << std::endl;
    }

    return 0;
}