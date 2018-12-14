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

    static Parameters setParameters(std::string InputFileName);

    static void changeInputFileTemp(Parameters params, double newValue);

    static void changeInputFile(int nrOfParameter);

    //static bool isInteger(double value);

    //static bool isInteger(int value);

    //static void defineParameterToChange(Parameters &paramsInitial);

    static int defineNrOfParametersToChange();


};


#endif //MORPHOTOOTH_INPUT_H
