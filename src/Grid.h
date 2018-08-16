//
// Created by Stefanie on 06.08.2018.
//

#ifndef TOOTHMAKER_GRID_H
#define TOOTHMAKER_GRID_H


#include "Cell.h"

class Grid {

public:
    static void calculateInitialCellBorders(std::vector<Cell> &cells, int cellsInSimulation);
    static void setBorders(std::vector<Cell> &cells, int centreCell, int neighbour1, int neighbour2);


};


#endif //TOOTHMAKER_GRID_H
