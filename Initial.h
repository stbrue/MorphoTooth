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

    static double nextX(double centerX, int neighbour);
    static double nextY(double centerX, int neighbour);
    static std::vector<Cell> makeInitialGrid(int cellsInSimulation);
    static void makeNeighbours(std::vector<Cell> &cells, int IDCentreCell, int &IDNewCell);

    static void printInitialGrid(std::vector<Cell> &cells);

    static void labelCellsInSimulation(std::vector<Cell> &cells, int cellsInSimulation);

};


#endif //TOOTHMAKER_INITIAL_H
