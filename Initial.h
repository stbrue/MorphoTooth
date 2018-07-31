//
// Created by Stefanie on 30.07.2018.
//

#ifndef TOOTHMAKER_INITIAL_H
#define TOOTHMAKER_INITIAL_H


#include "Cell.h"

class Initial {

private:
    int distanceBetweenCells = 1;



public:
    int getTotalNumberOfCells(int initialRadius) {};
    int getNumberOfInSimulationCells(int initialRadius) {};
    void makeInitialGrid(Cell cell1) {};

    double Initial::nextX(double centerX, int neighbour) {};
    void Initial::makeInitialGrid(std::vector<Cell>& cells, int cellsInSimulation) {};
    void Initial::makeNeighbours(Cell& centreCell) {};

};


#endif //TOOTHMAKER_INITIAL_H
