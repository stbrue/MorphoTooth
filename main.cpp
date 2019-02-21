#include <iostream>
#include <cmath>
#include <sstream>
#include <Utility.h>
#include "ProgramMorphoTooth.h"
#include "Input.h"


int main() {
    // Arguments read in by command line
    std::string simulationNumber = "01";
    std::string nameInputFileImplement = "ImplementParams01.txt";
    std::string nameInputFileModel = "ModelParams01.txt";

    // Read ModelParams.txt and ImplementParams.txt and set initial values
    ModelParams modelParamsInitial = Input::setModelParamsInitial(nameInputFileModel);
    ImplementParams implementParamsInitial = Input::setImplementParamsInitial(nameInputFileImplement);
    
    // if a parameter has to be changed, calculate how many times the simulation has do be done
    ProgramMorphoTooth::calculateNrOfConditions(implementParamsInitial);        

    // run the program as often as "repetition" (defined by input file) or as often as needed for parameter scanning (nrOfConditions)
    if (implementParamsInitial.nrOfConditions > 1){
        for (int condition = 0; condition < implementParamsInitial.nrOfConditions; ++condition) {
            Utility::resetNonConstantParameters(implementParamsInitial);
            ProgramMorphoTooth::runProgram(implementParamsInitial, modelParamsInitial, condition);
        }
    } else {
        for (int repetition = 0; repetition < implementParamsInitial.repetitions; ++repetition) {
            Utility::resetNonConstantParameters(implementParamsInitial);
            ProgramMorphoTooth::runProgram(implementParamsInitial, modelParamsInitial, repetition);
        }
    }
    return 0;
}