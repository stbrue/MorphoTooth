//
// Created by Stefanie on 13.08.2018.
//

#ifndef TOOTHMAKER_OUTPUT_H
#define TOOTHMAKER_OUTPUT_H


#include "Cell.h"
#include "Parameters.h"
#include "consts.h"

class Output {

public:

    static void XYZOutputSimple(Cell (&cells)[totalNrOfCells], Parameters params, int repetition, int success);

    static void geomorphLinkOutput(Cell (&cells)[totalNrOfCells], Parameters params);

    static void plyOutput(Cell (&cells)[totalNrOfCells], Parameters params, int repetition, int success);

    static void ROutput(Cell (&cells)[totalNrOfCells], Parameters params, int repetition, int success);

    static std::string createOutputFileName(char outputType, Parameters params, std::string path, int repetition);

};


#endif //TOOTHMAKER_OUTPUT_H
