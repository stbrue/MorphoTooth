//
// Created by Stefanie on 26.11.2018.
//

#ifndef MORPHOTOOTH_PROGRAMMORPHOTOOTH_H
#define MORPHOTOOTH_PROGRAMMORPHOTOOTH_H

#include "ImplementParams.h"
#include "ModelParams.h"
#include "Cell.h"


class ProgramMorphoTooth {
public:
    static void runProgram(ImplementParams &implementParams, ModelParams &modelParams, int repetition);

    static void changeModelParameter(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams, int condition);

    static void calculateNrOfConditions(ImplementParams &implementParams);


};


#endif //MORPHOTOOTH_PROGRAMMORPHOTOOTH_H
