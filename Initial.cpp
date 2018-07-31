//
// Created by Stefanie on 30.07.2018.
//

#include "Initial.h"
#define _USE_MATH_DEFINES
#include <math.h>

int Initial::getTotalNumberOfCells(int initialRadius)
{
    int j = 0;
    for (int i = 1; i <= initialRadius; ++i) {
        j += i;
    }
    return (6 * j + 1);
}

int Initial::getNumberOfInSimulationCells(int initialRadius)
{
    int j = 0;
    for (int i = 1; i < initialRadius; ++i) {
        j += i;
    }
    return (6 * j + 1);
}

void Initial::makeInitialGrid(std::vector<Cell>& cells, int cellsInSimulation)
{
    for (int cell = 1; cell <= cellsInSimulation; ++cell) {
        makeNeighbours(cells[cell]);
    }

}

double Initial::nextX(double centerX, int neighbour)
{
    double a = (2 * M_PI) / 360; //to transform from degree into rad
    return (centerX + (distanceBetweenCells * sin(a * (60 * neighbour - 1))));
}

void Initial::makeNeighbours(Cell& centreCell)
{
    for (int neighbour = 1; neighbour <= 6; ++neighbour) {
        double x = nextX(centreCell.getX(), neighbour);

    }
}
