//
// Created by Stefanie on 23.01.2019.
//

#include "Utility.h"

void Utility::resetNonConstantParameters(Parameters &params) {

    params.error = false;
    params.cellDivisionCount = 0;
    params.currentIteration = 0;
}
