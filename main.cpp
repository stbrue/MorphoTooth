#include <iostream>
#include "Cell.h"
#include "Initial.h"

int main() {

    //Parameters
    int InitialRadius = 3;

    //Calculate the amount of cells involved in simulations (that have 6 neighbours)
    int InSimulationCells = Initial::getNumberOfInSimulationCells(InitialRadius);

    //Construct the initial grid of cells
    std::vector<Cell> cells = Initial::makeInitialGrid(InSimulationCells);

    return 0;
}