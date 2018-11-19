#include <iostream>
#include "Input.h"
#include "Initial.h"
#include "Output.h"
#include "Geometrics.h"
#include "Model.h"
#include "Parameters.h"


int main() {

    //Make instance of Parameters by reading in the parameters from input file
    Parameters params = Input::setParameters();

    //Construct the initial grid of cells
    std::vector<Cell> cells = Initial::makeInitialGrid(params);

    //The big loop
    //In each iteration mechanisms as diffusion, reaction, growth, and cell division take place
    for (int step = 0; step < params.iterations; ++step) {
        Model::iterationStep(cells, params);
        //Abort the loop if there is an error
        if (params.error) {
            std::cout << "The loop is stopped because there was an error at iteration: " << step << std::endl;
            break;
        }

        if (params.cellDivisionCount == 2){
            std::cout << "The loop is stopped because this was cell division number " << params.cellDivisionCount << std::endl;
            std::cout << "This was at iteration " << step << std::endl;
            break;
        }
        //Print every 100 iteration the count
        if (step % 100 == 0) {
            std::cout << step << std::endl;
            std::cout << "ncels: " << params.nrCellsInSimulation << std::endl;
            std::cout.flush();
        }
    }

    Output::coordinatesXYOutput(cells, params);

    /*
        //Test
        std::vector<Cell> cells;
        Cell cell0(0, 0, 1, 0);
        Cell cell1(0, 2, 1.1, 1);
        Cell cell2(1.5, 1, 1.15, 2);
        Cell cell3(2, -2, 1.1, 3);
        Cell cell4(0, -3, 1.4, 4);
        Cell cell5(-2, -1, 1.2, 5);
        Cell cell6(-2, 0, 1.2, 6);
        Cell cell7(0, 6, 1.1, 7);
        Cell cell8(2, 3, 1.5, 8);
        Cell cell9(-2, 3, 1.3, 9);
        Cell cell10(3, 2, 1.45, 10);
        Cell cell11(3, 0, 1.4, 11);
        Cell cell12(3, -1, 1.2, 12);
        Cell cell13(2, -5, 1.3, 13);
        Cell cell14(0, -6, 1.2, 14);
        Cell cell15(-2, -5, 1.1, 15);
        Cell cell16(-4, -3, 1.35, 16);
        Cell cell17(-4, 0, 1.2, 17);
        Cell cell18(-5, 1, 1.25, 18);

        cells.push_back(cell0);
        cells.push_back(cell1);
        cells.push_back(cell2);
        cells.push_back(cell3);
        cells.push_back(cell4);
        cells.push_back(cell5);
        cells.push_back(cell6);
        cells.push_back(cell7);
        cells.push_back(cell8);
        cells.push_back(cell9);
        cells.push_back(cell10);
        cells.push_back(cell11);
        cells.push_back(cell12);
        cells.push_back(cell13);
        cells.push_back(cell14);
        cells.push_back(cell15);
        cells.push_back(cell16);
        cells.push_back(cell17);
        cells.push_back(cell18);

        for (int cell = 0; cell < 7; ++cell) {
            cells[cell].setInSimulation(true);
            cells[cell].setInCentre(true);

        }

        cells[0].setNeighbour(1);
        cells[0].setNeighbour(2);
        cells[0].setNeighbour(3);
        cells[0].setNeighbour(4);
        cells[0].setNeighbour(5);
        cells[0].setNeighbour(6);

        cells[1].setNeighbour(7);
        cells[1].setNeighbour(8);
        cells[1].setNeighbour(2);
        cells[1].setNeighbour(0);
        cells[1].setNeighbour(6);
        cells[1].setNeighbour(9);

        cells[2].setNeighbour(8);
        cells[2].setNeighbour(10);
        cells[2].setNeighbour(11);
        cells[2].setNeighbour(3);
        cells[2].setNeighbour(0);
        cells[2].setNeighbour(1);

        cells[3].setNeighbour(2);
        cells[3].setNeighbour(11);
        cells[3].setNeighbour(12);
        cells[3].setNeighbour(13);
        cells[3].setNeighbour(4);
        cells[3].setNeighbour(0);

        cells[4].setNeighbour(0);
        cells[4].setNeighbour(3);
        cells[4].setNeighbour(13);
        cells[4].setNeighbour(14);
        cells[4].setNeighbour(15);
        cells[4].setNeighbour(5);

        cells[5].setNeighbour(6);
        cells[5].setNeighbour(0);
        cells[5].setNeighbour(4);
        cells[5].setNeighbour(15);
        cells[5].setNeighbour(16);
        cells[5].setNeighbour(17);

        cells[6].setNeighbour(9);
        cells[6].setNeighbour(1);
        cells[6].setNeighbour(0);
        cells[6].setNeighbour(5);
        cells[6].setNeighbour(17);
        cells[6].setNeighbour(18);

        Parameters params = Input::defineParametersSealTest();
        params.nrCellsInSimulation = 7;

        //Act
        Geometrics::calculateCellBorders(cells, 7);

        cells[0].setProteinConcentration(0, 0, 1);
        cells[0].setProteinConcentration(0, 1, 1.1);
        cells[0].setProteinConcentration(0, 2, 1.2);
        cells[0].setProteinConcentration(0, 3, 1.3);
        cells[0].setProteinConcentration(1, 0, 1.4);
        cells[0].setProteinConcentration(1, 1, 1.5);
        cells[0].setProteinConcentration(1, 2, 1.6);
        cells[0].setProteinConcentration(1, 3, 1.7);
        cells[0].setProteinConcentration(2, 0, 1.8);
        cells[0].setProteinConcentration(2, 1, 1.9);
        cells[0].setProteinConcentration(2, 2, 2);
        cells[0].setProteinConcentration(2, 3, 2.1);
        cells[0].setProteinConcentration(3, 0, 2.2);
        cells[0].setProteinConcentration(3, 1, 2.3);
        cells[0].setProteinConcentration(3, 2, 2.4);
        cells[0].setProteinConcentration(3, 3, 2.5);

        cells[1].setProteinConcentration(0, 0, 2);
        cells[1].setProteinConcentration(0, 1, 2.1);
        cells[1].setProteinConcentration(0, 2, 2.2);
        cells[1].setProteinConcentration(0, 3, 2.3);
        cells[1].setProteinConcentration(1, 0, 2.4);
        cells[1].setProteinConcentration(1, 1, 2.5);
        cells[1].setProteinConcentration(1, 2, 2.6);
        cells[1].setProteinConcentration(1, 3, 2.7);
        cells[1].setProteinConcentration(2, 0, 2.8);
        cells[1].setProteinConcentration(2, 1, 2.9);
        cells[1].setProteinConcentration(2, 2, 3);
        cells[1].setProteinConcentration(2, 3, 3.1);
        cells[1].setProteinConcentration(3, 0, 3.2);
        cells[1].setProteinConcentration(3, 1, 3.3);
        cells[1].setProteinConcentration(3, 2, 3.4);
        cells[1].setProteinConcentration(3, 3, 3.5);

        cells[2].setProteinConcentration(0, 0, 4);
        cells[2].setProteinConcentration(0, 1, 4.1);
        cells[2].setProteinConcentration(0, 2, 4.2);
        cells[2].setProteinConcentration(0, 3, 4.3);
        cells[2].setProteinConcentration(1, 0, 4.4);
        cells[2].setProteinConcentration(1, 1, 4.5);
        cells[2].setProteinConcentration(1, 2, 4.6);
        cells[2].setProteinConcentration(1, 3, 4.7);
        cells[2].setProteinConcentration(2, 0, 4.8);
        cells[2].setProteinConcentration(2, 1, 4.9);
        cells[2].setProteinConcentration(2, 2, 4);
        cells[2].setProteinConcentration(2, 3, 4.1);
        cells[2].setProteinConcentration(3, 0, 5.2);
        cells[2].setProteinConcentration(3, 1, 5.3);
        cells[2].setProteinConcentration(3, 2, 5.4);
        cells[2].setProteinConcentration(3, 3, 5.5);

        cells[3].setProteinConcentration(0, 0, 6);
        cells[3].setProteinConcentration(0, 1, 6.1);
        cells[3].setProteinConcentration(0, 2, 6.2);
        cells[3].setProteinConcentration(0, 3, 6.3);
        cells[3].setProteinConcentration(1, 0, 6.4);
        cells[3].setProteinConcentration(1, 1, 6.5);
        cells[3].setProteinConcentration(1, 2, 6.6);
        cells[3].setProteinConcentration(1, 3, 6.7);
        cells[3].setProteinConcentration(2, 0, 6.8);
        cells[3].setProteinConcentration(2, 1, 6.9);
        cells[3].setProteinConcentration(2, 2, 7);
        cells[3].setProteinConcentration(2, 3, 7.1);
        cells[3].setProteinConcentration(3, 0, 7.2);
        cells[3].setProteinConcentration(3, 1, 7.3);
        cells[3].setProteinConcentration(3, 2, 7.4);
        cells[3].setProteinConcentration(3, 3, 7.5);

        cells[4].setProteinConcentration(0, 0, 8);
        cells[4].setProteinConcentration(0, 1, 8.1);
        cells[4].setProteinConcentration(0, 2, 8.2);
        cells[4].setProteinConcentration(0, 3, 8.3);
        cells[4].setProteinConcentration(1, 0, 8.4);
        cells[4].setProteinConcentration(1, 1, 8.5);
        cells[4].setProteinConcentration(1, 2, 8.6);
        cells[4].setProteinConcentration(1, 3, 8.7);
        cells[4].setProteinConcentration(2, 0, 8.8);
        cells[4].setProteinConcentration(2, 1, 8.9);
        cells[4].setProteinConcentration(2, 2, 9);
        cells[4].setProteinConcentration(2, 3, 9.1);
        cells[4].setProteinConcentration(3, 0, 9.2);
        cells[4].setProteinConcentration(3, 1, 9.3);
        cells[4].setProteinConcentration(3, 2, 9.4);
        cells[4].setProteinConcentration(3, 3, 9.5);

        cells[5].setProteinConcentration(0, 0, 10);
        cells[5].setProteinConcentration(0, 1, 10.1);
        cells[5].setProteinConcentration(0, 2, 10.2);
        cells[5].setProteinConcentration(0, 3, 10.3);
        cells[5].setProteinConcentration(1, 0, 10.4);
        cells[5].setProteinConcentration(1, 1, 10.5);
        cells[5].setProteinConcentration(1, 2, 10.6);
        cells[5].setProteinConcentration(1, 3, 10.7);
        cells[5].setProteinConcentration(2, 0, 10.8);
        cells[5].setProteinConcentration(2, 1, 10.9);
        cells[5].setProteinConcentration(2, 2, 11);
        cells[5].setProteinConcentration(2, 3, 11.1);
        cells[5].setProteinConcentration(3, 0, 11.2);
        cells[5].setProteinConcentration(3, 1, 11.3);
        cells[5].setProteinConcentration(3, 2, 11.4);
        cells[5].setProteinConcentration(3, 3, 11.5);

        cells[6].setProteinConcentration(0, 0, 12);
        cells[6].setProteinConcentration(0, 1, 12.1);
        cells[6].setProteinConcentration(0, 2, 12.2);
        cells[6].setProteinConcentration(0, 3, 12.3);
        cells[6].setProteinConcentration(1, 0, 12.4);
        cells[6].setProteinConcentration(1, 1, 12.5);
        cells[6].setProteinConcentration(1, 2, 12.6);
        cells[6].setProteinConcentration(1, 3, 12.7);
        cells[6].setProteinConcentration(2, 0, 12.8);
        cells[6].setProteinConcentration(2, 1, 12.9);
        cells[6].setProteinConcentration(2, 2, 13);
        cells[6].setProteinConcentration(2, 3, 13.1);
        cells[6].setProteinConcentration(3, 0, 13.2);
        cells[6].setProteinConcentration(3, 1, 13.3);
        cells[6].setProteinConcentration(3, 2, 13.4);
        cells[6].setProteinConcentration(3, 3, 13.5);

        Model::repulsionAndAdhesion(cells, params);

        for (int cell = 0; cell < 7; ++cell) {
            std::cout << "Cell nr" << cell << std::endl;
            for (int protein = 0; protein < 4; ++protein) {
                std::cout << "Protein nr" << protein << std::endl;
                for (int layer = 0; layer < 4; ++layer) {
                    std::cout << cells[cell].getProteinConcentrations()[protein][layer] << std::endl;
                }
            }
        }*/


    return 0;
}