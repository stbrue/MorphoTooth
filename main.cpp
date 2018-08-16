#include <iostream>
#include "Cell.h"
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

    Model::diffusion(cells, params);
    Model::reaction(cells, params);
    Model::buccalLingualBias(cells, params);
    Model::differenciation(cells, params);

    for (int cell = 0; cell < 19; ++cell) {
        std::cout << "Cell Nr.:" << cell << std::endl;
        std::cout << cells[cell].getPerimeter() << std::endl;
        std::cout << cells[cell].getCellArea() << std::endl;
    }

    return 0;
}