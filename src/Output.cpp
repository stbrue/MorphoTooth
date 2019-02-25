//
// Created by Stefanie on 13.08.2018.
//

#include "Output.h"

#include <iostream>
#include <fstream>
#include "ImplementParams.h"
#include "consts.h"
#include "Geometrics.h"
#include <sstream>

#ifdef __linux__
#include <sys/stat.h>
#elif _WIN32

#include <direct.h>

#endif

void Output::XYZOutputSimple(Cell (&cells)[totalNrOfCells], ImplementParams params, int repetition, int success) {
    // Define and create directory depending on success number
    std::string path;
    std::string directory;
    std::stringstream pathss;
    std::stringstream directoryss;
    pathss << "./Outputfiles" << ((success - 1) * params.minNrOfCells) << "/";
    directoryss << "./Outputfiles" << ((success - 1) * params.minNrOfCells);
    path = pathss.str();
    directory = directoryss.str();
#ifdef __linux__
    mkdir(directory.c_str(), S_IRWXU | S_IRWXG);
#elif _WIN32
    mkdir(directory.c_str());
#endif

    // Open File
    std::string name = "XYZSimple_";
    std::string file = ".txt";
    std::stringstream stringstream;
    std::string fileName;
    if (params.noiseType > 0) {
        stringstream << path << name << params.noiseType << "_" << params.parameterWithNoise << "_" << params.sd
                     << "_"
                     << params.noiseDuration << "_" << repetition
                     << file;
        fileName = stringstream.str();
    } else if (params.parameterToChange >= 0) {
        stringstream << path << name << params.parameterToChange << "_" << params.valueOfParameterToChange << "_"
                     << repetition
                     << file;
        fileName = stringstream.str();
    } else {
        stringstream << path << name << "normal" << file;
        fileName = stringstream.str();
    }

    std::ofstream outputFile(path);
    outputFile.precision(params.outputPrecision);
    outputFile.open(fileName);

    // Header
    outputFile << "ParameterWithNoise" << "\t" << "sd" << "\t" << "noiseDuration" << "\t" << "noiseType" << std::endl;
    outputFile << params.parameterWithNoise << "\t" << params.sd << "\t" << params.noiseDuration << "\t"
               << params.noiseType << std::endl;

    // Body
    outputFile << "x" << "\t" << "y" << "\t" << "z" << std::endl;
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        outputFile << cells[cell].getX() << "\t" << cells[cell].getY() << "\t" << cells[cell].getZ() << std::endl;
    }
    outputFile.close();
}

void Output::geomorphLinkOutput(Cell (&cells)[totalNrOfCells], ImplementParams params) {

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
            if (IDOfN < totalNrOfCells) {
                outputFile << cell << "\t" << IDOfN << std::endl;
            }
        }
    }

    outputFile.close();
}

void Output::plyOutput(Cell (&cells)[totalNrOfCells], ImplementParams params, int repetition, int success) {
    // Do the triangulation
    std::vector<std::vector<int>> faces;
    Geometrics::triangulation(cells, params, faces);

    // Define and create directory depending on success number
    std::string path;
    std::string directory;
    std::stringstream pathss;
    std::stringstream directoryss;
    pathss << "./Outputfiles" << ((success - 1) * params.minNrOfCells) << "/";
    directoryss << "./Outputfiles" << ((success - 1) * params.minNrOfCells);
    path = pathss.str();
    directory = directoryss.str();
#ifdef __linux__
    mkdir(directory.c_str(), S_IRWXU | S_IRWXG);
#elif _WIN32
    mkdir(directory.c_str());
#endif

    // Open File
    std::string fileName = Output::createOutputFileName('P', params, path, repetition);
    std::ofstream outputFile(path);
    outputFile.precision(params.outputPrecision);
    outputFile.open(fileName);

    //Header
    outputFile << "ply" << std::endl;
    outputFile << "format ascii 1.0" << std::endl;
    outputFile << "comment this file is a teeth made with MorphoTooth" << std::endl;
    outputFile << "comment " << "parameterToChange: " << params.parameterToChange << " value of ParameterToChange: "
               << params.valueOfParameterToChange << std::endl;
    outputFile << "comment " << "noiseType: " << params.noiseType << " noiseParameter: " << params.parameterWithNoise
               << " sd: " << params.sd << " repetition: " << repetition << std::endl;
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

    for (auto face : faces) {
        outputFile << face.size();
        for (auto vertex : face) {
            outputFile << " " << vertex;
        }
    }

    outputFile.close();
}

void Output::ROutput(Cell (&cells)[totalNrOfCells], ImplementParams params, int repetition, int success) {

    // Define and create directory depending on success number
    std::string path;
    std::string directory;
    std::stringstream pathss;
    std::stringstream directoryss;
    pathss << "./Outputfiles" << ((success - 1) * params.minNrOfCells) << "/";
    directoryss << "./Outputfiles" << ((success - 1) * params.minNrOfCells);
    path = pathss.str();
    directory = directoryss.str();
#ifdef __linux__
    mkdir(directory.c_str(), S_IRWXU | S_IRWXG);
#elif _WIN32
    mkdir(directory.c_str());
#endif

    // Open file
    std::string fileName = Output::createOutputFileName('R', params, path, repetition);
    std::ofstream outputFile(path);
    outputFile.precision(params.outputPrecision);
    outputFile.open(fileName);

    // Header
    outputFile << "ParameterWithNoise" << "\t" << "SDOnNoise" << "\t" << "ParameterToChange" << "\t" <<
               "ValueOfParameterToChange" << "\t" << "TotalIterations" << "\t" << " TotalNumberOfCellsInSimulation"
               << "\t" << "Repetition" << "\t" << "NoiseDuration" << "\t" << "NoiseType" << std::endl;

    outputFile << params.parameterWithNoise << "\t" << params.sd << "\t" << params.parameterToChange
               << "\t" << params.valueOfParameterToChange << "\t" << params.currentIteration << "\t"
               << params.nrCellsInSimulation << "\t" << repetition << "\t" << params.noiseDuration << "\t"
               << params.noiseType << std::endl;

    outputFile << std::endl;

    outputFile << "CellNumber" << "\t" << "x" << "\t" << "y" << "\t" << "z" << "\t" << "Group" << "\t"
               << "EpithelialAct" << "\t" << "EpithelialInh" << "\t" << "EpithelialSec" << "\t" << "DiffState" << "\t"
               << "EK" << "\t" << "CentreCell" << std::endl;


    // Body
    int groupCount = 0;

    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        int *neighbours = cells[cell].getNeighbours();
        for (int neighbour = 0; neighbour < cells[cell].getNrOfNeighbours(); ++neighbour) {
            int IDofN = neighbours[neighbour];
            // if neighbour is in simulation
            if (IDofN < totalNrOfCells) {
                outputFile << cell << "\t" << cells[cell].getX() << "\t" << cells[cell].getY() << "\t"
                           << cells[cell].getZ() << "\t" << groupCount << "\t"
                           << cells[cell].getProteinConcentrations()[PAct][LEpithelium] << "\t"
                           << cells[cell].getProteinConcentrations()[PInh][LEpithelium] << "\t"
                           << cells[cell].getProteinConcentrations()[PSec][LEpithelium] << "\t"
                           << cells[cell].getDiffState() << "\t"
                           << cells[cell].isKnotCell() << "\t" << cells[cell].isInCentre()
                           << std::endl;
                outputFile << IDofN << "\t" << cells[IDofN].getX() << "\t" << cells[IDofN].getY() << "\t"
                           << cells[IDofN].getZ() << "\t" << groupCount << "\t"
                           << cells[IDofN].getProteinConcentrations()[PAct][LEpithelium] << "\t"
                           << cells[IDofN].getProteinConcentrations()[PInh][LEpithelium] << "\t"
                           << cells[IDofN].getProteinConcentrations()[PSec][LEpithelium] << "\t"
                           << cells[IDofN].getDiffState()
                           << "\t" << cells[IDofN].isKnotCell() << "\t" << cells[IDofN].isInCentre()
                           << std::endl;
                groupCount += 1;
            }
        }
    }
    outputFile.close();
}

std::string Output::createOutputFileName(char outputType, ImplementParams params, std::string path, int repetition) {
    int outputCondition = 0;

    if (params.noiseType > 0) {
        outputCondition = 1;
    } else if (params.parameterToChange > 0) {
        outputCondition = 2;
    }

    // Create File name depending on the simulation conditions (if there was noise or parameter scanning or neither)
    std::stringstream stringstream;
    std::string fileName;
    std::string file;

    std::stringstream nameStream;

    switch (outputType) {
        case 'R': {
            file = ".txt";
            break;
        }
        case 'P': {
            file = ".ply";
            break;
        }
        default: {
            std::cout << "There was an error with creating output file name" << std::endl;
            std::cout.flush();
        }
    }

    switch (outputCondition) {
        case 1: {
            stringstream << path << outputType << "Noise_" << params.noiseType << "_" << params.parameterWithNoise
                         << "_" << params.sd
                         << "_" << params.noiseDuration << "_" << repetition << file;
            fileName = stringstream.str();
            return fileName;
        }
        case 2: {
            stringstream << path << outputType << "ParameterChange_" << params.parameterToChange << "_"
                         << params.valueOfParameterToChange << "_" << repetition << file;
            fileName = stringstream.str();
            return fileName;
        }
        default: {
            stringstream << path << outputType << "OutputNormal_" << repetition << file;
            fileName = stringstream.str();
            return fileName;
        }
    }
}