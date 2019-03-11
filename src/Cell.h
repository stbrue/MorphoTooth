//
// Created by Stefanie on 30.07.2018.
//

#ifndef TOOTHMAKER_CELL_H
#define TOOTHMAKER_CELL_H

#include <vector>
#include "consts.h"
#include "ModelParams.h"
#include <iostream>

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
    double originalDistances[maxNrOfNeighbours];

    /**
     * The ID of a cell is identical with their index in the vector containing all cells
     */
    int ID;

    /**
     * contains all neighbours (their ID). The order is relevant (clockwise order)
     */
    int neighbours[maxNrOfNeighbours];

    int nrOfNeighbours;

    /**
     * the differentiation state is a variable indicating the "age" of a cell
     */
    double diffState;

    /**
     * proteinConcentrations[protein][layer]
     * Proteins: Act, Inh, Sec
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

    /**
     * Holds all origianl  genetic information (model parameters) -> Genome
     */
    ModelParams originalModelParams;

    /**
     * Holds the modified (noise affected) genetic information
     */
    ModelParams modelParams;

public:
    //Getter
    ModelParams getModelParams() const;

    ModelParams getOriginalParams() const;

    double getX() const;

    double getTempX() const;

    double getY() const;

    double getTempY() const;

    double getZ() const;

    double getTempZ() const;

    double *getOriginalDistances();

    int getID() const;

    double getDiffState() const;

    bool isKnotCell() const;

    int *getNeighbours();

    int getNrOfNeighbours() const;

    int getMesenchymeThickness() const;

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

    const double getModelParamValue(std::string paramName) const;

    const double getOriginalModelParamValue(std::string paramName) const;


    //Setter

    void setX(double X);

    void setY(double Y);

    void setZ(double Z);

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

    void incrementNrOfNeighbours();

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

    void setModelParams(ModelParams modelParams);

    void setOriginalModelParams(ModelParams originalModelParams);

    void changeModelParameter(std::string const &paramName, double newValue);

    //Constructor
    Cell();

    //Editors

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
    void updateCoordinates();

    void checkTempCoordinatesForLimit(double maxMovement);

    void printTempConcentrations();

};

inline ModelParams Cell::getModelParams() const {
    return modelParams;
}

inline ModelParams Cell::getOriginalParams() const {
    return originalModelParams;
}

inline double Cell::getX() const {
    return x;
}

inline double Cell::getY() const {
    return y;
}

inline double Cell::getZ() const {
    return z;
}

inline double Cell::getTempX() const {
    return tempX;
}

inline double Cell::getTempY() const {
    return tempY;
}

inline double Cell::getTempZ() const {
    return tempZ;
}

inline double *Cell::getOriginalDistances() {
    double *originalDistances = Cell::originalDistances;
    return originalDistances;
}

inline int Cell::getID() const {
    return ID;
}

inline double Cell::getDiffState() const {
    return diffState;
}

inline int *Cell::getNeighbours() {
    int *neighbours = Cell::neighbours;
    return neighbours;
}

inline int Cell::getNrOfNeighbours() const {
    return nrOfNeighbours;
}

inline bool Cell::isKnotCell() const {
    return knot;
}

inline bool Cell::isInCentre() const {
    return inCentre;
}

inline int Cell::getMesenchymeThickness() const {
    return mesenchymeThickness;
}

inline std::vector<std::vector<double>> Cell::getBorderPoints() const {
    return borderPoints;
}

inline std::vector<std::vector<double>> Cell::getMarginPoints() const {
    return marginPoints;
}

inline const std::vector<double> &Cell::getPerimeterParts() const {
    return perimeterParts;
}

inline const std::vector<double> &Cell::getAreaParts() const {
    return areaParts;
}

inline double Cell::getPerimeter() const {
    return perimeter;
}

inline double Cell::getCellArea() const {
    return cellArea;
}

inline double Cell::getMargin() const {
    return margin;
}

inline std::vector<std::vector<double>> &Cell::getProteinConcentrations() {
    return proteinConcentrations;
}

inline const std::vector<std::vector<double>> &Cell::getTempProteinConcentrations() const {
    return tempProteinConcentrations;
}

inline const double Cell::getModelParamValue(std::string paramName) const {
    if (paramName == "ActDiffusion" || paramName == "actDiffusion") {
        return modelParams.ActDiffusion;
    } else if (paramName == "InhDiffusion" || paramName == "inhDiffusion") {
        return modelParams.InhDiffusion;
    } else if (paramName == "SecDiffusion" || paramName == "secDiffusion") {
        return modelParams.SecDiffusion;
    } else if (paramName == "delta" || paramName == "Delta") {
        return modelParams.delta;
    } else if (paramName == "act" || paramName == "Act") {
        return modelParams.act;
    } else if (paramName == "inh" || paramName == "Inh") {
        return modelParams.inh;
    } else if (paramName == "EpithelialDegradation" || paramName == "epithalialDegradation") {
        return modelParams.epithelialDegradation;
    } else if (paramName == "MesenchymeDegradation" || paramName == "mesenchymeDegradation") {
        return modelParams.mesenchymeDegradation;
    } else if (paramName == "int" || paramName == "Int") {
        return modelParams.inT;
    } else if (paramName == "set" || paramName == "Set") {
        return modelParams.set;
    } else if (paramName == "sec" || paramName == "Sec") {
        return modelParams.sec;
    } else if (paramName == "lbi" || paramName == "Lbi") {
        return modelParams.lbi;
    } else if (paramName == "bbi" || paramName == "Bbi") {
        return modelParams.bbi;
    } else if (paramName == "swi" || paramName == "Swi") {
        return modelParams.swi;
    } else if (paramName == "dff" || paramName == "Dff") {
        return modelParams.dff;
    } else if (paramName == "egr" || paramName == "Egr") {
        return modelParams.egr;
    } else if (paramName == "mgr" || paramName == "Mgr") {
        return modelParams.mgr;
    } else if (paramName == "dgr" || paramName == "Dgr") {
        return modelParams.dgr;
    } else if (paramName == "rep" || paramName == "Rep") {
        return modelParams.rep;
    } else if (paramName == "adh" || paramName == "Adh") {
        return modelParams.adh;
    } else if (paramName == "ntr" || paramName == "Ntr") {
        return modelParams.ntr;
    } else if (paramName == "bwi" || paramName == "Bwi") {
        return modelParams.bwi;
    } else if (paramName == "abi" || paramName == "Abi") {
        return modelParams.abi;
    } else if (paramName == "pbi" || paramName == "Pbi") {
        return modelParams.pbi;
    } else if (paramName == "bgr" || paramName == "Bgr") {
        return modelParams.bgr;
    } else if (paramName == "boy" || paramName == "Boy") {
        return modelParams.boy;
    } else {
        std::cout << "Could not get parameter value" << std::endl;
    }
}


inline const double Cell::getOriginalModelParamValue(std::string paramName) const {
    if (paramName == "ActDiffusion" || paramName == "actDiffusion") {
        return originalModelParams.ActDiffusion;
    } else if (paramName == "InhDiffusion" || paramName == "inhDiffusion") {
        return originalModelParams.InhDiffusion;
    } else if (paramName == "SecDiffusion" || paramName == "secDiffusion") {
        return originalModelParams.SecDiffusion;
    } else if (paramName == "delta" || paramName == "Delta") {
        return originalModelParams.delta;
    } else if (paramName == "act" || paramName == "Act") {
        return originalModelParams.act;
    } else if (paramName == "inh" || paramName == "Inh") {
        return originalModelParams.inh;
    } else if (paramName == "epithelialDegradation" || paramName == "EpithelialDegradation") {
        return originalModelParams.epithelialDegradation;
    } else if (paramName == "mesenchymeDegradation" || paramName == "MesenchymeDegradation") {
        return originalModelParams.mesenchymeDegradation;
    } else if (paramName == "int" || paramName == "Int") {
        return originalModelParams.inT;
    } else if (paramName == "set" || paramName == "Set") {
        return originalModelParams.set;
    } else if (paramName == "sec" || paramName == "Sec") {
        return originalModelParams.sec;
    } else if (paramName == "lbi" || paramName == "Lbi") {
        return originalModelParams.lbi;
    } else if (paramName == "bbi" || paramName == "Bbi") {
        return originalModelParams.bbi;
    } else if (paramName == "swi" || paramName == "Swi") {
        return originalModelParams.swi;
    } else if (paramName == "dff" || paramName == "Dff") {
        return originalModelParams.dff;
    } else if (paramName == "egr" || paramName == "Egr") {
        return originalModelParams.egr;
    } else if (paramName == "mgr" || paramName == "Mgr") {
        return originalModelParams.mgr;
    } else if (paramName == "dgr" || paramName == "Dgr") {
        return originalModelParams.dgr;
    } else if (paramName == "rep" || paramName == "Rep") {
        return originalModelParams.rep;
    } else if (paramName == "adh" || paramName == "Adh") {
        return originalModelParams.adh;
    } else if (paramName == "ntr" || paramName == "Ntr") {
        return originalModelParams.ntr;
    } else if (paramName == "bwi" || paramName == "Bwi") {
        return originalModelParams.bwi;
    } else if (paramName == "abi" || paramName == "Abi") {
        return originalModelParams.abi;
    } else if (paramName == "pbi" || paramName == "Pbi") {
        return originalModelParams.pbi;
    } else if (paramName == "bgr" || paramName == "Bgr") {
        return originalModelParams.bgr;
    } else if (paramName == "boy" || paramName == "Boy") {
        return originalModelParams.boy;
    } else {
        std::cout << "Could not get parameter value" << std::endl;
    }
}


//Setter

inline void Cell::setX(double X) {
    Cell::x = X;
}

inline void Cell::setY(double Y) {
    Cell::y = Y;
}

inline void Cell::setZ(double Z) {
    Cell::z = Z;
}

inline void Cell::addX(double newX) {
    Cell::x += newX;
}

inline void Cell::addY(double newY) {
    Cell::y += newY;
}

inline void Cell::addZ(double newZ) {
    Cell::z += newZ;
}

inline void Cell::setID(int newID) {
    Cell::ID = newID;
}

inline void Cell::addDiffState(double addedDiffState) {
    Cell::diffState += addedDiffState;
    if (diffState > 1) {
        diffState = 1;
    }
}

inline void Cell::setKnotCell(bool knot) {
    Cell::knot = knot;
}

inline void Cell::addNeighbour(int neighbourID) {
    Cell::neighbours[Cell::nrOfNeighbours] = neighbourID;
    Cell::incrementNrOfNeighbours();
}

inline void Cell::incrementNrOfNeighbours() {
    Cell::nrOfNeighbours += 1;
}

inline void Cell::setNeighbour(int position, int newNeighbourID) {
    neighbours[position] = newNeighbourID;
}

inline void Cell::replaceNeighbour(int oldNeighbourID, int newNeighbourID) {
    /*for (auto neighbour : Cell::neighbours) {
        if (neighbour == oldNeighbourID) {
            neighbour = newNeighbourID;
            return;
        }
    }*/

    for (int neighbour = 0; neighbour < maxNrOfNeighbours; ++neighbour) {
        if (Cell::neighbours[neighbour] == oldNeighbourID) {
            setNeighbour(neighbour, newNeighbourID);
            return;
        }
    }
}

inline void Cell::insertNeighbour(int newNeighbourID, int position) {
    int tempArray[maxNrOfNeighbours];

    // write all values of the array before "position" into tempArray
    for (int index = 0; index < position; ++index) {
        tempArray[index] = Cell::neighbours[index];
    }

    // write all remaining values from the array one position later into tempArray
    for (int index = position; index < maxNrOfNeighbours -
                                       1; ++index) { // -1 because we have [position + 1]
        tempArray[index + 1] = Cell::neighbours[index];
    }
    // replace the value at "position" with the new value
    tempArray[position] = newNeighbourID;

    // replace the array with the tempArray
    for (int index = 0; index < maxNrOfNeighbours; ++index) {
        Cell::neighbours[index] = tempArray[index];
    }

    Cell::incrementNrOfNeighbours();
}

inline void Cell::setInSimulation(bool inSimulation) {
    Cell::inSimulation = inSimulation;
}

inline void Cell::setInCentre(bool inCentre) {
    Cell::inCentre = inCentre;
}

inline void Cell::newBorderPoint(double x, double y, double z) {
    std::vector<double> newPoint = {x, y, z};
    borderPoints.push_back(newPoint);
}

inline void Cell::newMarginPoint(double x, double y, double z) {
    std::vector<double> newPoint = {x, y, z};
    marginPoints.push_back(newPoint);
}

inline void Cell::newPerimeterPart(double perimeterPart) {
    perimeterParts.push_back(perimeterPart);
}

inline void Cell::newAreaPart(double areaPart) {
    areaParts.push_back(areaPart);
}

inline void Cell::setPerimeter(double perimeter) {
    Cell::perimeter = perimeter;
}

inline void Cell::setCellArea(double cellArea) {
    Cell::cellArea = cellArea;
}

inline void Cell::setMargin(double margin) {
    Cell::margin = margin;
}

inline void Cell::setMarginArea(double area) {
    Cell::marginArea = area;
}

inline void Cell::setModelParams(ModelParams modelParams) {
    Cell::modelParams.delta = modelParams.delta;
    Cell::modelParams.act = modelParams.act;
    Cell::modelParams.inh = modelParams.inh;
    Cell::modelParams.epithelialDegradation = modelParams.epithelialDegradation;
    Cell::modelParams.mesenchymeDegradation = modelParams.mesenchymeDegradation;
    Cell::modelParams.inT = modelParams.inT;
    Cell::modelParams.set = modelParams.set;
    Cell::modelParams.sec = modelParams.sec;
    Cell::modelParams.lbi = modelParams.lbi;
    Cell::modelParams.bbi = modelParams.bbi;
    Cell::modelParams.swi = modelParams.swi;
    Cell::modelParams.dff = modelParams.dff;
    Cell::modelParams.egr = modelParams.egr;
    Cell::modelParams.mgr = modelParams.mgr;
    Cell::modelParams.dgr = modelParams.dgr;
    Cell::modelParams.rep = modelParams.rep;
    Cell::modelParams.adh = modelParams.adh;
    Cell::modelParams.ntr = modelParams.ntr;
    Cell::modelParams.bwi = modelParams.bwi;
    Cell::modelParams.abi = modelParams.abi;
    Cell::modelParams.pbi = modelParams.pbi;
    Cell::modelParams.bgr = modelParams.bgr;
    Cell::modelParams.ActDiffusion = modelParams.ActDiffusion;
    Cell::modelParams.InhDiffusion = modelParams.InhDiffusion;
    Cell::modelParams.SecDiffusion = modelParams.SecDiffusion;
}

inline void Cell::setOriginalModelParams(ModelParams originalModelParams) {
    Cell::originalModelParams.delta = originalModelParams.delta;
    Cell::originalModelParams.act = originalModelParams.act;
    Cell::originalModelParams.inh = originalModelParams.inh;
    Cell::originalModelParams.epithelialDegradation = originalModelParams.epithelialDegradation;
    Cell::originalModelParams.mesenchymeDegradation = originalModelParams.mesenchymeDegradation;
    Cell::originalModelParams.inT = originalModelParams.inT;
    Cell::originalModelParams.set = originalModelParams.set;
    Cell::originalModelParams.sec = originalModelParams.sec;
    Cell::originalModelParams.lbi = originalModelParams.lbi;
    Cell::originalModelParams.bbi = originalModelParams.bbi;
    Cell::originalModelParams.swi = originalModelParams.swi;
    Cell::originalModelParams.dff = originalModelParams.dff;
    Cell::originalModelParams.egr = originalModelParams.egr;
    Cell::originalModelParams.mgr = originalModelParams.mgr;
    Cell::originalModelParams.dgr = originalModelParams.dgr;
    Cell::originalModelParams.rep = originalModelParams.rep;
    Cell::originalModelParams.adh = originalModelParams.adh;
    Cell::originalModelParams.ntr = originalModelParams.ntr;
    Cell::originalModelParams.bwi = originalModelParams.bwi;
    Cell::originalModelParams.abi = originalModelParams.abi;
    Cell::originalModelParams.pbi = originalModelParams.pbi;
    Cell::originalModelParams.bgr = originalModelParams.bgr;
    Cell::originalModelParams.ActDiffusion = originalModelParams.ActDiffusion;
    Cell::originalModelParams.InhDiffusion = originalModelParams.InhDiffusion;
    Cell::originalModelParams.SecDiffusion = originalModelParams.SecDiffusion;
}

inline void Cell::changeModelParameter(std::string const &paramName, double newValue) {
    if (paramName == "ActDiffusion" || paramName == "actDiffusion") {
        modelParams.ActDiffusion = newValue;
        return;
    } else if (paramName == "InhDiffusion" || paramName == "inhDiffusion") {
        modelParams.InhDiffusion = newValue;
        return;
    } else if (paramName == "SecDiffusion" || paramName == "secDiffusion") {
        modelParams.SecDiffusion = newValue;
        return;
    } else if (paramName == "delta" || paramName == "Delta") {
        modelParams.delta = newValue;
        return;
    } else if (paramName == "act" || paramName == "Act") {
        modelParams.act = newValue;
        return;
    } else if (paramName == "inh" || paramName == "Inh") {
        modelParams.inh = newValue;
        return;
    } else if (paramName == "epithelialDegradation" || paramName == "EpithelialDegradation") {
        modelParams.epithelialDegradation = newValue;
        return;
    } else if (paramName == "mesenchymeDegradation" || paramName == "MesenchymeDegradation") {
        modelParams.mesenchymeDegradation = newValue;
        return;
    } else if (paramName == "int" || paramName == "Int") {
        modelParams.inT = newValue;
        return;
    } else if (paramName == "set" || paramName == "Set") {
        modelParams.set = newValue;
        return;
    } else if (paramName == "sec" || paramName == "Sec") {
        modelParams.sec = newValue;
        return;
    } else if (paramName == "lbi" || paramName == "Lbi") {
        modelParams.lbi = newValue;
        return;
    } else if (paramName == "bbi" || paramName == "Bbi") {
        modelParams.bbi = newValue;
        return;
    } else if (paramName == "swi" || paramName == "Swi") {
        modelParams.swi = newValue;
        return;
    } else if (paramName == "dff" || paramName == "Dff") {
        modelParams.dff = newValue;
        return;
    } else if (paramName == "egr" || paramName == "Egr") {
        modelParams.egr = newValue;
        return;
    } else if (paramName == "mgr" || paramName == "Mgr") {
        modelParams.mgr = newValue;
        return;
    } else if (paramName == "dgr" || paramName == "Dgr") {
        modelParams.dgr = newValue;
        return;
    } else if (paramName == "rep" || paramName == "Rep") {
        modelParams.rep = newValue;
        return;
    } else if (paramName == "adh" || paramName == "Adh") {
        modelParams.adh = newValue;
        return;
    } else if (paramName == "ntr" || paramName == "Ntr") {
        modelParams.ntr = newValue;
        return;
    } else if (paramName == "bwi" || paramName == "Bwi") {
        modelParams.bwi = newValue;
        return;
    } else if (paramName == "abi" || paramName == "Abi") {
        modelParams.abi = newValue;
        return;
    } else if (paramName == "pbi" || paramName == "Pbi") {
        modelParams.pbi = newValue;
        return;
    } else if (paramName == "bgr" || paramName == "Bgr") {
        modelParams.bgr = newValue;
        return;
    } else if (paramName == "boy" || paramName == "Boy") {
        modelParams.boy = newValue;
        return;
    } else if (paramName == "epithelialDegradation" || paramName == "EpithelialDegradation") {
        modelParams.epithelialDegradation = newValue;
        return;
    } else if (paramName == "mesenchymeDegradation" || paramName == "MesenchymeDegradation") {
        modelParams.mesenchymeDegradation = newValue;
        return;
    } else {
        std::cout << "Parameter " << paramName << " could not be changed" << std::endl;
    }
}


inline void Cell::addProteinConcentration(int protein, int layer, double addedConcentration) {
    proteinConcentrations[protein][layer] += addedConcentration;
}

inline void Cell::addTempConcentration(int protein, int layer, double addedConcentration) {
    tempProteinConcentrations[protein][layer] += addedConcentration;
}

inline void Cell::setProteinConcentration(int protein, int layer, double newConcentration) {
    proteinConcentrations[protein][layer] = newConcentration;
}

inline void Cell::addTempX(double tempX) {
    Cell::tempX += tempX;
}

inline void Cell::addTempY(double tempY) {
    Cell::tempY += tempY;
}

inline void Cell::addTempZ(double tempZ) {
    Cell::tempZ += tempZ;
}

inline void Cell::multiplyTempX(double tempX) {
    Cell::tempX = Cell::tempX * tempX;
}

inline void Cell::multiplyTempZ(double tempZ) {
    Cell::tempZ = Cell::tempZ * tempZ;
}

inline void Cell::addOriginalDistance(double distance, int position) {
    int tempArray[maxNrOfNeighbours];

    // write all values of the array before "position" into tempArray
    for (int index = 0; index < position; ++index) {
        tempArray[index] = Cell::originalDistances[index];
    }

    // write all remaining values from the array one position later into tempArray
    for (int index = position; index < maxNrOfNeighbours -
                                       1; ++index) { // -1 because we have [position + 1]
        tempArray[index + 1] = Cell::originalDistances[index];
    }
    // replace the value at "position" with the new value
    tempArray[position] = distance;

    // replace the array with the tempArray
    for (int index = 0; index < maxNrOfNeighbours; ++index) {
        Cell::originalDistances[index] = tempArray[index];
    }
}

inline void Cell::replaceOriginalDistance(double distance, int position) {
    originalDistances[position] = distance;
}

inline void Cell::checkTempCoordinatesForLimit(double maxMovement) {
    if (maxMovement == 0) {
        return;
    }
    if (tempX > maxMovement) {
        tempX = maxMovement;
    }
    if (tempY > maxMovement) {
        tempY = maxMovement;
    }
    if (tempZ > maxMovement) {
        tempZ = maxMovement;
    }
}

inline void Cell::printTempConcentrations() {
    std::cout << "Act: " << tempProteinConcentrations[PAct][LEpithelium];
    std::cout << "Inh: " << tempProteinConcentrations[PInh][LEpithelium];
    std::cout << "Sec: " << tempProteinConcentrations[PSec][LEpithelium] << std::endl;
}

//Constructor
inline Cell::Cell() {
    knot = false;
    inSimulation = false;
    inCentre = false;
    mesenchymeThickness = 4;
    diffState = 0;
    tempX = 0;
    tempY = 0;
    tempZ = 0;
    //Set Concentrations to 0 (in each layer)
    for (int layer = 0; layer < mesenchymeThickness; ++layer) {
        std::vector<double> tempv;
        for (int protein = 0; protein < 4; ++protein) {
            tempv.push_back(0);
        }
        proteinConcentrations.push_back(tempv);
        tempProteinConcentrations.push_back(tempv);
    }
    perimeter = 0;
    cellArea = 0;
    margin = 0;
    marginArea = 0;
    nrOfNeighbours = 0;
    for (int neighbour = 0; neighbour < maxNrOfNeighbours; ++neighbour) {
        neighbours[neighbour] = -1;
    }
}

//Editors

inline void Cell::resetTempProteinConcentrations() {
    for (int layer = 0; layer < mesenchymeThickness; ++layer) {
        for (int protein = 0; protein < 4; ++protein) {
            tempProteinConcentrations[protein][layer] = 0;
        }
    }
}

inline void Cell::resetTempCoordinates() {
    tempX = 0;
    tempY = 0;
    tempZ = 0;
}

inline void Cell::deleteBorderPoints() {
    Cell::borderPoints.clear();
}

inline void Cell::deletePerimeterParts() {
    Cell::perimeterParts.clear();
}

inline void Cell::deleteAreaParts() {
    Cell::areaParts.clear();
}

inline void Cell::deleteMarginPoints() {
    Cell::marginPoints.clear();
}

inline void Cell::updateCoordinates() {
    // There cannot be any force in negative z-direction due to the pressure of the stelate
    if (Cell::tempZ < 0) {
        Cell::tempZ = 0;
    }

    //There is no force at all in z-direction, if the cell is an EK-cell
    if (Cell::isKnotCell()) {
        Cell::tempZ = 0;
    }

    //Apply the forces on the positions
    Cell::x += Cell::tempX * Cell::modelParams.delta;
    Cell::y += Cell::tempY * Cell::modelParams.delta;
    Cell::z += Cell::tempZ * Cell::modelParams.delta;
}

#endif //TOOTHMAKER_CELL_H
