//
// Created by Stefanie on 26.11.2018.
//

#ifndef MORPHOTOOTH_PROGRAMMORPHOTOOTH_H
#define MORPHOTOOTH_PROGRAMMORPHOTOOTH_H

#include "ImplementParams.h"
#include "ModelParams.h"


class ProgramMorphoTooth {
public:
    static void runProgram(ImplementParams &implementParams, ModelParams &modelParams, int repetition);

    static void runProgramWithDifferentConditions(ImplementParams &paramsInitial, std::string nameInputFileTemp);


};


#endif //MORPHOTOOTH_PROGRAMMORPHOTOOTH_H
