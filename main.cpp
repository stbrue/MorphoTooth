#include <iostream>
#include <cmath>
#include "ProgramMorphoTooth.h"
#include "Input.h"


int main() {

    // Read in InputFile.txt and set initial parameters
    Parameters paramsInitial = Input::setParametersInitial("InputFile.txt");


    // If no parameter has to be changed, set all values connected with parameterToChange to zero and start one simulation only
    if (paramsInitial.nrOfParametersToChange == 0) {
        std::vector<double> zeroVector = {0, 0, 0, 0};
        paramsInitial.parameterToChangeValues.push_back(zeroVector);

        // Create InputFileTemp.txt with all values for parameterToChange set to zero
        Input::createInputFileTemp(0, paramsInitial);

        // Set the parameters
        Parameters params = Input::setParameters("InputFileTemp.txt");

        // Run the program once
        ProgramMorphoTooth::runProgram(params);
    }

        // else do the simulation with different parameters
    else {
        for (int parameter = 0; parameter < paramsInitial.nrOfParametersToChange; ++parameter) {
            // Create InputFileTemp.txt based on current parameterToChange
            Input::createInputFileTemp(parameter, paramsInitial);

            // Set the parameters with current parameterToChange
            Parameters params = Input::setParameters("InputFileTemp.txt");

            // Run the program with different values of this parameter
            ProgramMorphoTooth::runProgramWithDifferentConditions(params, false);
        }
    }

    return 0;
}