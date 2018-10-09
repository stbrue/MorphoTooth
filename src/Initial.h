//
// Created by Stefanie on 30.07.2018.
//

#ifndef TOOTHMAKER_INITIAL_H
#define TOOTHMAKER_INITIAL_H


#include "Cell.h"
#include "Parameters.h"

/**
 * @brief   Set up of the initial cell grid
 *
 * @details Calculates the positions of new cells and instantiates them
 */
class Initial {

private:
    static const int distanceBetweenCells = 1;


public:
    int getTotalNumberOfCells(int initialRadius);

    /**
    * @brief   Calculates how many cells are "in simulation" (have a closed neighbour sequence)
    * @param   initialRadius
    * @return  number of cells in simulation
    */
    static int getNumberOfInSimulationCells(int initialRadius);

    /**
    * @brief   Calculates the x-position of a certain neighbour of the center cell
    * @param   centerCoordinate    the x position of the center cell for which the neighbours are calculated
    * @param   neighbour           which neighbour (first, second, ...) is calculated (beginning with the one that is 1 unit
    *                              higher in y and then clockwise)
    * @return  x-value of neighbour (rounded to 6 decimal places)
    */
    static double nextX(double centerX, int neighbour);


    /**
    * @brief   Calculates the y-position of a certain neighbour of the center cell
    * @param   centerCoordinate    the y position of the center cell for which the neighbours are calculated
    * @param   neighbour           which neighbour (first, second, ...) is calculated (beginning with the one that is 1 unit
    *                              higher in y and then clockwise)
     * @return  y-value of neighbour (rounded to 6 decimal places)
    */
    static double nextY(double centerX, int neighbour);

    /**
    * @brief Instantiates all the initial cells and calculates their borders
    * @param params struct containing all parameters
    * @return a vector containing all cells
    */
    static std::vector<Cell> makeInitialGrid(Parameters &params);

    /**
    * @brief   Creates or declares all neighbours for one centre cell
    * @param   cells   Vector containing all cells
    * @param   IDCentreCell ID of the cell that gets new neighbours
    * @param   IDNewCell   ID that a new cell gets (always one higher than the ID of the last cell in cells)
    */
    static void makeNeighbours(std::vector<Cell> &cells, int IDCentreCell, int &IDNewCell);

    static void printInitialGrid(std::vector<Cell> &cells);

    static void printInitialNeighbours(std::vector<Cell> cells);

    /**
    * @brief   Checks if cells are "within simulation" (have a closed neighbour sequence) and labels them accordingly
    * @param   cells   Vector containing all cells
    * @param   params  Struct containing all parameters
    */
    static void labelNrCellsInSimulation(std::vector<Cell> &cells, Parameters &params);

    /**
    * @brief   Checks if cells are "in the center" (have neighbours that are all within simulation or at least 7) and labels them accordingly
    * @attention   This function has to be called after labelNrCellsInSimulation because it needs the this as parameter
    * @param   cells   Vector containing all cells
    * @param   params  Struct containing all parameters
    */
    static void labelCellsInCentre(std::vector<Cell> &cells, Parameters &params);

    /**
    * @brief   Deletes entries of neighbours that each cell has maximally one entry of a neighbour cell that is not within simulation
    * @param   cells   Vector containing all cells
    * @param   nrCellsInSimulation     How many cells are within simulation
    */
    static void reduceNeighboursOutOfSimulation(std::vector<Cell> &cells, int nrCellsInSimulation);

    /**
    * @brief   Checks if a certain neighbour is within simulation
    * @param   cells   Vector containing all cells
    * @param   IDCentreCell    ID of the cell of which we look at the neighbours
    * @param   neighbour       which neighbour we look at (the first, second, third..)
    * @return  true if this neighbour is within simulation (has a closed neighbour sequence)
    */
    static bool isNeighbourInSimulation(std::vector<Cell> &cells, int IDCentreCell, int neighbour);


};


#endif //TOOTHMAKER_INITIAL_H
