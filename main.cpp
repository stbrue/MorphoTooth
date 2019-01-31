#include <iostream>
#include <cmath>
#include <sstream>
#include <Utility.h>
#include "ProgramMorphoTooth.h"
#include "Input.h"


int main() {
    // Arguments read in by command line
    std::string simulationNumber = "01";
    std::string nameInputFile = "InputFile01.txt";
    std::string nameInputFileTemp = "InputFileTemp01.txt";

    // Read InputFile.txt and set initial parameters
    Parameters paramsInitial = Input::setParametersInitial(nameInputFile);

    // If no parameter has to be changed, set all values connected with parameterToChange to zero and start the simulation with the same parameters
    if (paramsInitial.nrOfParametersToChange == 0) {
        std::vector<double> zeroVector = {0, 0, 0, 0};
        paramsInitial.parameterToChangeValues.push_back(zeroVector);

        // Create InputFileTemp.txt with all values for parameterToChange set to zero
        Input::createInputFileTemp(0, paramsInitial, nameInputFileTemp);

        // Set the parameters
        Parameters params = Input::setParameters(nameInputFileTemp);

        // Run the program as often as declared in the InputFile with "repetitions"
        for (int repetition = 0; repetition < params.repetitions; ++repetition) {
            Utility::resetNonConstantParameters(params);
            ProgramMorphoTooth::runProgram(params);
        }
    }

        // else do the simulation with different parameters
    else {
        for (int parameter = 0; parameter < paramsInitial.nrOfParametersToChange; ++parameter) {
            // Create InputFileTemp.txt based on current parameterToChange
            Input::createInputFileTemp(parameter, paramsInitial, nameInputFileTemp);

            // Set the parameters with current parameterToChange
            Parameters params = Input::setParameters(nameInputFileTemp);

            // Run the program with different values of this parameter
            ProgramMorphoTooth::runProgramWithDifferentConditions(params, nameInputFileTemp);
        }
    }

    return 0;
}