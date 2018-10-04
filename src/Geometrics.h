//
// Created by Stefanie on 13.08.2018.
//

#ifndef TOOTHMAKER_GEOMETRICS_H
#define TOOTHMAKER_GEOMETRICS_H


#include "Cell.h"

/**
 * @brief   Contains all methods that are used to calculate geometrical values (distances, norm, cross product,...)
 */
class Geometrics {
public:

    /**
     * @brief   calculates the square of the distance between two cell centers in the xyz plane (without taking square root)
     * @param   cell1
     * @param   cell2
     * @return  distance
     */
    static double squareCenterDistance3D(Cell cell1, Cell cell2);

    /**
     * @brief   calculates the distance between two cell centers in the xy plane
     * @param   cell1
     * @param   cell2
     * @return  distance
     */
    static double centerDistance2D(Cell cell1, Cell cell2);

    /**
     * @brief   calculates the distance between two cell centers in the xyz plane
     * @param   cell1
     * @param   cell2
     * @return  distance
     */
    static double centerDistance3D(Cell cell1, Cell cell2);

    /**
     * @brief   calculates the euclidean distance between two points in the xy plane
     * @param   v1    vector with x,y, and z coordinates of a point
     * @param   v2  vector with x,y, and z coordinates of a point
     * @return  distance
     */
    static double distance2D(std::vector<double> v1, std::vector<double> v2);

    /**
     * @brief   calculates the euclidean distance between two points in the xyz plane
     * @param   v1    vector with x,y, and z coordinates of a point
     * @param   v2    vector with x,y, and z coordinates of a point
     * @return  distance
     */
    static double distance3D(std::vector<double> v1, std::vector<double> v2);

    /**
     * @brief   calculates the euclidean norm of a vector (its length)
     * @param   v   vector with 3 components
     * @return  norm
     */
    static double vectorNorm3D(std::vector<double> v);

    /**
     * @brief   calculates the cross product of two vectors
     * @param   v1  vector with 3 components
     * @param   v2  vector with 3 components
     * @return  cross product (a vector with 3 components)
     */
    static std::vector<double> crossProduct(std::vector<double> v1, std::vector<double> v2);

    /**
     * @brief   adds up all components of a vector
     * @param   v   vector
     * @return  sum
     */
    static double vectorSum(std::vector<double> v);

    /**
     * @brief   calls function to calculate cell perimeter parts and area parts and defines their sum as perimeter and area
     * @param   cells   vector containing all cells
     * @param   nrCellsInSimulation number of cells that are in simulation (have a closed neighbour sequence)
     */
    static void calculatePerimeterAndArea(std::vector<Cell> &cells, int nrCellsInSimulation);

    /**
     * @brief   calculates a part of the cell perimeter (= length of border to a neighbour)
     * @param   cells   vector containing all cells
     * @param   cell    ID of the current center cell
     * @param   borderPoint1    first border point
     * @param   borderPoint2    second border point
     */
    static void calculatePerimeterParts(std::vector<Cell> &cells, int cell, int borderPoint1, int borderPoint2);

    /**
     * @brief   calculates a part of the cell area (= triangle between two border points and center cell)
     * @param   cells   vector containing all cells
     * @param   cell    ID of the current center cell
     * @param   borderPoint1    first neighbour
     * @param   borderPoint2    second neighbour (adjacent to borderPoint1)
     */
    static void calculateCellAreaParts(std::vector<Cell> &cells, int cell, int borderPoint1, int borderPoint2);

    /**
     * @brief   calculates the distance of a cell to the origin in the xy plane
     * @param   cell
     * @return  distance
     */
    static double centerDistanceToOrigin2D(Cell cell);

    /**
     * @brief   calculates the distance of a cell to the origin in the xyz plane
     * @param   cell
     * @return  distance
     */
    static double centerDistanceToOrigin3D(Cell cell);

    /**
    * @brief   Defines neighbour pairs and calls function to calculate the border between them (Voronoi Diagram)
    * @param   cells   Vector containing all cells
    * @param   nrCellsInSimulation     How many cells are in simulation
    */
    static void calculateCellBorders(std::vector<Cell> &cells, int nrCellsInSimulation);

    /**
    * @brief   Calculates and sets the midpoint between two (or one) adjacent neighbours and the center cell (Voronoi node)
    * @param   cells     Vector containing all cells
    * @param   centreCell ID of cell that is in the center
    * @param   neighbour1 Which neighbour (first, second, ...)
    * @param   neighbour2 Which neighbour (first, second, ...)
    */
    static void setBorders(std::vector<Cell> &cells, int centreCell, int neighbour1, int neighbour2);
};


#endif //TOOTHMAKER_GEOMETRICS_H
