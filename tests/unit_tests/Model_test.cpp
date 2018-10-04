//
// Created by Stefanie on 02.10.2018.
//

#include <Cell.h>
#include <Model.h>
#include "gtest/gtest.h"

class ModelTestFixture : public ::testing::Test {
public:
    ModelTestFixture() {
        // initialization code here
    }

    void SetUp() {
        // code here will execute just before the test runs
        std::vector<Cell> cells;
        Cell cell0(0, 0, 1, 0);
        Cell cell1(0, 2, 1.1, 1);
        Cell cell2(0.75, 1, 1.15, 2);
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

    }

    void TearDown() {
        // code here will be called just after the test completes
        // ok to throw exceptions from here if needed
    }

    ~ModelTestFixture() {
        // cleanup any pending stuff, but no exceptions allowed
    }

    // put here in any custom data members that you need (for several/all tests)



};

