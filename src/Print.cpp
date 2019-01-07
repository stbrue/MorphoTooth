//
// Created by Stefanie on 17.12.2018.
//

#include <iostream>
#include "Print.h"

void Print::printStartOfSimulation(Parameters params) {
    std::cout << "##################################################################################" << std::endl;
    std::cout << "##################################################################################" << std::endl;
    std::cout << "## Simulation has started                                                       ##" << std::endl;
    std::cout << "##################################################################################" << std::endl;

    Print::printParameterToChange(params);
    Print::printParameterWithNoise(params);
}

void Print::printParameterToChange(Parameters params) {
    // Print only if the parameter gets changed
    if (params.totalPlusMinusScope > 0) {
        std::cout << "###########################################################" << std::endl;
        std::cout << "# Parameter to change " << params.parameterToChange << ": "
                  << params.valueOfParameterToChange << " #" << std::endl;
        std::cout << "###########################################################" << std::endl;
        std::cout.flush();
    }
}

void Print::printParameterWithNoise(Parameters params) {
    // Print only if a parameter has noise
    if (params.parameterWithNoise > 0) {
        std::cout << "#############################################################" << std::endl;
        std::cout << "# Parameter with Noise: " << params.parameterWithNoise << " #" << std::endl;
        std::cout << "#############################################################" << std::endl;
    }
}

void Print::printEndOfSimulation() {
    std::cout << "##################################################################################" << std::endl;
    std::cout << "##################################################################################" << std::endl;
    std::cout << "## Simulation is completed                                                      ##" << std::endl;
    std::cout << "##################################################################################" << std::endl;
    std::cout << "##################################################################################" << std::endl;
}
