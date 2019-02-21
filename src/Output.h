//
// Created by Stefanie on 13.08.2018.
//

#ifndef TOOTHMAKER_OUTPUT_H
#define TOOTHMAKER_OUTPUT_H


#include "Cell.h"
#include "ImplementParams.h"
#include "consts.h"

class Output {

public:

    static void XYZOutputSimple(Cell (&cells)[totalNrOfCells], ImplementParams params, int repetition, int success);

    static void geomorphLinkOutput(Cell (&cells)[totalNrOfCells], ImplementParams params);

    static void plyOutput(Cell (&cells)[totalNrOfCells], ImplementParams params, int repetition, int success);

    static void ROutput(Cell (&cells)[totalNrOfCells], ImplementParams params, int repetition, int success);

    static std::string createOutputFileName(char outputType, ImplementParams params, std::string path, int repetition);

};


#endif //TOOTHMAKER_OUTPUT_H
