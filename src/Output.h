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
    static void initialCellCentersXY(Cell (&cells)[totalNrOfCells], int InSimulationCells);

    static void initialCellBordersXY(Cell (&cells)[totalNrOfCells], int InSimulationCells);

    static void bigOutput(Cell (&cells)[totalNrOfCells], Parameters params);

    static void RParameterChange(Cell (&cells)[totalNrOfCells], Parameters params);

    static void XYZOutputSimple(Cell (&cells)[totalNrOfCells], Parameters params);

    static void geomorphLinkOutput(Cell (&cells)[totalNrOfCells], Parameters params);

    static void plyOutput(Cell (&cells)[totalNrOfCells], Parameters params);

    static void RNoiseOutput(Cell (&cells)[totalNrOfCells], Parameters params, int repetition);

};


#endif //TOOTHMAKER_OUTPUT_H
