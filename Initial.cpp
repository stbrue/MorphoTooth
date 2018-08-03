//
// Created by Stefanie on 30.07.2018.
//

#include "Initial.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include "Cell.h"

std::vector<Cell> Initial::makeInitialGrid(int cellsInSimulation)
{
    //Make the first cell
    Cell cell1(0, 0, 0);

    //Vector containing all cells
    std::vector<Cell> cells;

    //The first cell is a placeholder
    cells.push_back(cell1);

    int IDNewCell = 1;
    for (int centreCell = 0; centreCell < cellsInSimulation; ++centreCell) {
        makeNeighbours(cells, centreCell, IDNewCell);
    }

    //Define for each cell if it is "within simulation"
    labelCellsInSimulation(cells, cellsInSimulation);

    return cells;
}

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

double Initial::nextX(double centerCoordinate, int neighbour)
{
    double a = (2 * M_PI) / 360; //to transform from degree into rad
    double x;
    x = centerCoordinate + (distanceBetweenCells * sin(a * (60 * neighbour)));
    //return the rounded value
    return (std::floor(x * 10000 + 0.5)/10000);
}

double Initial::nextY(double centerCoordinate, int neighbour)
{
    double a = (2 * M_PI) / 360; //to transform from degree into rad
    double y;
    y = centerCoordinate + (distanceBetweenCells * cos(a * (60 * neighbour)));
    //return the rounded value
    return (std::floor(y * 10000 + 0.5)/10000);
}

void Initial::makeNeighbours(std::vector<Cell> &cells, int IDCentreCell, int &IDNewCell)
{
    bool isAlreadyExisting = false;
    //for each  neighbour cell of the centreCell
    for (int neighbour = 0; neighbour < 6; ++neighbour) {
        //define the coordinates of the neighbour
        double x = nextX(cells[IDCentreCell].getX(), neighbour);
        double y = nextY(cells[IDCentreCell].getY(), neighbour);

        //create a temporary Instance of this cell
        Cell tempCell(x, y, IDNewCell);

        //check if this neighbour is already an existing cell
        isAlreadyExisting = false;
        for(auto cell : cells) {
            if (cell == tempCell) {
                //declare it as a neighbour
                cells[IDCentreCell].setNeighbour(cell.getID());
                isAlreadyExisting = true;
                break;
            }
        }

        if(isAlreadyExisting==false)
        {
            //Create this new cell
            cells.push_back(tempCell);
            //Declare it as a neighbour
            cells[IDCentreCell].setNeighbour(IDNewCell);
            IDNewCell++;
        }
    }
}

void Initial::printInitialGrid(std::vector<Cell> &cells)
{
    for(auto cell : cells)
    {
        std::cout << cell.getID() << ": " << cell.getX() << "/" << cell.getY() << std::endl;
        std::cout << "In simulation: " << cell.isInSimulation() << std::endl;
    }
}

void Initial::labelCellsInSimulation(std::vector<Cell> &cells, int cellsInSimulation)
{
    //check if cells are within "InSimulation" and label them
    for (int cell = 0; cell < cells.size(); ++cell) {
        if (cells[cell].getID() < cellsInSimulation)
        {
            cells[cell].setInSimulation(true);
        }
        else
        {
            cells[cell].setInSimulation(false);
        }

    }
}



