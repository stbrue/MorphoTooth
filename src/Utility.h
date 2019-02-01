//
// Created by Stefanie on 23.01.2019.
//

#ifndef MORPHOTOOTH_UTILITY_H
#define MORPHOTOOTH_UTILITY_H


#include "Parameters.h"
#include "Cell.h"
#include <string>

class Utility {

public:
    static void resetNonConstantParameters(Parameters &params);

    static void trimString(std::string &str);

    static void leftTrim(std::string &str);

    static void rightTrim(std::string &str);

    static std::string doubleToString(double value);

    static bool NanIsPresent(double x, double y, double z);

    static bool errorTesting(Cell cells[totalNrOfCells], Parameters &params);

    static int endOfSimulation(Parameters &params, int iterationStep);
};


#endif //MORPHOTOOTH_UTILITY_H
