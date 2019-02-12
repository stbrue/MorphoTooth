//
// Created by Stefanie on 17.12.2018.
//

#ifndef MORPHOTOOTH_PRINT_H
#define MORPHOTOOTH_PRINT_H


#include "Parameters.h"

class Print {
public:
    static void printStartOfSimulation(Parameters params, int repetition);

    static void printParameterToChange(Parameters params);

    static void printParameterWithNoise(Parameters params);

    static void printEndOfSimulation();

};


#endif //MORPHOTOOTH_PRINT_H
