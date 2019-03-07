//
// Created by Stefanie on 17.12.2018.
//

#ifndef MORPHOTOOTH_PRINT_H
#define MORPHOTOOTH_PRINT_H


#include "ImplementParams.h"

class Print {
public:
    static void printStartOfSimulation(ImplementParams params, int repetition);

    static void printParameterToChange(ImplementParams params);

    static void printParameterWithNoise(ImplementParams params);

    static void printEndOfSimulation();

    static void printSimulationStatus(ImplementParams &params);

};


#endif //MORPHOTOOTH_PRINT_H
