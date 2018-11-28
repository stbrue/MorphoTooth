//
// Created by Stefanie on 13.08.2018.
//

#include "Output.h"

#include <iostream>
#include <fstream>
#include "Parameters.h"
#include "consts.h"
#include <sstream>

void Output::initialCellCentersXY(std::vector<Cell> cells, int InSimulationCells) {
    std::ofstream outputFile;
    outputFile.open("Initial_Cell_Centers.txt");

    outputFile << "X\tY" << std::endl;

    for (int cell = 0; cell < InSimulationCells; ++cell) {
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
            outputFile << cells[cell].getBorderPoints()[borderPoint][X] << "\t"
                       << cells[cell].getBorderPoints()[borderPoint][Y] << std::endl;
        }
    }


    outputFile.close();
}

void Output::bigOutput(std::vector<Cell> cells, Parameters params) {
    std::ofstream outputFile;
    outputFile.precision(params.outputPrecision);
    outputFile.open("BigOutputMorphoTooth.txt");

    outputFile << "Iterations: " << params.currentIteration << "Cells in Simulation: " << params.nrCellsInSimulation
               << std::endl;

    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        outputFile << "Cell Nr.: " << cell << std::endl;
        outputFile << "X, Y, Z: " << cells[cell].getX() << "\t" << cells[cell].getY() << "\t" << cells[cell].getZ()
                   << std::endl;
        outputFile << "Diff State: " << cells[cell].getDiffState() << std::endl;
        outputFile << "Epithelial Act: " << cells[cell].getProteinConcentrations()[PAct][LEpithelium] << std::endl;
        outputFile << "Epithelial Inh: " << cells[cell].getProteinConcentrations()[PInh][LEpithelium] << std::endl;
        outputFile << "Epithelial Sec1: " << cells[cell].getProteinConcentrations()[PSec1][LEpithelium] << std::endl;
        outputFile << "Epithelial Sec2: " << cells[cell].getProteinConcentrations()[PSec2][LEpithelium] << std::endl;
        outputFile << std::endl;
    }

    outputFile.close();
}

void Output::ROutput(std::vector<Cell> cells, Parameters params) {
    std::stringstream stringstream;
    std::string fileName;

    std::string path = "./Outputfiles/";
    std::string name = "ToothBig";
    std::string file = ".txt";

    stringstream << path << name << params.parameterToChange << "_" << params.valueOfParameterToChange << file;
    fileName = stringstream.str();

    std::ofstream outputFile(path);
    outputFile.precision(12);
    outputFile.open(fileName);

    outputFile << "CellNumber" << "\t" << "x" << "\t" << "y" << "\t" << "z" << "\t" << "Group" << "\t"
               << "EpithelialAct" << "\t" << "EpithelialInh" << "\t" << "EpithelialSec" << "\t" << "DiffState" << "\t"
               << "EK" << "\t" << "TotalIterations" << std::endl;

    int groupCount = 0;

    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        std::vector<int> neighbours = cells[cell].getNeighbours();
        for (int neighbour = 0; neighbour < neighbours.size(); ++neighbour) {
            int IDofN = neighbours[neighbour];
            bool neighbourIsInSimulation = cells[IDofN].isInSimulation();
            if (neighbourIsInSimulation) {
                outputFile << cell << "\t" << cells[cell].getX() << "\t" << cells[cell].getY() << "\t"
                           << cells[cell].getZ() << "\t" << groupCount << "\t"
                           << cells[cell].getProteinConcentrations()[PAct][LEpithelium] << "\t"
                           << cells[cell].getProteinConcentrations()[PInh][LEpithelium] << "\t"
                           << cells[cell].getProteinConcentrations()[PSec1][LEpithelium] << "\t"
                           << cells[cell].getDiffState() << "\t"
                           << cells[cell].isKnotCell() << "\t" << params.currentIteration
                           << std::endl;
                outputFile << IDofN << "\t" << cells[IDofN].getX() << "\t" << cells[IDofN].getY() << "\t"
                           << cells[IDofN].getZ() << "\t" << groupCount << "\t"
                           << cells[IDofN].getProteinConcentrations()[PAct][LEpithelium] << "\t"
                           << cells[IDofN].getProteinConcentrations()[PInh][LEpithelium] << "\t"
                           << cells[IDofN].getProteinConcentrations()[PSec1][LEpithelium] << "\t"
                           << cells[IDofN].getDiffState()
                           << "\t" << cells[IDofN].isKnotCell() << "\t" << params.currentIteration
                           << std::endl;
                groupCount += 1;
            }
        }
    }
    outputFile.close();
}

void Output::XYZOutputSimple(std::vector<Cell> cells, Parameters params) {
    std::stringstream stringstream;
    std::string fileName;

    std::string path = "./Outputfiles/";
    std::string name = "XYZSimple";
    std::string file = ".txt";

    stringstream << path << name << params.currentIteration << file;
    fileName = stringstream.str();

    std::ofstream outputFile(path);
    outputFile.precision(12);
    outputFile.open(fileName);

    outputFile << "x" << "\t" << "y" << "\t" << "z" << std::endl;

    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        outputFile << cells[cell].getX() << "\t" << cells[cell].getY() << "\t" << cells[cell].getZ() << std::endl;
    }
    outputFile.close();
}

void Output::geomorphLinkOutput(std::vector<Cell> cells, Parameters params) {

    std::stringstream stringstream;
    std::string fileName;

    std::string path = "./Outputfiles/";
    std::string name = "Link";
    std::string file = ".txt";

    stringstream << path << name << params.parameterToChange << "_" << params.valueOfParameterToChange << file;
    fileName = stringstream.str();

    std::ofstream outputFile(path);
    outputFile.precision(12);
    outputFile.open(fileName);

    //Print the ID's of each pair of neighbours
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        std::vector<int> neighbours = cells[cell].getNeighbours();
        for (int neighbour = 0; neighbour < neighbours.size(); ++neighbour) {
            int IDOfN = neighbours[neighbour];
            bool neighbourIsInSimulation = cells[IDOfN].isInSimulation();
            if (neighbourIsInSimulation) {
                outputFile << cell << "\t" << IDOfN << std::endl;
            }
        }
    }

    outputFile.close();
}
