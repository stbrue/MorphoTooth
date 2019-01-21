#include <iostream>
#include <cmath>
#include "ProgramMorphoTooth.h"
#include "Input.h"


int main(int argc, char *argv[]) {
    std::string simulationNumber = argv[1];

    // Name the files corresponding to the simulationNumber
    char nameInputFile[256];
    sprintf(nameInputFile, "InputFile%s.txt", simulationNumber);
    char nameInputFileTemp[256];
    sprintf(nameInputFileTemp, "InputFileTemp%s.txt", simulationNumber);

    // Read in InputFile.txt and set initial parameters
    Parameters paramsInitial = Input::setParametersInitial(nameInputFile);

    // If no parameter has to be changed, set all values connected with parameterToChange to zero and start one simulation only
    if (paramsInitial.nrOfParametersToChange == 0) {
        std::vector<double> zeroVector = {0, 0, 0, 0};
        paramsInitial.parameterToChangeValues.push_back(zeroVector);

        // Create InputFileTemp.txt with all values for parameterToChange set to zero
        Input::createInputFileTemp(0, paramsInitial, nameInputFileTemp);

        // Set the parameters
        Parameters params = Input::setParameters(nameInputFileTemp);

        // Run the program once
        ProgramMorphoTooth::runProgram(params);
    }

        // else do the simulation with different parameters
    else {
        for (int parameter = 0; parameter < paramsInitial.nrOfParametersToChange; ++parameter) {
            // Create InputFileTemp.txt based on current parameterToChange
            Input::createInputFileTemp(parameter, paramsInitial, nameInputFileTemp);

            // Set the parameters with current parameterToChange
            Parameters params = Input::setParameters(nameInputFileTemp);

            // Run the program with different values of this parameter
            ProgramMorphoTooth::runProgramWithDifferentConditions(params, false);
        }
    }

    return 0;
}