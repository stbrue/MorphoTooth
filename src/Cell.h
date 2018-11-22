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
     * This are the distances the cell has to its neighbours when it (or a new neighbour) is inserted into the grid
     */
    std::vector<double> originalDistances;

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
    std::vector<std::vector<double>> borderPoints;

    /**
     * marginPoints contains these two points that make the edge of the cell which is part of the border of the
     * whole tissue. They are the result, in contrast to the other cell border points, of the midpoint of only two
     * instead of three points.
     * Obviously only cells on the tissue border have such points.
     */
    std::vector<std::vector<double>> marginPoints;

    /**
     * margin is the length of the cell border that is part of the tissue border (length between the two marginPoints
     * Obviously only cells on the tissue border have such a margin length
     */
    double margin;

    /**
     * This is the area of the triangle centre-marginPoint1-marginPoint2. It represents the area made of the part of the
     * cell that is next to the tissue border.
     * It is part of the whole cellArea and is used for horizontal diffusion when there is a sink at the tissue border
     * Obviously only cells on the tissue border have such a marginArea.
     */
    double marginArea;

    /**
     * Contains the lengths of the polygon sides. Their sum (together with the margin, if the cell is at the tissue
     * border) is the perimeter of the polygon
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

    double getTempX() const;

    double getY() const;

    double getTempY() const;

    double getZ() const;

    double getTempZ() const;

    const std::vector<double> &getOriginalDistances() const;

    int getID() const;

    double getDiffState() const;

    bool isKnotCell() const;

    std::vector<int> getNeighbours() const;

    int getMesenchymeThickness() const;

    bool isInSimulation() const;

    bool isInCentre() const;

    std::vector<std::vector<double>> getBorderPoints() const;

    std::vector<std::vector<double>> getMarginPoints() const;

    const std::vector<double> &getPerimeterParts() const;

    const std::vector<double> &getAreaParts() const;

    double getPerimeter() const;

    double getCellArea() const;

    double getMargin() const;

    std::vector<std::vector<double>> &getProteinConcentrations();

    const std::vector<std::vector<double>> &getTempProteinConcentrations() const;


    //Setter

    void addX(double newX);

    void addY(double newY);

    void addZ(double newZ);

    void setID(int newID);

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

    void addOriginalDistance(double distance, int position);

    void replaceOriginalDistance(double distance, int position);

    /**
     * Increments the variable diffState by a certain amount
     * @param addedDiffState
     */
    void addDiffState(double addedDiffState);

    void setKnotCell(bool knot);

    void addNeighbour(int neighbourID);

    void setNeighbour(int position, int newNeighbourID);

    void replaceNeighbour(int oldNeighbourID, int newNeighbourID);

    void insertNeighbour(int newNeighbourID, int position);

    void setInSimulation(bool inSimulation);

    void setInCentre(bool inCentre);

    /**
     * Sets a new border point
     */
    void newBorderPoint(double x, double y, double z);

    void newPerimeterPart(double perimeterPart);

    void newAreaPart(double areaPart);

    void setPerimeter(double perimeter);

    void setCellArea(double cellArea);

    void setMargin(double margin);

    void setMarginArea(double area);

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

    void newMarginPoint(double x, double y, double z);

    //Constructor
    Cell(double x, double y, double z, int ID);

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
     * Deletes all the border points
     */
    void deleteBorderPoints();

    /**
     * Deletes all the perimeter parts
     */
    void deletePerimeterParts();

    /**
     * Deletes all the area parts
     */
    void deleteAreaParts();

    void deleteMarginPoints();

    /**
     * Calculates the new position of the cell by adding the temp coordinates multiplied with delta
     * @param delta
     */
    void updateCoordinates(double delta);

};


#endif //TOOTHMAKER_CELL_H
