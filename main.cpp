#include <iostream>
#include <cmath>
#include <sstream>
#include <Utility.h>
#include <ctime>
#include "ProgramMorphoTooth.h"
#include "Input.h"


int main(int argc, char *argv[]) {
    std::clock_t start;
    double duration;
    start = std::clock();

    // Arguments read in by command line
    const char *s1 = argv[1];
    std::string simulationNumber = s1;

    const char *s2 = argv[2];
    std::string nameInputFile = s2;

    // Read ModelParams.txt and ImplementParams.txt and set initial values
    ModelParams modelParamsInitial = Input::setModelParamsInitial(nameInputFile);
    ImplementParams implementParamsInitial = Input::setImplementParamsInitial(nameInputFile);

    // if a parameter has to be changed, calculate how many times the simulation has do be done
    ProgramMorphoTooth::calculateNrOfConditions(implementParamsInitial);

    // run the program as often as "repetition" (defined by input file) or as often as needed for parameter scanning (nrOfConditions)
    if (implementParamsInitial.nrOfConditions > 1) {
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

    duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;

    std::cout << "duration: " << duration << std::endl;
    return 0;
}