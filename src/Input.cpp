//
// Created by Stefanie on 07.09.2018.
//

#include "Input.h"
#include <iostream>
#include <fstream>

Parameters Input::defineParametersSealTest() {
    Parameters params;

    params.initialRadius = 2;
    params.iterations = 3;
    params.diffusionRates = {0.2, 0.2, 0.2, 0};
    params.nrCellsInSimulation = 0;
    params.delta = 0.05;
    params.egr = 0.017;
    params.mgr = 200;
    params.dgr = 10000;
    params.boy = 0.1;
    params.act = 1.1;
    params.inh = 26;
    params.mu = 0.1;
    params.inT = 0.19;
    params.set = 0.95;
    params.sec = 0.03;
    params.sec2Inhibition = 0.19;
    params.lbi = 1;
    params.bbi = 1;
    params.swi = 0;
    params.dff = 0.0002;
    params.rep = 1;
    params.adh = 0.001;
    params.ntr = 0.00001;
    params.bwi = 0.8;
    params.abi = 18;
    params.pbi = 15;
    params.bgr = 1;

    return params;
}

Parameters Input::setParameters() {
    Parameters params;
    params.error = false;
    std::string line;
    int counter = 0;

    std::ifstream InputFile("TestInput.txt");
    if (InputFile.is_open()) {
        while (getline(InputFile, line)) {
            switch (counter) {
                case 0: {
                    params.iterations = std::stoi(line);
                    break;
                }
                case 1: {
                    params.initialRadius = std::stoi(line);
                    break;
                }
                case 2: {
                    params.diffusionRates.push_back(std::stod(line));
                    break;
                }
                case 3: {
                    params.diffusionRates.push_back(std::stod(line));
                    break;
                }
                case 4: {
                    params.diffusionRates.push_back(std::stod(line));
                    break;
                }
                case 5: {
                    params.diffusionRates.push_back(std::stod(line));
                    break;
                }
                case 6: {
                    params.delta = std::stod(line);
                    break;
                }
                case 7: {
                    params.act = std::stod(line);
                    break;
                }
                case 8: {
                    params.inh = std::stod(line);
                    break;
                }
                case 9: {
                    params.mu = std::stod(line);
                    break;
                }
                case 10: {
                    params.inT = std::stod(line);
                    break;
                }
                case 11: {
                    params.set = std::stod(line);
                    break;
                }
                case 12: {
                    params.sec = std::stod(line);
                    break;
                }
                case 13: {
                    params.sec2Inhibition = std::stod(line);
                    break;
                }
                case 14: {
                    params.lbi = std::stod(line);
                    break;
                }
                case 15: {
                    params.bbi = std::stod(line);
                    break;
                }
                case 16: {
                    params.swi = std::stod(line);
                    break;
                }
                case 17: {
                    params.dff = std::stod(line);
                    break;
                }
                case 18: {
                    params.egr = std::stod(line);
                    break;
                }
                case 19: {
                    params.mgr = std::stod(line);
                    break;
                }
                case 20: {
                    params.dgr = std::stod(line);
                    break;
                }
                case 21: {
                    params.boy = std::stod(line);
                    break;
                }
                case 22: {
                    params.rep = std::stod(line);
                    break;
                }
                case 23: {
                    params.adh = std::stod(line);
                    break;
                }
                case 24: {
                    params.ntr = std::stod(line);
                    break;
                }
                case 25: {
                    params.bwi = std::stod(line);
                    break;
                }
                case 26: {
                    params.abi = std::stod(line);
                    break;
                }
                case 27: {
                    params.pbi = std::stod(line);
                    break;
                }
                case 28: {
                    params.bgr = std::stod(line);
                    break;
                }
                default: {
                    std::cout << "Error in reading of input values" << std::endl;
                }
            }
            counter += 1;
        }
        InputFile.close();
    } else std::cout << "Unable to open file";

    return params;
}
