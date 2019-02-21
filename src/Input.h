//
// Created by Stefanie on 07.09.2018.
//

#ifndef MORPHOTOOTH_INPUT_H
#define MORPHOTOOTH_INPUT_H

#include "ImplementParams.h"
#include "ModelParams.h"
#include<string>


/**
 * @brief   Reading and assignment of the input Parameters
 */
class Input {
public:

    static ImplementParams setParametersInitial(std::string InputFileName);

    static ImplementParams setParameters(std::string InputFileName);

    static void changeInputFileTemp(ImplementParams params, double newValue, std::string nameInputFileTemp);

    static void changeInputFile(int nrOfParameter);

    //static bool isInteger(double value);

    //static bool isInteger(int value);

    //static void defineParameterToChange(ImplementParams &paramsInitial);

    static int defineNrOfParametersToChange();

    static double getParameterAffectedByNoise(ImplementParams &params);

    static void createInputFileTemp(int parameter, ImplementParams params, std::string fileName);

    static ModelParams setModelParamsInitial(std::string InputFileName);

    static ImplementParams setImplementParamsInitial(std::string InputFileName);


};


#endif //MORPHOTOOTH_INPUT_H
