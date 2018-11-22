//
// Created by Stefanie on 30.07.2018.
//

#include <iostream>
#include "Cell.h"


//Getter
double Cell::getX() const {
    return x;
}

double Cell::getY() const {
    return y;
}

double Cell::getZ() const {
    return z;
}

double Cell::getTempX() const {
    return tempX;
}

double Cell::getTempY() const {
    return tempY;
}

double Cell::getTempZ() const {
    return tempZ;
}

const std::vector<double> &Cell::getOriginalDistances() const {
    return originalDistances;
}

int Cell::getID() const {
    return ID;
}

double Cell::getDiffState() const {
    return diffState;
}

std::vector<int> Cell::getNeighbours() const {
    return neighbours;
}

bool Cell::isKnotCell() const {
    return knot;
}

bool Cell::isInSimulation() const {
    return inSimulation;
}

bool Cell::isInCentre() const {
    return inCentre;
}

int Cell::getMesenchymeThickness() const {
    return mesenchymeThickness;
}

std::vector<std::vector<double>> Cell::getBorderPoints() const {
    return borderPoints;
}

std::vector<std::vector<double>> Cell::getMarginPoints() const {
    return marginPoints;
}

const std::vector<double> &Cell::getPerimeterParts() const {
    return perimeterParts;
}

const std::vector<double> &Cell::getAreaParts() const {
    return areaParts;
}

double Cell::getPerimeter() const {
    return perimeter;
}

double Cell::getCellArea() const {
    return cellArea;
}

double Cell::getMargin() const {
    return margin;
}

std::vector<std::vector<double>> &Cell::getProteinConcentrations() {
    return proteinConcentrations;
}

const std::vector<std::vector<double>> &Cell::getTempProteinConcentrations() const {
    return tempProteinConcentrations;
}

//Setter

void Cell::addX(double newX) {
    Cell::x += newX;
}

void Cell::addY(double newY) {
    Cell::y += newY;
}

void Cell::addZ(double newZ) {
    Cell::z += newZ;
}

void Cell::setID(int newID) {
    Cell::ID = newID;
}

void Cell::addDiffState(double addedDiffState) {
    Cell::diffState += addedDiffState;
    if (diffState > 1) {
        diffState = 1;
    }
}

void Cell::setKnotCell(bool knot) {
    Cell::knot = knot;
}

void Cell::addNeighbour(int neighbourID) {
    Cell::neighbours.push_back(neighbourID);
}

void Cell::setNeighbour(int position, int newNeighbourID) {
    neighbours[position] = newNeighbourID;
}

void Cell::replaceNeighbour(int oldNeighbourID, int newNeighbourID) {
    /*for (auto neighbour : Cell::neighbours) {
        if (neighbour == oldNeighbourID) {
            neighbour = newNeighbourID;
            return;
        }
    }*/

    for (int neighbour = 0; neighbour < Cell::neighbours.size(); ++neighbour) {
        if (Cell::neighbours[neighbour] == oldNeighbourID) {
            setNeighbour(neighbour, newNeighbourID);
            return;
        }
    }
}

void Cell::insertNeighbour(int newNeighbourID, int position) {
    Cell::neighbours.insert(Cell::neighbours.begin() + position, newNeighbourID);
}

void Cell::setInSimulation(bool inSimulation) {
    Cell::inSimulation = inSimulation;
}

void Cell::setInCentre(bool inCentre) {
    Cell::inCentre = inCentre;
}

void Cell::newBorderPoint(double x, double y, double z) {
    std::vector<double> newPoint = {x, y, z};
    borderPoints.push_back(newPoint);
}

void Cell::newMarginPoint(double x, double y, double z) {
    std::vector<double> newPoint = {x, y, z};
    marginPoints.push_back(newPoint);
}

void Cell::newPerimeterPart(double perimeterPart) {
    perimeterParts.push_back(perimeterPart);
}

void Cell::newAreaPart(double areaPart) {
    areaParts.push_back(areaPart);
}

void Cell::setPerimeter(double perimeter) {
    Cell::perimeter = perimeter;
}

void Cell::setCellArea(double cellArea) {
    Cell::cellArea = cellArea;
}

void Cell::setMargin(double margin) {
    Cell::margin = margin;
}

void Cell::setMarginArea(double area) {
    Cell::marginArea = area;
}

void Cell::addProteinConcentration(int protein, int layer, double addedConcentration) {
    proteinConcentrations[protein][layer] += addedConcentration;
}

void Cell::addTempConcentration(int protein, int layer, double addedConcentration) {
    tempProteinConcentrations[protein][layer] += addedConcentration;
}

void Cell::setProteinConcentration(int protein, int layer, double newConcentration) {
    proteinConcentrations[protein][layer] = newConcentration;
}

void Cell::addTempX(double tempX) {
    Cell::tempX += tempX;
}

void Cell::addTempY(double tempY) {
    Cell::tempY += tempY;
}

void Cell::addTempZ(double tempZ) {
    Cell::tempZ += tempZ;
}

void Cell::multiplyTempX(double tempX) {
    Cell::tempX = Cell::tempX * tempX;
}

void Cell::multiplyTempZ(double tempZ) {
    Cell::tempZ = Cell::tempZ * tempZ;
}

void Cell::addOriginalDistance(double distance, int position) {
    Cell::originalDistances.insert(Cell::originalDistances.begin() + position, distance);
}

void Cell::replaceOriginalDistance(double distance, int position) {
    originalDistances[position] = distance;
}

//Constructor
Cell::Cell(double x, double y, double z, int ID) : x(x), y(y), z(z), ID(ID) {
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
}

//Editors

void Cell::deleteNeighbour(int neighbour) {
    neighbours.erase(neighbours.begin() + neighbour);
}

void Cell::resetTempProteinConcentrations() {
    for (int layer = 0; layer < mesenchymeThickness; ++layer) {
        for (int protein = 0; protein < 4; ++protein) {
            tempProteinConcentrations[protein][layer] = 0;
        }
    }
}

void Cell::resetTempCoordinates() {
    tempX = 0;
    tempY = 0;
    tempZ = 0;
}

void Cell::deleteBorderPoints() {
    Cell::borderPoints.clear();
}

void Cell::deletePerimeterParts() {
    Cell::perimeterParts.clear();
}

void Cell::deleteAreaParts() {
    Cell::areaParts.clear();
}

void Cell::deleteMarginPoints() {
    Cell::marginPoints.clear();
}

void Cell::updateCoordinates(double delta) {
    // There cannot be any force in negative z-direction due to the pressure of the stelate
    if (Cell::tempZ < 0) {
        Cell::tempZ = 0;
    }

    //There is no force at all in z-direction, if the cell is an EK-cell
    if (Cell::isKnotCell()) {
        Cell::tempZ = 0;
    }

    //Apply the forces on the positions
    Cell::x += Cell::tempX * delta;
    Cell::y += Cell::tempY * delta;
    Cell::z += Cell::tempZ * delta;
}















