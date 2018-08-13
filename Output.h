//
// Created by Stefanie on 13.08.2018.
//

#ifndef TOOTHMAKER_OUTPUT_H
#define TOOTHMAKER_OUTPUT_H


#include "Cell.h"

class Output {

public:
    static void initialCellCentersXY(std::vector<Cell> cells, int InSimulationCells);
    static void initialCellBordersXY(std::vector<Cell> cells, int InSimulationCells);

};


#endif //TOOTHMAKER_OUTPUT_H
