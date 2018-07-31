//
// Created by Stefanie on 30.07.2018.
//

#include "Initial.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

bool operator== (const Cell &c1, const Cell &c2)
{
    return(c1.getX()==c2.getX() && c1.getY()==c2.getY() && c1.getZ()==c2.getZ());
}

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

void Initial::makeInitialGrid(std::vector<Cell> &cells, int cellsInSimulation)
{
    int IDNewCell = 1;
    for (int i = 1; i <= cellsInSimulation; ++i) {
        makeNeighbours(cells, i, IDNewCell);
    }
}

double Initial::nextX(double centerCoordinate, int neighbour)
{
    double a = (2 * M_PI) / 360; //to transform from degree into rad
    return (centerCoordinate + (distanceBetweenCells * sin(a * (60 * neighbour - 1))));
}

double Initial::nextY(double centerCoordinate, int neighbour)
{
    double a = (2 * M_PI) / 360; //to transform from degree into rad
    return (centerCoordinate + (distanceBetweenCells * cos(a * (60 * neighbour - 1))));
}

void Initial::makeNeighbours(std::vector<Cell> &cells, int IDCentreCell, int &IDNewCell)
{
    IDCentreCell = 1;
    //for each  neighbour cell of the centreCell
    for (int neighbour = 0; neighbour < 6; ++neighbour) {
        //define the coordinates of the neighbour
        double x = nextX(cells[IDCentreCell].getX(), neighbour);
        double y = nextY(cells[IDCentreCell].getY(), neighbour);

        //create a temporary Instance of this cell
        Cell tempCell(x, y, IDNewCell);

        //check if this neighbour is already an existing cell
        for(auto cell : cells)
        {
            if(cell == tempCell)
            {
                //declare it as a neighbour
                cells[IDCentreCell].setNeighbour(IDNewCell);
            }
            else
            {
                //Create this new cell
                cells.push_back(tempCell);
                //Declare it as a neighbour
                cells[IDCentreCell].setNeighbour(IDNewCell);
                IDNewCell++;
            }
        }
    }
}




