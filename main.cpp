#include <iostream>
#include "Cell.h"
#include "Initial.h"
#include "Output.h"
#include "Geometrics.h"
#include "Model.h"

int main() {

    //Parameters
    int InitialRadius = 3;
    int iterations = 3;

    //Construct the initial grid of cells
    std::vector<Cell> cells = Initial::makeInitialGrid(InitialRadius);

    Model::diffusion(cells, 19);

    for (int cell = 0; cell < 19; ++cell) {
        std::cout << "Cell Nr.:" << cell << std::endl;
        std::cout << cells[cell].getPerimeter() << std::endl;
        std::cout << cells[cell].getCellArea() << std::endl;
    }

    return 0;
}