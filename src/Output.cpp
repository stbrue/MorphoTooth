//
// Created by Stefanie on 13.08.2018.
//

#include "Output.h"

#include <iostream>
#include <fstream>
#include "Parameters.h"
#include "consts.h"

void Output::initialCellCentersXY(std::vector<Cell> cells, int InSimulationCells) {
    std::ofstream outputFile;
    outputFile.open("Initial_Cell_Centers.txt");

    outputFile << "X\tY" << std::endl;

    for (int cell = 0; cell < InSimulationCells; ++cell) {
        outputFile << cells[cell].getX() << "\t" << cells[cell].getY() << std::endl;
    }

    outputFile << "Rest of the cells" << std::endl;

    for (int cell = 7; cell < 19; ++cell) {
        outputFile << cells[cell].getX() << "\t" << cells[cell].getY() << std::endl;
    }

    outputFile.close();
}

void Output::initialCellBordersXY(std::vector<Cell> cells, int InSimulationCells) {
    std::ofstream outputFile;
    outputFile.open("Initial_Cell_Borders.txt");

    outputFile << "X\tY" << std::endl;

    for (int cell = 0; cell < InSimulationCells; ++cell) {
        for (int borderPoint = 0; borderPoint < cells[cell].getBorderPoints().size(); ++borderPoint) {
            outputFile << cells[cell].getBorderPoints()[borderPoint][0] << "\t"
                       << cells[cell].getBorderPoints()[borderPoint][1] << std::endl;
        }
    }


    outputFile.close();
}

void Output::bigOutput(std::vector<Cell> cells, Parameters params) {
    std::ofstream outputFile;
    outputFile.open("BigOutputMorphoTooth.txt");

    outputFile << "Iterations: " << params.iterations << "Cells in Simulation: " << params.nrCellsInSimulation << std::endl;

    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        outputFile << "Cell Nr.: " << cell << std::endl;
        outputFile << "X, Y, Z: " << cells[cell].getX() << "\t" << cells[cell].getY() << cells[cell].getZ() << std::endl;
        outputFile << "Diff State: " << cells[cell].getDiffState() << std::endl;
        outputFile << "Epithelial Act: " << cells[cell].getProteinConcentrations()[Act][Epithelium];
        outputFile << "Epithelial Inh: " << cells[cell].getProteinConcentrations()[Inh][Epithelium];
        outputFile << "Epithelial Sec1: " << cells[cell].getProteinConcentrations()[Sec1][Epithelium];
        outputFile << "Epithelial Sec2: " << cells[cell].getProteinConcentrations()[Sec2][Epithelium];
        outputFile << std::endl;
    }
}
