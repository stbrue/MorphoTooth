//
// Created by Stefanie on 13.08.2018.
//

#include "Output.h"

#include <iostream>
#include <fstream>
#include "Parameters.h"
#include "consts.h"
#include "Geometrics.h"
#include <sstream>

void Output::initialCellCentersXY(Cell (&cells)[maxNrOfCells], int InSimulationCells) {
    std::ofstream outputFile;
    outputFile.open("Initial_Cell_Centers.txt");

    outputFile << "X\tY" << std::endl;

    for (int cell = 0; cell < InSimulationCells; ++cell) {
        outputFile << cells[cell].getX() << "\t" << cells[cell].getY() << std::endl;
    }

    outputFile.close();
}

void Output::initialCellBordersXY(Cell (&cells)[maxNrOfCells], int InSimulationCells) {
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

void Output::bigOutput(Cell (&cells)[maxNrOfCells], Parameters params) {
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

void Output::ROutput(Cell (&cells)[maxNrOfCells], Parameters params) {
    // File name
    std::stringstream stringstream;
    std::string fileName;

    std::string path = "./Outputfiles/";
    std::string name = "ToothBig";
    std::string file = ".txt";

    stringstream << path << name << params.parameterToChange << "_" << params.valueOfParameterToChange << "_"
                 << params.currentIteration << file;
    fileName = stringstream.str();

    std::ofstream outputFile(path);
    outputFile.precision(params.outputPrecision);
    outputFile.open(fileName);

    // Header
    outputFile << "ParameterWithNoise" << "\t" << "SDOnNoise" << "\t" << "ParameterToChange" << "\t" <<
               "ValueOfParameterToChange" << "\t" << "TotalIterations" << "\t" << " TotalNumberOfCellsInSimulation"
               << std::endl;

    outputFile << params.parameterWithNoise << "\t" << params.sdPercentage << "\t" << params.parameterToChange
               << "\t" << params.valueOfParameterToChange << "\t" << params.currentIteration << "\t"
               << params.nrCellsInSimulation << std::endl;

    outputFile << std::endl;

    outputFile << "CellNumber" << "\t" << "x" << "\t" << "y" << "\t" << "z" << "\t" << "Group" << "\t"
               << "EpithelialAct" << "\t" << "EpithelialInh" << "\t" << "EpithelialSec" << "\t" << "DiffState" << "\t"
               << "EK" << "\t" << std::endl;


    // Body
    int groupCount = 0;

    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        int *neighbours = cells[cell].getNeighbours();
        for (int neighbour = 0; neighbour < cells[cell].getNrOfNeighbours(); ++neighbour) {
            int IDofN = neighbours[neighbour];
            // if neighbour is in simulation
            if (IDofN < maxNrOfCells) {
                outputFile << cell << "\t" << cells[cell].getX() << "\t" << cells[cell].getY() << "\t"
                           << cells[cell].getZ() << "\t" << groupCount << "\t"
                           << cells[cell].getProteinConcentrations()[PAct][LEpithelium] << "\t"
                           << cells[cell].getProteinConcentrations()[PInh][LEpithelium] << "\t"
                           << cells[cell].getProteinConcentrations()[PSec1][LEpithelium] << "\t"
                           << cells[cell].getDiffState() << "\t"
                           << cells[cell].isKnotCell()
                           << std::endl;
                outputFile << IDofN << "\t" << cells[IDofN].getX() << "\t" << cells[IDofN].getY() << "\t"
                           << cells[IDofN].getZ() << "\t" << groupCount << "\t"
                           << cells[IDofN].getProteinConcentrations()[PAct][LEpithelium] << "\t"
                           << cells[IDofN].getProteinConcentrations()[PInh][LEpithelium] << "\t"
                           << cells[IDofN].getProteinConcentrations()[PSec1][LEpithelium] << "\t"
                           << cells[IDofN].getDiffState()
                           << "\t" << cells[IDofN].isKnotCell()
                           << std::endl;
                groupCount += 1;
            }
        }
    }
    outputFile.close();
}

void Output::XYZOutputSimple(Cell (&cells)[maxNrOfCells], Parameters params) {
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

void Output::geomorphLinkOutput(Cell (&cells)[maxNrOfCells], Parameters params) {

    std::stringstream stringstream;
    std::string fileName;

    std::string path = "./Outputfiles/";
    std::string name = "Link";
    std::string file = ".txt";

    stringstream << path << name << params.parameterToChange << "_" << params.valueOfParameterToChange << "_"
                 << params.currentIteration << file;
    fileName = stringstream.str();

    std::ofstream outputFile(path);
    outputFile.precision(12);
    outputFile.open(fileName);

    //Print the ID's of each pair of neighbours
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        int *neighbours = cells[cell].getNeighbours();
        for (int neighbour = 0; neighbour < cells[cell].getNrOfNeighbours(); ++neighbour) {
            int IDOfN = neighbours[neighbour];
            // if neighbour is in Simulation
            if (IDOfN < maxNrOfCells) {
                outputFile << cell << "\t" << IDOfN << std::endl;
            }
        }
    }

    outputFile.close();
}

void Output::plyOutput(Cell (&cells)[maxNrOfCells], Parameters params) {
    // Do the triangulation
    std::vector<std::vector<int>> faces;
    Geometrics::triangulation(cells, params, faces);

    // Open File
    std::stringstream stringstream;
    std::string fileName;

    std::string path = "./Outputfiles/";
    std::string name = "Ply";
    std::string file = ".ply";

    stringstream << path << name << params.parameterToChange << "_" << params.valueOfParameterToChange << "_"
                 << params.currentIteration << file;
    fileName = stringstream.str();

    std::ofstream outputFile(path);
    outputFile.precision(12);
    outputFile.open(fileName);

    //Header
    outputFile << "ply" << std::endl;
    outputFile << "format ascii 1.0" << std::endl;
    outputFile << "comment this file is a teeth made with MorphoTooth" << std::endl;
    outputFile << "comment " << "parameterToChange: " << params.parameterToChange << " value of ParameterToChange: "
               << params.valueOfParameterToChange << std::endl;
    outputFile << "element vertex " << params.nrCellsInSimulation << std::endl;
    outputFile << "property float x" << std::endl;
    outputFile << "property float y" << std::endl;
    outputFile << "property float z" << std::endl;
    outputFile << "element face " << faces.size() << std::endl;
    outputFile << "property list unchar int vertex_indices" << std::endl;
    outputFile << "end_header" << std::endl;

    // List of X,Y,Z coordinates per line (vertex 0 - vertex n)
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        outputFile << cells[cell].getX() << " " << cells[cell].getY() << " " << cells[cell].getZ() << std::endl;
    }
    for (int face = 0; face < faces.size(); ++face) {
        std::vector<int> currentFace = faces[face];
        outputFile << currentFace.size();
        for (int vertex = 0; vertex < currentFace.size(); ++vertex) {
            outputFile << " " << currentFace[vertex];
        }
        outputFile << std::endl;
    }

    outputFile.close();
}