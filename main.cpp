#include <iostream>
#include <cmath>
#include "ProgramMorphoTooth.h"
#include "Input.h"


int main() {
    //Make instance of Parameters by reading in the parameters from input file
    Parameters paramsInitial = Input::setParameters("InputFile.txt");

    // Check if parameter to change is integer
    bool parameterToChangeIsInt = Input::isInteger(paramsInitial.valueOfParameterToChange);

    ProgramMorphoTooth::runProgramWithDifferentConditions(paramsInitial, parameterToChangeIsInt);

    return 0;
}