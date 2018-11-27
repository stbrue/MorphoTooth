//
// Created by Stefanie on 26.11.2018.
//

#ifndef MORPHOTOOTH_PROGRAMMORPHOTOOTH_H
#define MORPHOTOOTH_PROGRAMMORPHOTOOTH_H

#include "Parameters.h"


class ProgramMorphoTooth {
public:
    static void runProgram(Parameters &params);

    static void runProgramWithDifferentConditions(Parameters &paramsInitial, bool parameterToChangeIsInt);
};


#endif //MORPHOTOOTH_PROGRAMMORPHOTOOTH_H
