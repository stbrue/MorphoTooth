//
// Created by Stefanie on 13.08.2018.
//

#ifndef TOOTHMAKER_GEOMETRICS_H
#define TOOTHMAKER_GEOMETRICS_H


#include "Cell.h"

class Geometrics {
public:

    static double getCenterDistance2D(Cell cell1, Cell cell2);
    static double getCenterDistance3D(Cell cell1, Cell cell2);

};


#endif //TOOTHMAKER_GEOMETRICS_H
