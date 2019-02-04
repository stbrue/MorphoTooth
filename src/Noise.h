//
// Created by Stefanie on 17.12.2018.
//

#ifndef MORPHOTOOTH_NOISE_H
#define MORPHOTOOTH_NOISE_H


#include "Parameters.h"

class Noise {
public:
    static void setNoiseParameter(Parameters params, Parameters &noiseParams);

    static double generateNoiseValue(double mean, double sd);

    static void addToParameter(int parameterIndex, Parameters &params, double value);

    static void updateParams(Parameters &noiseParams, Parameters &params);

};


#endif //MORPHOTOOTH_NOISE_H
