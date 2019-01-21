//
// Created by Stefanie on 07.09.2018.
//

#ifndef MORPHOTOOTH_INPUT_H
#define MORPHOTOOTH_INPUT_H

#include "Parameters.h"
#include<string>


/**
 * @brief   Reading and assignment of the input Parameters
 */
class Input {
public:

    static Parameters setParametersInitial(std::string InputFileName);

    static Parameters setParameters(std::string InputFileName);

    static void changeInputFileTemp(Parameters params, double newValue, std::string nameInputFileTemp);

    static void changeInputFile(int nrOfParameter);

    //static bool isInteger(double value);

    //static bool isInteger(int value);

    //static void defineParameterToChange(Parameters &paramsInitial);

    static int defineNrOfParametersToChange();

    static double getParameterAffectedByNoise(Parameters &params);

    static std::string doubleToString(double value);

    static void createInputFileTemp(int parameter, Parameters params, std::string fileName);


};


#endif //MORPHOTOOTH_INPUT_H
