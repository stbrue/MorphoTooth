//
// Created by Stefanie on 13.08.2018.
//

#include <cmath>
#include "Geometrics.h"

double Geometrics::getCenterDistance2D(Cell cell1, Cell cell2) {
    double x = cell2.getX() - cell1.getX();
    double y = cell2.getY() - cell1.getY();
    double distance = sqrt((x * x) + (y * y));
    return distance;
}

double Geometrics::getCenterDistance3D(Cell cell1, Cell cell2) {
    double x = cell2.getX() - cell1.getX();
    double y = cell2.getY() - cell1.getY();
    double z = cell2.getZ() - cell1.getZ();
    double distance = sqrt((x * x) + (y * y) + (z * z));
    return distance;
}