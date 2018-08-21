//
// Created by Stefanie on 13.08.2018.
//

#include <cmath>
#include "Geometrics.h"

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
    double dx = v2[0] - v1[0];
    double dy = v2[1] - v1[1];
    double distance = sqrt((dx * dx) + (dy * dy));
    return distance;
}

double Geometrics::distance3D(std::vector<double> v1, std::vector<double> v2) {
    double dx = v2[0] - v1[0];
    double dy = v2[1] - v1[1];
    double dz = v2[2] - v1[2];
    double distance = sqrt((dx * dx) + (dy * dy) + (dz * dz));
    return distance;
}

double Geometrics::vectorNorm3D(std::vector<double> v) {
    double norm = sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
    return norm;
}

std::vector<double> Geometrics::crossProduct(std::vector<double> v1, std::vector<double> v2) {
    double x = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    double y = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    double z = (v1[0] * v2[1]) - (v1[1] * v2[0]);
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

void Geometrics::calculatePerimeterAndArea(std::vector<Cell> &cells, int cellsInSimulation) {

    for (int cell = 0; cell < cellsInSimulation; ++cell) {

        //Last and first neighbour
        int borderPoint1 = (cells[cell].getBorderPointsX().size() - 1);
        int borderPoint2 = 0;
        calculatePerimeter(cells, cell, borderPoint1, borderPoint2);
        calculateCellArea(cells, cell, borderPoint1, borderPoint2);

        //All other neighbour pairs
        for (int borderPoint1 = 0; borderPoint1 < (cells[cell].getBorderPointsX().size() - 1); ++borderPoint1) {
            int borderPoint2 = borderPoint1 + 1;
            //Perimeter
            calculatePerimeter(cells, cell, borderPoint1, borderPoint2);
            //Cell Area
            calculateCellArea(cells, cell, borderPoint1, borderPoint2);
        }

        double perimeter = Geometrics::vectorSum(cells[cell].getPerimeterParts());
        cells[cell].setPerimeter(perimeter);
        double cellArea = Geometrics::vectorSum(cells[cell].getAreaParts());
        cells[cell].setCellArea(cellArea);
    }
}

void Geometrics::calculatePerimeter(std::vector<Cell> &cells, int cell, int borderPoint1, int borderPoint2) {
    double x = cells[cell].getBorderPointsX()[borderPoint2] - cells[cell].getBorderPointsX()[borderPoint1];
    double y = cells[cell].getBorderPointsY()[borderPoint2] - cells[cell].getBorderPointsY()[borderPoint1];
    double z = cells[cell].getBorderPointsZ()[borderPoint2] - cells[cell].getBorderPointsZ()[borderPoint1];
    std::vector<double> borderToBorder = {x, y, z};
    double perimeterPart = Geometrics::vectorNorm3D(borderToBorder);
    cells[cell].newPerimeterPart(perimeterPart);
}

void Geometrics::calculateCellArea(std::vector<Cell> &cells, int cell, int borderPoint1, int borderPoint2) {
    double x1 = cells[cell].getBorderPointsX()[borderPoint1] - cells[cell].getX();
    double x2 = cells[cell].getBorderPointsX()[borderPoint2] - cells[cell].getX();
    double y1 = cells[cell].getBorderPointsY()[borderPoint1] - cells[cell].getY();
    double y2 = cells[cell].getBorderPointsY()[borderPoint2] - cells[cell].getY();
    double z1 = cells[cell].getBorderPointsZ()[borderPoint1] - cells[cell].getZ();
    double z2 = cells[cell].getBorderPointsZ()[borderPoint2] - cells[cell].getZ();
    std::vector<double> cellToBorder1 = {x1, y1, z1};
    std::vector<double> cellToBorder2 = {x2, y2, z2};
    std::vector<double> crossProduct = Geometrics::crossProduct(cellToBorder1, cellToBorder2);
    double areaPart = 0.5 * Geometrics::vectorNorm3D(crossProduct); // *0.5 because we want the triangle
    cells[cell].newAreaPart(areaPart);
}