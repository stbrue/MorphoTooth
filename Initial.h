//
// Created by Stefanie on 30.07.2018.
//

#ifndef TOOTHMAKER_INITIAL_H
#define TOOTHMAKER_INITIAL_H


#include "Cell.h"

class Initial {

private:
    static const int distanceBetweenCells = 1;



public:
    int getTotalNumberOfCells(int initialRadius);
    static int getNumberOfInSimulationCells(int initialRadius);
    static void makeInitialGrid(Cell cell1);

    static double nextX(double centerX, int neighbour);
    static double nextY(double centerX, int neighbour);
    static void makeInitialGrid(std::vector<Cell>& cells, int cellsInSimulation);
    static void makeNeighbours(std::vector<Cell> &cells, int IDCentreCell, int &IDNewCell);


};


#endif //TOOTHMAKER_INITIAL_H
