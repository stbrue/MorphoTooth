//
// Created by Stefanie on 13.08.2018.
//

#include <cmath>
#include "Model.h"
#include "Geometrics.h"

void Model::diffusion(std::vector<Cell> &cells, int cellsInSimulation) {

    //Calculate for each cell its perimeter and area
    Geometrics::calculatePerimeterAndArea(cells, cellsInSimulation);

    for (int cell = 0; cell < cellsInSimulation; ++cell) {
        //Total diffusion area = perimeter + 2 * area (bottom and top area)
        double perimeter = cells[cell].getPerimeter();
        double cellArea = cells[cell].getCellArea();

        double diffusionArea = perimeter + (2 * cellArea);

    }
}