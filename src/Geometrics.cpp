//
// Created by Stefanie on 13.08.2018.
//

#include <cmath>
#include <iostream>
#include "Geometrics.h"
#include "Parameters.h"
#include "consts.h"

double Geometrics::squareCenterDistance3D(Cell cell1, Cell cell2) {
    double dx = cell2.getX() - cell1.getX();
    double dy = cell2.getY() - cell1.getY();
    double dz = cell2.getZ() - cell1.getZ();
    double distance = (dx * dx) + (dy * dy) + (dz * dz);
    return distance;
}

double Geometrics::centerDistance2D(Cell cell1, Cell cell2) {
    double x = cell2.getX() - cell1.getX();
    double y = cell2.getY() - cell1.getY();
    double distance = sqrt((x * x) + (y * y));
    return distance;
}

double Geometrics::centerDistance3D(Cell cell1, Cell cell2) {
    double x = cell2.getX() - cell1.getX();
    double y = cell2.getY() - cell1.getY();
    double z = cell2.getZ() - cell1.getZ();
    double distance = sqrt((x * x) + (y * y) + (z * z));
    return distance;
}

double Geometrics::centerDistanceToOrigin2D(Cell cell) {
    double x = cell.getX();
    double y = cell.getY();
    double distance = sqrt(x * x + y * y);
    return distance;
}

double Geometrics::centerDistanceToOrigin3D(Cell cell) {
    double x = cell.getX();
    double y = cell.getY();
    double z = cell.getZ();
    double distance = sqrt(x * x + y * y + z * z);
    return distance;
}

double Geometrics::distance2D(std::vector<double> v1, std::vector<double> v2) {
    double dx = v2[X] - v1[X];
    double dy = v2[Y] - v1[Y];
    double distance = sqrt((dx * dx) + (dy * dy));
    return distance;
}

double Geometrics::distance3D(std::vector<double> v1, std::vector<double> v2) {
    double dx = v2[X] - v1[X];
    double dy = v2[Y] - v1[Y];
    double dz = v2[Z] - v1[Z];
    double distance = sqrt((dx * dx) + (dy * dy) + (dz * dz));
    return distance;
}

double Geometrics::vectorNorm3D(std::vector<double> v) {
    double norm = sqrt((v[X] * v[X]) + (v[Y] * v[Y]) + (v[Z] * v[Z]));
    return norm;
}

double Geometrics::vectorNorm2D(std::vector<double> v) {
    double norm = sqrt((v[X] * v[X]) + (v[Y] * v[Y]));
    return norm;
}

std::vector<double> Geometrics::crossProduct(std::vector<double> v1, std::vector<double> v2) {
    double x = (v1[Y] * v2[Z]) - (v1[Z] * v2[Y]);
    double y = (v1[Z] * v2[X]) - (v1[X] * v2[Z]);
    double z = (v1[X] * v2[Y]) - (v1[Y] * v2[X]);
    std::vector<double> product;
    product.push_back(x);
    product.push_back(y);
    product.push_back(z);
    return product;
}

double Geometrics::vectorSum(std::vector<double> v) {
    double sum = 0;
    for (auto element : v) {
        sum += element;
    }
    return sum;
}

void Geometrics::calculatePerimeterAndArea(Cell (&cells)[maxNrOfCells], Parameters &params) {

    //Perimeter: distance between two adjacent border points
    //Area: polygon consisting of triangles. Each triangle is made up by 2 adjacent borderpoints and the center cell
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        //First of all, delete all perimeter and area parts
        cells[cell].deletePerimeterParts();
        cells[cell].deleteAreaParts();

        //Now calculate the new perimeter and area parts
        //Last and first neighbour
        int borderPoint1 = (cells[cell].getBorderPoints().size() - 1);
        int borderPoint2 = 0;
        calculatePerimeterParts(cells, cell, borderPoint1, borderPoint2);
        calculateCellAreaParts(cells, cell, borderPoint1, borderPoint2);

        //All other neighbour pairs
        for (int borderPoint1 = 0; borderPoint1 < (cells[cell].getBorderPoints().size() - 1); ++borderPoint1) {
            int borderPoint2 = borderPoint1 + 1;
            //Perimeter
            calculatePerimeterParts(cells, cell, borderPoint1, borderPoint2);
            //Cell Area
            calculateCellAreaParts(cells, cell, borderPoint1, borderPoint2);
        }

        //Do the same for the margin (perimeter and area), if the cell is at the tissue border (=has at margin points)
        double margin = 0;
        double marginArea = 0;
        if (cells[cell].getMarginPoints().size() == 2) {
            margin = Geometrics::calculateMargin(cells[cell].getMarginPoints());
            cells[cell].setMargin(margin);
            marginArea = Geometrics::calculateMarginArea(cells, cell);
            cells[cell].setMarginArea(marginArea);
        } else if (cells[cell].getMarginPoints().size() == 1) {
            std::cout << "There is only one margin point" << std::endl;
            params.error = true;
        } else if (cells[cell].getMarginPoints().size() > 2) {
            std::cout << "There are more than two margin points" << std::endl;
            params.error = true;
        }

        //Sum them up to get total perimeter and total area
        double perimeter = Geometrics::vectorSum(cells[cell].getPerimeterParts()) + margin;
        cells[cell].setPerimeter(perimeter);
        double cellArea = Geometrics::vectorSum(cells[cell].getAreaParts()) + marginArea;
        cells[cell].setCellArea(cellArea);
    }
}

void Geometrics::calculatePerimeterParts(Cell (&cells)[maxNrOfCells], int cell, int borderPoint1, int borderPoint2) {
    double z1 = cells[cell].getBorderPoints()[borderPoint1][Z];
    double z2 = cells[cell].getBorderPoints()[borderPoint2][Z];
    // if one of the border Points is inexistent (=0), set the perimeter part to 0 (marker and placeholder)
    if (z1 == 0 || z2 == 0) {
        cells[cell].newPerimeterPart(0);
        return;
    }
    double dx = cells[cell].getBorderPoints()[borderPoint2][X] - cells[cell].getBorderPoints()[borderPoint1][X];
    double dy = cells[cell].getBorderPoints()[borderPoint2][Y] - cells[cell].getBorderPoints()[borderPoint1][Y];
    double dz = cells[cell].getBorderPoints()[borderPoint2][Z] - cells[cell].getBorderPoints()[borderPoint1][Z];
    std::vector<double> borderToBorder = {dx, dy, dz};
    double perimeterPart = Geometrics::vectorNorm3D(borderToBorder);
    cells[cell].newPerimeterPart(perimeterPart);
}

void Geometrics::calculateCellAreaParts(Cell (&cells)[maxNrOfCells], int cell, int borderPoint1, int borderPoint2) {
    double z1 = cells[cell].getBorderPoints()[borderPoint1][Z];
    double z2 = cells[cell].getBorderPoints()[borderPoint2][Z];

    // if one of the border Points is inexistent (=0), set the area part to 0 (marker and placeholder)
    if (z1 == 0 || z2 == 0) {
        cells[cell].newAreaPart(0);
        return;
    }

    double dx1 = cells[cell].getBorderPoints()[borderPoint1][X] - cells[cell].getX();
    double dx2 = cells[cell].getBorderPoints()[borderPoint2][X] - cells[cell].getX();
    double dy1 = cells[cell].getBorderPoints()[borderPoint1][Y] - cells[cell].getY();
    double dy2 = cells[cell].getBorderPoints()[borderPoint2][Y] - cells[cell].getY();
    double dz1 = cells[cell].getBorderPoints()[borderPoint1][Z] - cells[cell].getZ();
    double dz2 = cells[cell].getBorderPoints()[borderPoint2][Z] - cells[cell].getZ();

    std::vector<double> cellToBorder1 = {dx1, dy1, dz1};
    std::vector<double> cellToBorder2 = {dx2, dy2, dz2};
    std::vector<double> crossProduct = Geometrics::crossProduct(cellToBorder1, cellToBorder2);
    double areaPart = half * Geometrics::vectorNorm3D(crossProduct); // *0.5 because we want the triangle
    cells[cell].newAreaPart(areaPart);
}

double Geometrics::calculateMargin(std::vector<std::vector<double>> marginPoints) {
    double dx = marginPoints[first][X] - marginPoints[second][X];
    double dy = marginPoints[first][Y] - marginPoints[second][Y];
    double dz = marginPoints[first][Z] - marginPoints[second][Z];
    std::vector<double> marginPointToMarginPoint = {dx, dy, dz};
    double margin = Geometrics::vectorNorm3D(marginPointToMarginPoint);
    return margin;
}

double
Geometrics::calculateMarginArea(Cell (&cells)[maxNrOfCells], int cell) {
    double dx1 = cells[cell].getMarginPoints()[first][X] - cells[cell].getX();
    double dx2 = cells[cell].getMarginPoints()[second][X] - cells[cell].getX();
    double dy1 = cells[cell].getMarginPoints()[first][Y] - cells[cell].getY();
    double dy2 = cells[cell].getMarginPoints()[second][Y] - cells[cell].getY();
    double dz1 = cells[cell].getMarginPoints()[first][Z] - cells[cell].getZ();
    double dz2 = cells[cell].getMarginPoints()[second][Z] - cells[cell].getZ();

    std::vector<double> cellToMarginPoint1 = {dx1, dy1, dz1};
    std::vector<double> cellToMarginPoint2 = {dx2, dy2, dz2};
    std::vector<double> crossProduct = Geometrics::crossProduct(cellToMarginPoint1, cellToMarginPoint2);
    double marginArea = half * Geometrics::vectorNorm3D(crossProduct); // *0.5 because we want the triangle
    return marginArea;
}

void Geometrics::calculateCellBorders(Cell (&cells)[maxNrOfCells], int nrCellsInSimulation) {
    for (int centreCell = 0; centreCell < nrCellsInSimulation; ++centreCell) {
        // first of all delete all the border points and margin points
        cells[centreCell].deleteBorderPoints();
        cells[centreCell].deleteMarginPoints();

        //Now calculate the new border points
        //last and first neighbour
        int neighbour1 = cells[centreCell].getNrOfNeighbours() - 1;
        int neighbour2 = 0;

        Geometrics::setBorders(cells, centreCell, neighbour1, neighbour2);

        //all other neighbour pairs
        for (int neighbour1 = 0; neighbour1 < (cells[centreCell].getNrOfNeighbours() - 1); ++neighbour1) {
            int neighbour2 = neighbour1 + 1;

            Geometrics::setBorders(cells, centreCell, neighbour1, neighbour2);
        }
    }
}


void Geometrics::setBorders(Cell (&cells)[maxNrOfCells], int centreCell, int neighbour1, int neighbour2) {
    // IDs of the neighbours
    int IDn1 = cells[centreCell].getNeighbours()[neighbour1];
    int IDn2 = cells[centreCell].getNeighbours()[neighbour2];

    //if both neighbours are in simulation, calculate the midpoint of centreCell and these two neighbours
    if (IDn1 < maxNrOfCells && IDn2 < maxNrOfCells) {
        double nrOfPoints = 3;
        double x = (cells[centreCell].getX() + cells[IDn1].getX() + cells[IDn2].getX()) / nrOfPoints;
        double y = (cells[centreCell].getY() + cells[IDn1].getY() + cells[IDn2].getY()) / nrOfPoints;
        double z = (cells[centreCell].getZ() + cells[IDn1].getZ() + cells[IDn2].getZ()) / nrOfPoints;
        cells[centreCell].newBorderPoint(x, y, z);
        return;
    }

    //if no neighbour is in simulation, set the border point to 0 (as a marker and placeholder)
    if (IDn1 > maxNrOfCells && IDn2 > maxNrOfCells) {
        cells[centreCell].newBorderPoint(0, 0, 0);
        return;
    }

    //if only the first neighbour is in simulation, take the point between the center cell and the first neighbour
    if (IDn1 < maxNrOfCells && IDn2 > maxNrOfCells) {
        double nrOfPoints = 2;
        double x = (cells[centreCell].getX() + cells[IDn1].getX()) / nrOfPoints;
        double y = (cells[centreCell].getY() + cells[IDn1].getY()) / nrOfPoints;
        double z = (cells[centreCell].getZ() + cells[IDn1].getZ()) / nrOfPoints;
        cells[centreCell].newBorderPoint(x, y, z);
        // set this point as a margin point
        cells[centreCell].newMarginPoint(x, y, z);
        return;
    }

    //if only the second neighbour is in simulation, take the point between the center cell and the second neighbour
    if (IDn1 > maxNrOfCells && IDn2 < maxNrOfCells) {
        double nrOfPoints = 2;
        double x = (cells[centreCell].getX() + cells[IDn2].getX()) / nrOfPoints;
        double y = (cells[centreCell].getY() + cells[IDn2].getY()) / nrOfPoints;
        double z = (cells[centreCell].getZ() + cells[IDn2].getZ()) / nrOfPoints;
        cells[centreCell].newBorderPoint(x, y, z);
        // set this point as a margin point
        cells[centreCell].newMarginPoint(x, y, z);
        return;
    }
}

void Geometrics::setInitialOriginalDistances(Cell (&cells)[maxNrOfCells], Parameters &params) {
    double initialDistance = 1;
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {

        for (int neighbour = 0; neighbour < initialNrOfNeighbours; ++neighbour) {
            cells[cell].addOriginalDistance(initialDistance, neighbour);
        }
    }
}