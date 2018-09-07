//
// Created by Stefanie on 13.08.2018.
//

#ifndef TOOTHMAKER_GEOMETRICS_H
#define TOOTHMAKER_GEOMETRICS_H


#include "Cell.h"

class Geometrics {
public:

    static double centerDistance2D(Cell cell1, Cell cell2);

    static double centerDistance3D(Cell cell1, Cell cell2);

    static double distance2D(std::vector<double> v1, std::vector<double> v2);

    static double distance3D(std::vector<double> v1, std::vector<double> v2);

    static double vectorNorm3D(std::vector<double> v);

    static std::vector<double> crossProduct(std::vector<double> v1, std::vector<double> v2);

    static double vectorSum(std::vector<double> v);

    static void calculatePerimeterAndArea(std::vector<Cell> &cells, int nrCellsInSimulation);

    static void calculatePerimeter(std::vector<Cell> &cells, int cell, int borderPoint1, int borderPoint2);

    static void calculateCellArea(std::vector<Cell> &cells, int cell, int borderPoint1, int borderPoint2);

    static double centerDistanceToOrigin2D(Cell cell);

    static double centerDistanceToOrigin3D(Cell cell);
};


#endif //TOOTHMAKER_GEOMETRICS_H
