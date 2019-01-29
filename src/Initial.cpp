//
// Created by Stefanie on 30.07.2018.
//

#include "Initial.h"
#include <cmath>
#include <iostream>
#include "Cell.h"
#include "Parameters.h"
#include "Geometrics.h"
#include "consts.h"


void Initial::makeInitialGrid(Parameters &params, Cell (&cells)[totalNrOfCells]) {
    //Calculate the initial amount of cells involved in simulations (that have 6 neighbours)
    params.nrCellsInSimulation = Initial::getNumberOfInSimulationCells(params.initialRadius);

    //Make the first cell
    Cell cell1;
    cell1.setX(params.firstX);
    cell1.setY(params.firstY);
    cell1.setZ(params.firstZ);
    cell1.setID(firstID);

    //Include the first cell
    cells[first] = cell1;

    //Make the neighbours of this cell and then of all the other cells
    int IDNewCell = 1;
    for (int centreCell = 0; centreCell < params.nrCellsInSimulation; ++centreCell) {
        makeNeighbours(cells, centreCell, IDNewCell, params);
    }

    //Define for each cell if it is "within simulation" or "in Centre"
    labelCellsInSimulation(cells, params);
    labelCellsInCentre(cells, params);  // has to be called after labelCellsInSimulation!!

    Geometrics::calculateCellBorders(cells, params.nrCellsInSimulation);
    Geometrics::setInitialOriginalDistances(cells, params);

    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        cells[cell].resetTempCoordinates();
    }
}

/**
 * @brief   Operator overloading to test if two cells are the same (have the same positions)
 * @param   c1  cell1
 * @param   c2  cell2
 * @return  true if the cells have the same position
 */
bool operator==(const Cell &c1, const Cell &c2) {
    double x1 = std::floor(c1.getX() * 1000 + 0.5) / 1000;
    double x2 = std::floor(c2.getX() * 1000 + 0.5) / 1000;
    double y1 = std::floor(c1.getY() * 1000 + 0.5) / 1000;
    double y2 = std::floor(c2.getY() * 1000 + 0.5) / 1000;
    double z1 = std::floor(c1.getZ() * 1000 + 0.5) / 1000;
    double z2 = std::floor(c2.getZ() * 1000 + 0.5) / 1000;
    return (x1 == x2 && y1 == y2 && z1 == z2);
}

int Initial::getNumberOfInSimulationCells(int initialRadius) {
    int j = 0;
    for (int i = 1; i < initialRadius; ++i) {
        j += i;
    }
    return (initialNrOfNeighbours * j + 1);
}


double Initial::nextX(double centerCoordinate, int neighbour, Parameters &params) {
    double a = (2 * M_PI) / totalDegrees; //to transform from degree into rad
    double x;
    int distanceBetweenCells = 1;
    x = centerCoordinate + (distanceBetweenCells * sin(a * (degrees * neighbour)));
    //return the rounded value
    return (std::floor(x * params.round3 + 0.5) / params.round3);
}


double Initial::nextY(double centerCoordinate, int neighbour, Parameters &params) {
    double a = (2 * M_PI) / totalDegrees; //to transform from degree into rad
    double y;
    int distanceBetweenCells = 1;
    y = centerCoordinate + (distanceBetweenCells * cos(a * (degrees * neighbour)));
    //return the rounded value
    return (std::floor(y * params.round3 + 0.5) / params.round3);
}


void Initial::makeNeighbours(Cell (&cells)[totalNrOfCells], int IDCentreCell, int &IDNewCell, Parameters &params) {
    bool isAlreadyExisting = false;
    //for each  neighbour cell of the centreCell
    for (int neighbour = 0; neighbour < initialNrOfNeighbours; ++neighbour) {
        //define the coordinates of the neighbour
        double x = nextX(cells[IDCentreCell].getX(), neighbour, params);
        double y = nextY(cells[IDCentreCell].getY(), neighbour, params);

        //create a temporary Instance of this cell
        Cell tempCell;
        tempCell.setX(x);
        tempCell.setY(y);
        tempCell.setZ(params.firstZ);
        tempCell.setID(IDNewCell);

        //check if this neighbour is already an existing cell
        isAlreadyExisting = false;
        for (int cell = 0; cell < IDNewCell; ++cell) {
            if (cells[cell] == tempCell) {
                //declare it as a neighbour
                cells[IDCentreCell].addNeighbour(cell);
                isAlreadyExisting = true;
                break;
            }
        }


        if (!isAlreadyExisting) {
            //Create this new cell
            cells[IDNewCell] = tempCell;
            //Declare it as a neighbour
            cells[IDCentreCell].addNeighbour(IDNewCell);
            IDNewCell++;
        }
    }
}

void Initial::labelCellsInSimulation(Cell (&cells)[totalNrOfCells], Parameters &params) {
    //for each cell in the array
    for (int cell = 0; cell < totalNrOfCells; ++cell) {
        if (cell < params.nrCellsInSimulation) {
            // Label cells within simulation
            cells[cell].setInSimulation(true);
        } else { // Give all out-of-simulation cells an ID higher than "totalNrOfCells"
            cells[cell].setID(cells[cell].getID() + totalNrOfCells);
        }

        //Change the ID of out-of-simulation cells also in neighbour arrays
        int *neighbours = cells[cell].getNeighbours(); // a pointer to array with neighbours

        for (int neighbour = 0; neighbour < initialNrOfNeighbours; ++neighbour) {
            int neighbourID = neighbours[neighbour];
            if (neighbourID >= params.nrCellsInSimulation) {
                cells[cell].replaceNeighbour(neighbourID, neighbourID + totalNrOfCells);
            }
        }
    }
}


void Initial::labelCellsInCentre(Cell (&cells)[totalNrOfCells], Parameters &params) {
    int nrCellsNotInCentre = ((params.initialRadius - 1) * initialNrOfNeighbours) + 1;
    int nrCellsInCentre = params.nrCellsInSimulation - nrCellsNotInCentre + 1;

    for (int cell = 0; cell < nrCellsInCentre; ++cell) {
        cells[cell].setInCentre(true);
    }
}




