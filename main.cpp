#include <iostream>
#include "ProgramMorphoTooth.h"
#include "Input.h"


int main() {
    //Make instance of Parameters by reading in the parameters from input file
    Parameters paramsInitial = Input::setParameters();

    //Calculate how many conditions there are
    paramsInitial.nrOfConditions = (paramsInitial.totalPlusMinusScope / paramsInitial.percentageSteps) * 2; // in both directions -> *2

    //Calculate starting condition
    double startingValue = paramsInitial.valueOfParameterToChange - (paramsInitial.valueOfParameterToChange * paramsInitial.totalPlusMinusScope);

    //Calculate change per conditions
    double changePerCondition = paramsInitial.valueOfParameterToChange * paramsInitial.percentageSteps;

    //Set starting conditions
    Input::changeInputFile(paramsInitial, startingValue);

    //Loop that starts the program with different conditions (input parameters)
    for (int condition = 0; condition < paramsInitial.nrOfConditions; ++condition) {
        //Re-read the InputFile
        Parameters params = Input::setParameters();

        // run the program with current conditions
        ProgramMorphoTooth::runProgram(params);

        // change the conditions
        double newValue = ((condition + 1) * changePerCondition) + paramsInitial.valueOfParameterToChange;
        Input::changeInputFile(params, newValue);

    }
    
    return 0;
}