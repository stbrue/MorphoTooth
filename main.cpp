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
    std::string nameInputFileTempImplement = "TempImplementParams01.txt";

    // Read ModelParams.txt and set initial values
    ModelParams modelParamsInitial = Input::setModelParamsInitial(nameInputFileModel);

    // Read ImplementParams.txt and set initial values
    ImplementParams implementParamsInitial = Input::setImplementParamsInitial(nameInputFileImplement);

    // Run the program as often as declared in the InputFile with "repetitions"
    for (int repetition = 0; repetition < implementParamsInitial.repetitions; ++repetition) {
        Utility::resetNonConstantParameters(implementParamsInitial);
        ProgramMorphoTooth::runProgram(implementParamsInitial, modelParamsInitial, repetition);
    }

    /*
    // If no parameter has to be changed, set all values connected with parameterToChange to zero and start the simulation with the same parameters
    if (implementParamsInitial.nrOfParametersToChange == 0) {
        std::vector<double> zeroVector = {0, 0, 0, 0};
        implementParamsInitial.parameterToChangeValues.push_back(zeroVector);

        // Create TempImplementParams01.txt with all values for parameterToChange set to zero
        Input::createInputFileTemp(0, implementParamsInitial, nameInputFileTempImplement);

        // Set the parameters
        ImplementParams implementParams = Input::setImplementParameters(nameInputFileTempImplement);

        // Run the program as often as declared in the InputFile with "repetitions"
        for (int repetition = 0; repetition < params.repetitions; ++repetition) {
            Utility::resetNonConstantParameters(params);
            ProgramMorphoTooth::runProgram(params, repetition);
        }
    }

        // else do the simulation with different parameters
    else {
        for (int parameter = 0; parameter < paramsInitial.nrOfParametersToChange; ++parameter) {
            // Create InputFileTemp.txt based on current parameterToChange
            Input::createInputFileTemp(parameter, paramsInitial, nameInputFileTemp);

            // Set the parameters with current parameterToChange
            ImplementParams params = Input::setParameters(nameInputFileTemp);

            // Run the program with different values of this parameter
            ProgramMorphoTooth::runProgramWithDifferentConditions(params, nameInputFileTemp);
        }
    }
     */

    return 0;
}