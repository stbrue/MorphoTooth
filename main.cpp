#include <iostream>
#include "Cell.h"

int main() {

   //Make the first cell
    Cell cell1(0, 0, 1, 1, 0, 0, 0, 0, 0);
    cell1.setMesenchymeThickness(4);

    //Vector containing all cells
    std::vector<Cell> cells;
    cells.push_back(cell1);




    return 0;
}