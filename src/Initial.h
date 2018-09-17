//
// Created by Stefanie on 30.07.2018.
//

#ifndef TOOTHMAKER_INITIAL_H
#define TOOTHMAKER_INITIAL_H


#include "Cell.h"
#include "Parameters.h"

/**
 * @brief   Set up of the initial cell grid
 *
 * @details Calculates the positions of new cells and instantiates them
 */
class Initial {

private:
    static const int distanceBetweenCells = 1;


public:
    int getTotalNumberOfCells(int initialRadius);

    static int getNumberOfInSimulationCells(int initialRadius);

    static double nextX(double centerX, int neighbour);

    static double nextY(double centerX, int neighbour);

    static std::vector<Cell> makeInitialGrid(Parameters &params);

    static void makeNeighbours(std::vector<Cell> &cells, int IDCentreCell, int &IDNewCell);

    static void printInitialGrid(std::vector<Cell> &cells);

    static void printInitialNeighbours(std::vector<Cell> cells);

    static void labelNrCellsInSimulation(std::vector<Cell> &cells, Parameters &params);

    static void labelCellsInCentre(std::vector<Cell> &cells, Parameters &params);

    static void reduceNeighboursOutOfSimulation(std::vector<Cell> &cells, int nrCellsInSimulation);

    static bool isNeighbourInSimulation(std::vector<Cell> &cells, int IDCentreCell, int neighbour);

    static void calculateInitialCellBorders(std::vector<Cell> &cells, int nrCellsInSimulation);
    static void setBorders(std::vector<Cell> &cells, int centreCell, int neighbour1, int neighbour2);
};


#endif //TOOTHMAKER_INITIAL_H
