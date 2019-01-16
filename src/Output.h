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
    static void initialCellCentersXY(Cell (&cells)[maxNrOfCells], int InSimulationCells);

    static void initialCellBordersXY(Cell (&cells)[maxNrOfCells], int InSimulationCells);

    static void bigOutput(Cell (&cells)[maxNrOfCells], Parameters params);

    static void ROutput(Cell (&cells)[maxNrOfCells], Parameters params);

    static void XYZOutputSimple(Cell (&cells)[maxNrOfCells], Parameters params);

    static void geomorphLinkOutput(Cell (&cells)[maxNrOfCells], Parameters params);

    static void plyOutput(Cell (&cells)[maxNrOfCells], Parameters params);

};


#endif //TOOTHMAKER_OUTPUT_H
