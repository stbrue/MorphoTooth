#include <iostream>
#include <cmath>
#include "ProgramMorphoTooth.h"
#include "Input.h"


int main() {
    //Make instance of Parameters by reading in the parameters from input file
    //Parameters paramsInitial = Input::setParameters("InputFile.txt");

    //Define the number of parameters to change
    int nrOfParameterToChange = Input::defineNrOfParametersToChange();

    for (int parameter = 0; parameter < nrOfParameterToChange; ++parameter) {
        // Set parameterToChange and valueOfParameterToChange in InputFile.txt
        Input::changeInputFile(parameter);

        // Reset the parameters
        Parameters params = Input::setParameters("InputFile.txt");

        // Check if parameter to change is integer
        //bool parameterToChangeIsInt = Input::isInteger(params.valueOfParameterToChange);

        // Run the program with different values of this parameter
        ProgramMorphoTooth::runProgramWithDifferentConditions(params, false);
    }

    return 0;
}