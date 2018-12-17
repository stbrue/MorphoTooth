//
// Created by Stefanie on 17.12.2018.
//

#ifndef MORPHOTOOTH_NOISE_H
#define MORPHOTOOTH_NOISE_H


#include "Parameters.h"

class Noise {
public:
    static void addNoiseToParameter(Parameters &params);

    static double generateNoiseValue(double mean, double sd);

    static void addToParameter(int parameterIndex, Parameters &params, double value);
};


#endif //MORPHOTOOTH_NOISE_H
