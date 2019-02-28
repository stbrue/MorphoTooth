//
// Created by Stefanie on 23.01.2019.
//

#ifndef MORPHOTOOTH_UTILITY_H
#define MORPHOTOOTH_UTILITY_H


#include "ImplementParams.h"
#include "Cell.h"
#include <string>

class Utility {

public:
    static void resetNonConstantParameters(ImplementParams &params);

    static void trimString(std::string &str);

    static void leftTrim(std::string &str);

    static void rightTrim(std::string &str);

    static std::string doubleToString(double value);

    static bool NanIsPresent(double x, double y, double z);

    static bool errorTesting(Cell cells[totalNrOfCells], ImplementParams &params);

    static int endOfSimulation(ImplementParams &params, int iterationStep, int oldSuccess);

    static void checkForFullNeighbourVector(Cell cells[totalNrOfCells], ImplementParams &params, int cellID);

};


#endif //MORPHOTOOTH_UTILITY_H
