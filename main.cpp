#include <iostream>
#include "Cell.h"
#include "Initial.h"
#include "Output.h"

int main() {

    //Parameters
    int InitialRadius = 3;

    //Calculate the amount of cells involved in simulations (that have 6 neighbours)
    int InSimulationCells = Initial::getNumberOfInSimulationCells(InitialRadius);

    //Construct the initial grid of cells
    std::vector<Cell> cells = Initial::makeInitialGrid(InSimulationCells);

    //Cell::printCellBorders(cells, InSimulationCells);

    Output::initialCellCentersXY(cells, InSimulationCells);
    Output::initialCellBordersXY(cells, InSimulationCells);

    return 0;
}