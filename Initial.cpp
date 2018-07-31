//
// Created by Stefanie on 30.07.2018.
//

#include "Initial.h"
#define _USE_MATH_DEFINES
#include <math.h>

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

void Initial::makeInitialGrid(Cell cell1)
{
    double a = (2 * M_PI) / 360; //to transform from degree into rad
}

double Initial::nextX(double previousX)
{
    double x;
    for (int angle = 0; angle < 300; angle += 60) {
        x = previousX + sin(a * angle);
    }
}
