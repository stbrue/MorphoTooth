#include <iostream>
#include "Cell.h"

int main() {

    //Make the first cell
    Cell cell1(0, 0, 1);

    //Vector containing all cells
    std::vector<Cell> cells;

    //The first one is a placeholder (ID = index)
    cells.push_back(cell1);
    cells.push_back(cell1);

    std::cout << cells[1].getMesenchymeThickness();




    return 0;
}