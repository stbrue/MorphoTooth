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

void Initial::makeInitialGrid(std::vector<Cell>& cells, int cellsInSimulation)
{
    int IDNewCell = 2;
    for (int cell = 1; cell <= cellsInSimulation; ++cell) {
        makeNeighbours(cells, cell, IDNewCell);
    }
}

double Initial::nextCoordinate(double centerCoordinate, int neighbour)
{
    double a = (2 * M_PI) / 360; //to transform from degree into rad
    return (centerCoordinate + (distanceBetweenCells * sin(a * (60 * neighbour - 1))));
}

void Initial::makeNeighbours(std::vector<Cell> &cells, int IDCentreCell, int &IDNewCell)
{
    //for each  neighbour cell of the centreCell
    for (int neighbour = 1; neighbour <= 6; ++neighbour) {
        //define the coordinates of the neighbour
        double x = nextCoordinate(cells[IDCentreCell].getX(), neighbour);
        double y = nextCoordinate(cells[IDCentreCell].getY(), neighbour);

        //create a temporary Instance of this cell
        Cell tempCell(x, y, 1000);

        //check if this neighbour is already an existing cell
        for(auto cell : cells)
        {
            if(cell == tempCell)
            {
                //declare it as a neighbour
                cells[IDCentreCell].setNeighbour(IDNewCell, neighbour);
                cell.setNeighbour(IDNewCell, getNeighbourRelation(neighbour));
            }
            else
            {
                //Create this new cell
                cells[IDNewCell] = tempCell;
                IDNewCell++;
                //Declare it as a neighbour
                cells[IDCentreCell].setNeighbour(IDNewCell, neighbour);
                cell.setNeighbour(IDNewCell, getNeighbourRelation(neighbour));
            }
        }
    }
}

int Initial::getNeighbourRelation(int neighbour)
{
    switch (neighbour)
    {
        case 1:
            return 4;
        case 2:
            return 5;
        case 3:
            return 6;
        case 4:
            return 1;
        case 5:
            return 2;
        case 6:
            return 3;
        default:
            std::cout << "Error in Neighbour Declaration" << std::endl;
    }
}


