//
// Created by Stefanie on 17.12.2018.
//

#ifndef MORPHOTOOTH_NOISE_H
#define MORPHOTOOTH_NOISE_H


#include "ImplementParams.h"
#include "Cell.h"
#include "consts.h"

class Noise {
public:
    static void doNoise(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams);

    static double generateNoiseValue(double mean, double sd, unsigned int seed);


};


#endif //MORPHOTOOTH_NOISE_H
