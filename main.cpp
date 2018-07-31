#include <iostream>
#include "Cell.h"
#include "Initial.h"

int main() {

    //Parameters
    int InitialRadius = 3;

    //Make the first cell
    Cell cell1(0, 0, 1);

    //Vector containing all cells
    std::vector<Cell> cells;

    //The first one is a placeholder (ID = index)
    cells.push_back(cell1);

    //Calculate the amount of cells involved in simulations (that have 6 neighbours)
    int InSimulationCells = Initial::getNumberOfInSimulationCells(InitialRadius);
    std::cout << "ncels = " << InSimulationCells;

    //Construct the initial grid of cells
    Initial::makeInitialGrid(cells, InSimulationCells);


    return 0;
}