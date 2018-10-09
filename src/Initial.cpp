//
// Created by Stefanie on 30.07.2018.
//

#include "Initial.h"

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include "Cell.h"
#include "Parameters.h"
#include "Geometrics.h"


std::vector<Cell> Initial::makeInitialGrid(Parameters &params) {
    //Calculate the initial amount of cells involved in simulations (that have 6 neighbours)
    params.nrCellsInSimulation = Initial::getNumberOfInSimulationCells(params.initialRadius);

    //Make the first cell
    Cell cell1(0, 0, 1, 0);

    //Vector containing all cells
    std::vector<Cell> cells;

    //Include the first cell
    cells.push_back(cell1);

    //Make the neighbours of this cell and then of all the other cells
    int IDNewCell = 1;
    for (int centreCell = 0; centreCell < params.nrCellsInSimulation; ++centreCell) {
        makeNeighbours(cells, centreCell, IDNewCell);
    }

    //Define for each cell if it is "within simulation" or "in Centre"
    labelNrCellsInSimulation(cells, params);
    labelCellsInCentre(cells, params);  // has to be called after labelNrCellsInSimulation!!

    //reduceNeighboursOutOfSimulation(cells, params.nrCellsInSimulation);       //not needed for this way of implementation

    Geometrics::calculateCellBorders(cells, params.nrCellsInSimulation);

    return cells;
}

/**
 * @brief   Operator overloading to test if two cells are the same (have the same positions)
 * @param   c1  cell1
 * @param   c2  cell2
 * @return  true if the cells have the same position
 */
bool operator==(const Cell &c1, const Cell &c2) {
    return (c1.getX() == c2.getX() && c1.getY() == c2.getY() && c1.getZ() == c2.getZ());
}

int Initial::getTotalNumberOfCells(int initialRadius) {
    int j = 0;
    for (int i = 1; i <= initialRadius; ++i) {
        j += i;
    }
    return (6 * j + 1);
}


int Initial::getNumberOfInSimulationCells(int initialRadius) {
    int j = 0;
    for (int i = 1; i < initialRadius; ++i) {
        j += i;
    }
    return (6 * j + 1);
}


double Initial::nextX(double centerCoordinate, int neighbour) {
    double a = (2 * M_PI) / 360; //to transform from degree into rad
    double x;
    x = centerCoordinate + (distanceBetweenCells * sin(a * (60 * neighbour)));
    //return the rounded value
    return (std::floor(x * 1000000 + 0.5) / 1000000);
}


double Initial::nextY(double centerCoordinate, int neighbour) {
    double a = (2 * M_PI) / 360; //to transform from degree into rad
    double y;
    y = centerCoordinate + (distanceBetweenCells * cos(a * (60 * neighbour)));
    //return the rounded value
    return (std::floor(y * 1000000 + 0.5) / 1000000);
}


void Initial::makeNeighbours(std::vector<Cell> &cells, int IDCentreCell, int &IDNewCell) {
    bool isAlreadyExisting = false;
    //for each  neighbour cell of the centreCell
    for (int neighbour = 0; neighbour < 6; ++neighbour) {
        //define the coordinates of the neighbour
        double x = nextX(cells[IDCentreCell].getX(), neighbour);
        double y = nextY(cells[IDCentreCell].getY(), neighbour);

        //create a temporary Instance of this cell
        Cell tempCell(x, y, 1, IDNewCell);

        //check if this neighbour is already an existing cell
        isAlreadyExisting = false;
        for (auto cell : cells) {
            if (cell == tempCell) {
                //declare it as a neighbour
                cells[IDCentreCell].setNeighbour(cell.getID());
                isAlreadyExisting = true;
                break;
            }
        }

        if (isAlreadyExisting == false) {
            //Create this new cell
            cells.push_back(tempCell);
            //Declare it as a neighbour
            cells[IDCentreCell].setNeighbour(IDNewCell);
            IDNewCell++;
        }
    }
}

void Initial::printInitialGrid(std::vector<Cell> &cells) {
    for (auto cell : cells) {
        std::cout << cell.getID() << ": " << cell.getX() << "/" << cell.getY() << std::endl;
        std::cout << "In simulation: " << cell.isInSimulation() << std::endl;
        std::cout << "In center: " << cell.isInCentre() << std::endl;
    }
}

void Initial::printInitialNeighbours(std::vector<Cell> cells) {
    for (auto cell : cells) {
        std::vector<int> neighbours = cell.getNeighbours();
        for (int neighbour = 0; neighbour < neighbours.size(); ++neighbour) {
            std::cout << neighbours[neighbour] << "  ";
        }
        std::cout << std::endl;
    }
}


void Initial::labelNrCellsInSimulation(std::vector<Cell> &cells, Parameters &params) {
    //for each cell
    for (int cell = 0; cell < cells.size(); ++cell) {
        if (cells[cell].getID() < params.nrCellsInSimulation) {
            cells[cell].setInSimulation(true);
        } else {
            cells[cell].setInSimulation(false);
        }
    }
}


void Initial::labelCellsInCentre(std::vector<Cell> &cells, Parameters &params) {
    int nrCellsNotInCentre = ((params.initialRadius - 1) * 6) + 1;
    int nrCellsInCentre = params.nrCellsInSimulation - nrCellsNotInCentre + 1;
    if (nrCellsInCentre < 7) {
        nrCellsInCentre = 7;
    }
    params.nrCellsInCenter = nrCellsInCentre;

    //change state of "inCentre" for all these cells
    for (int cell = 0; cell < nrCellsInCentre; ++cell) {
        cells[cell].setInCentre(true);
    }
}


void Initial::reduceNeighboursOutOfSimulation(std::vector<Cell> &cells, int nrCellsInSimulation) {
    bool neighbour1 = false;
    bool neighbour2 = false;
    std::vector<int> neighboursToDelete;
    int deletedNeighbours;
    for (int cell = 0; cell < nrCellsInSimulation; ++cell) {
        for (int neighbour = 0; neighbour < (cells[cell].getNeighbours().size() - 1); ++neighbour) {

            //Check if two adjacent neighbours are within simulation
            neighbour1 = isNeighbourInSimulation(cells, cell, neighbour);
            neighbour2 = isNeighbourInSimulation(cells, cell, neighbour + 1);

            //If two adjacent neighbours are not within simulation remember the first one
            if (neighbour1 == false && neighbour2 == false) {
                neighboursToDelete.push_back(neighbour);
            }
        }
        //Delete all the remembered cells
        deletedNeighbours = 0;
        for (auto neighbourToDelete : neighboursToDelete) {
            cells[cell].deleteNeighbour(neighbourToDelete - deletedNeighbours);
            deletedNeighbours++;
        }
        neighboursToDelete.clear();
    }
    //if a cell has two neighbours out of simulation, delete the second
    for (int cell = 7; cell < nrCellsInSimulation; ++cell) {
        neighbour1 = false;
        for (int neighbour = 0; neighbour < cells[cell].getNeighbours().size(); ++neighbour) {
            if (isNeighbourInSimulation(cells, cell, neighbour) == false && neighbour1 == false) {
                neighbour1 = true;
                continue;
            }
            if (isNeighbourInSimulation(cells, cell, neighbour) == false && neighbour1 == true) {
                cells[cell].deleteNeighbour(neighbour);
                break; // it is never the case that a cell has three neighbours out of simulation at this point
            }
        }
    }
}


bool Initial::isNeighbourInSimulation(std::vector<Cell> &cells, int IDCentreCell, int neighbour) {
    int IDOfNeighbour = cells[IDCentreCell].getNeighbours()[neighbour];
    if (cells[IDOfNeighbour].isInSimulation()) {
        return true;
    } else {
        return false;
    }
}



