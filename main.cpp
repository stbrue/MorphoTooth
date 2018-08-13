#include <iostream>
#include "Cell.h"
#include "Initial.h"
#include "Output.h"
#include "Geometrics.h"

int main() {

    //Parameters
    int InitialRadius = 3;

    //Construct the initial grid of cells
    std::vector<Cell> cells = Initial::makeInitialGrid(InitialRadius);



    return 0;
}