//
// Created by Stefanie on 30.07.2018.
//

#ifndef TOOTHMAKER_CELL_H
#define TOOTHMAKER_CELL_H

#include <vector>

/**
 * Object that contains all information and features about a cell
 */
class Cell {
private:
    /**
     * position on the x-axis
     */
    double x;

    /**
     * temp coordinates are used to cache the position changes resulting from the different forces
     * and are applied on the position after all forces are calculated
     */
    double tempX;

    /**
     * position on the y-axis
     */
    double y;

    /**
     * temp coordinates are used to cache the position changes resulting from the diffferent forces
     * and are applied on the position after all forces are calculated
     */
    double tempY;

    /**
     * position on the z-axis
     */
    double z;

    /**
     * temp coordinates are used to cache the position changes resulting from the diffferent forces
     * and are applied on the position after all forces are calculated
     */
    double tempZ;

    /**
     * The ID of a cell is identical with their index in the vector containing all cells
     */
    int ID;

    /**
     * contains all neighbours (their ID). The order is relevant (clockwise order)
     */
    std::vector<int> neighbours;

    /**
     * the differentiation state is a variable indicating the "age" of a cell
     */
    double diffState;

    /**
     * proteinConcentrations[protein][layer]
     * Proteins: Act, Inh, Sec1, Sec2
     * Layers: Epithelium, Mesenchyme1, Mesenchyme2,.. MesenchymeThickness
     */
    std::vector<std::vector<double>> proteinConcentrations;

    /**
     * tempProteinConcentrations[protein][layer]
     *
     * contains the resulting concentration changes based on concentration differences
     */
    std::vector<std::vector<double>> tempProteinConcentrations;

    /**
     * If this cell is an enamel knot cell
     */
    bool knot;

    /**
     * A cell is within simulation if it has neighbours on all sides i.e. if it is not at the border
     */
    bool inSimulation;

    /**
     * is true if the cell is in the center of the cell compound.
     * The radius of "center" is defined by the parameter initialRadius
     */
    bool inCentre;

    /**
     * MesenchymeThickness indicates how many mesenchyme cells lay under the epithelium cell
     */
    int mesenchymeThickness;

    /**
     * This vector contains the x coordinates of all voronoi vertices around the cell centre
     */
    std::vector<double> borderPointsX;

    /**
     * This vector contains the y coordinates of all voronoi vertices around the cell centre
     */
    std::vector<double> borderPointsY;

    /**
     * This vector contains the z coordinates of all voronoi vertices around the cell centre
     */
    std::vector<double> borderPointsZ;

    /**
     * Contains the lengths of the polygon sides. Their sum is the perimeter of the polygon
     */
    std::vector<double> perimeterParts;

    /**
     * Contains the triangles of the polygon area. Their sum is the area of the polygon
     */
    std::vector<double> areaParts;

    /**
     * Perimeter of the polygon (cell)
     */
    double perimeter;

    /**
     * Area of the polygon (cell)
     */
    double cellArea;

public:
    //Getter
    double getX() const;

    double getY() const;

    double getZ() const;

    int getID() const;

    double getDiffState() const;

    bool isKnotCell() const;

    std::vector<int> getNeighbours() const;

    int getMesenchymeThickness() const;

    bool isInSimulation() const;

    bool isInCentre() const;

    const std::vector<double> &getBorderPointsX() const;

    const std::vector<double> &getBorderPointsY() const;

    const std::vector<double> &getBorderPointsZ() const;

    const std::vector<double> &getPerimeterParts() const;

    const std::vector<double> &getAreaParts() const;

    double getPerimeter() const;

    double getCellArea() const;

    std::vector<std::vector<double>> &getProteinConcentrations();

    const std::vector<std::vector<double>> &getTempProteinConcentrations() const;

    double getTempX() const;

    double getTempY() const;

    double getTempZ() const;

    //Setter
    void setX(double x);

    void setY(double y);

    void setZ(double z);

    /**
     * Increments the variable tempX by a certain amount
     * @param tempX
     */
    void addTempX(double tempX);

    /**
     * Multiplies the variable tempX by a certain amount
     * @param tempX
     */
    void multiplyTempX(double tempX);

    void addTempY(double tempY);

    void addTempZ(double tempZ);

    void multiplyTempZ(double tempZ);

    void setID(int ID);

    void setDiffState(double diffState);

    /**
     * Increments the variable diffState by a certain amount
     * @param addedDiffState
     */
    void addDiffState(double addedDiffState);

    void setKnotCell(bool knot);

    void setNeighbour(int neighbourID);

    void setMesenchymeThickness(int mesenchymeThickness);

    void setInSimulation(bool inSimulation);

    void setInCentre(bool inCentre);

    /**
     * Sets a new border point
     * @param axis x,y, or z
     * @param point value of this coordinate
     */
    void newBorderPoint(char axis, double point);

    void replaceBorderPoint(char axis, double point, int position);

    void newPerimeterPart(double perimeterPart);

    void newAreaPart(double areaPart);

    void setPerimeter(double perimeter);

    void setCellArea(double cellArea);

    /**
     * Increments the variable proteinConcentration[protein][layer] by newConcentration
     *
     * @param protein
     * @param layer
     * @param newConcentration
     */
    void addProteinConcentration(int protein, int layer, double newConcentration);

    /**
     * Increments the variable tempConcentrations[protein][layer] by addedConcentration
     * @param protein
     * @param layer
     * @param addedConcentration
     */
    void addTempConcentration(int protein, int layer, double addedConcentration);

    void setProteinConcentration(int protein, int layer, double newConcentration);

    //Constructor
    Cell(double x, double y, int z, int ID);

    //Editors
    void deleteNeighbour(int neighbour);

    /**
     * sets the vector tempConcentrations to 0
     */
    void resetTempProteinConcentrations();

    /**
     * sets the vector tempCoordinates to 0
     */
    void resetTempCoordinates();

    /**
     * Calculates the new position of the cell by adding the temp coordinates multiplied with delta
     * @param delta
     */
    void updateCoordinates(double delta);

    //Printer
    static void printCellBorders(std::vector<Cell> cells, int nrCellsInSimulation);


};


#endif //TOOTHMAKER_CELL_H
