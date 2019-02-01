//
// Created by Stefanie on 17.12.2018.
//

#ifndef MORPHOTOOTH_PRINT_H
#define MORPHOTOOTH_PRINT_H


#include "Parameters.h"

class Print {
public:
    static void printStartOfSimulation(Parameters params);

    static void printParameterToChange(Parameters params);

    static void printParameterWithNoise(Parameters params);

    static void printEndOfSimulation(int success);

};


#endif //MORPHOTOOTH_PRINT_H
