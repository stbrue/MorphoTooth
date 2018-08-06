//
// Created by Stefanie on 06.08.2018.
//

#include <iostream>
#include "Grid.h"
#include "Initial.h"

void Grid::calculateInitialCellBorders(std::vector<Cell> &cells, int cellsInSimulation) {
    for (int centreCell = 0; centreCell < cellsInSimulation; ++centreCell) {
        for (int neighbour1 = 0; neighbour1 < (cells[centreCell].getNeighbours().size() - 1); ++neighbour1) {
            int neighbour2 = neighbour1 + 1;

            Grid::setBorders(cells, centreCell, neighbour1, neighbour2);
        }
        //last and first neighbour
        int neighbour1 = (cells[centreCell].getNeighbours().size() - 1);
        int neighbour2 = 0;

        Grid::setBorders(cells, centreCell, neighbour1, neighbour2);
    }
}

void Grid::setBorders(std::vector<Cell> &cells, int centreCell, int neighbour1, int neighbour2)
{
    int IDn1 = cells[centreCell].getNeighbours()[neighbour1];
    int IDn2 = cells[centreCell].getNeighbours()[neighbour2];

    bool n1InSimulation = Initial::isNeighbourInSimulation(cells, centreCell, neighbour1);
    bool n2InSimulation = Initial::isNeighbourInSimulation(cells, centreCell, neighbour2);

    //if two adjacent neighbours of centreCell are within Simulation
    if (n1InSimulation && n2InSimulation)
    {
        //calculate the midpoint of centreCell and these two neighbours
        cells[centreCell].newBorderPoint('X', ((cells[centreCell].getX() + cells[IDn1].getX() + cells[IDn2].getX()) / 3));
        cells[centreCell].newBorderPoint('Y', ((cells[centreCell].getY() + cells[IDn1].getY() + cells[IDn2].getY()) / 3));
        cells[centreCell].newBorderPoint('Z', ((cells[centreCell].getZ() + cells[IDn1].getZ() + cells[IDn2].getZ()) / 3));
        return;
    }

        //if at least one of the neighbours is within Simulation
    else if (n1InSimulation || n2InSimulation)
    {
        // calculate the midpoint of centreCell and the cell within simulation
        if (n1InSimulation)
        {
            cells[centreCell].newBorderPoint('X', ((cells[centreCell].getX() + cells[IDn1].getX()) / 2));
            cells[centreCell].newBorderPoint('Y', ((cells[centreCell].getY() + cells[IDn1].getY()) / 2));
            cells[centreCell].newBorderPoint('Z', ((cells[centreCell].getZ() + cells[IDn1].getZ()) / 2));
            return;
        }
        else if(n2InSimulation)
        {
            cells[centreCell].newBorderPoint('X', ((cells[centreCell].getX() + cells[IDn2].getX()) / 2));
            cells[centreCell].newBorderPoint('Y', ((cells[centreCell].getY() + cells[IDn2].getY()) / 2));
            cells[centreCell].newBorderPoint('Z', ((cells[centreCell].getZ() + cells[IDn2].getZ()) / 2));
            return;
        }
    }
}


