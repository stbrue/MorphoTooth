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
    static void doNoise(Cell (&cells)[totalNrOfCells], ImplementParams params, ImplementParams &noiseParams);

    static double generateNoiseValue(ImplementParams &params, double mean, double sd);

    static void addToParameter(int parameterIndex, ImplementParams &params, double value);

    static void updateParams(ImplementParams &noiseParams, ImplementParams &params);

};


#endif //MORPHOTOOTH_NOISE_H
