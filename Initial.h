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
    int getTotalNumberOfCells(int initialRadius);
    int getNumberOfInSimulationCells(int initialRadius);
    void makeInitialGrid(Cell cell1);

    double nextCoordinate(double centerX, int neighbour);
    void makeInitialGrid(std::vector<Cell>& cells, int cellsInSimulation);
    void makeNeighbours(std::vector<Cell> &cells, int IDCentreCell, int &IDNewCell);
    int getNeighbourRelation(int neighbour);

};


#endif //TOOTHMAKER_INITIAL_H
