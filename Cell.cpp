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
    if (knot){
        return true;
    }
    else
    {
        return false;
    }
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

const std::vector<double> &Cell::getBorderPointsX() const {
    return borderPointsX;
}

const std::vector<double> &Cell::getBorderPointsY() const {
    return borderPointsY;
}

const std::vector<double> &Cell::getBorderPointsZ() const {
    return borderPointsZ;
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

const std::vector<std::vector<double>> &Cell::getProteinConcentrations() const {
    return proteinConcentrations;
}

const std::vector<std::vector<double>> &Cell::getTempProteinConcentrations() const {
    return tempProteinConcentrations;
}

//Setter
void Cell::setX(double x) {
    Cell::x = x;
}

void Cell::setY(double y) {
    Cell::y = y;
}

void Cell::setZ(double z) {
    Cell::z = z;
}

void Cell::setID(int ID) {
    Cell::ID = ID;
}

void Cell::setDiffState(double diffState) {
    Cell::diffState = diffState;
}

void Cell::setKnotCell() {
    Cell::knot = true;
}

void Cell::setNeighbour(int neighbourID) {
    Cell::neighbours.push_back(neighbourID);
}

void Cell::setInSimulation(bool inSimulation) {
    Cell::inSimulation = inSimulation;
}

void Cell::setInCentre(bool inCentre) {
    Cell::inCentre = inCentre;
}

void Cell::setMesenchymeThickness(int mesenchymeThickness) {
    Cell::mesenchymeThickness = mesenchymeThickness;
}

void Cell::newBorderPoint(char axis, double point) {
    switch (axis)
    {
        case 'X': {borderPointsX.push_back(point); break;}
        case 'Y': {borderPointsY.push_back(point); break;}
        case 'Z': {borderPointsZ.push_back(point); break;}
        default: std::cout << "The point could not be added" << std::endl;
    }
}

void Cell::replaceBorderPoint(char axis, double point, int position) {
    switch (axis)
    {
        case 'X': {borderPointsX[position] = point; break;}
        case 'Y': {borderPointsY[position] = point; break;}
        case 'Z': {borderPointsZ[position] = point; break;}
        default: std::cout << "The point could not be replaced" << std::endl;
    }
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

void Cell::addProteinConcentration(int protein, int layer, double addedConcentration) {
    proteinConcentrations[protein][layer] += addedConcentration;
}

void Cell::addTempConcentration(int protein, int layer, double addedConcentration){
    tempProteinConcentrations[protein][layer] += addedConcentration;
}

//Constructor
Cell::Cell(double x, double y, int z, int ID) : x(x), y(y), z(z), ID(ID) {
   knot = false;
   inSimulation = false;
   inCentre = false;
   mesenchymeThickness = 4;
   diffState = 0;
   //Set Concentrations to 0 (in each layer)
    for (int layer = 0; layer < mesenchymeThickness; ++layer) {
        ActConcentrations.push_back(layer);
        InhConcentrations.push_back(layer + 1);
        Sec1Concentrations.push_back(layer + 2);
        Sec2Concentrations.push_back(layer + 3);
        tempAct.push_back(0);
        tempInh.push_back(0);
        tempSec1.push_back(0);
        tempSec2.push_back(0);
    }
   proteinConcentrations = {ActConcentrations, InhConcentrations, Sec1Concentrations, Sec2Concentrations};
    tempProteinConcentrations = {tempAct, tempInh, tempSec1, tempSec2};
    perimeter = 0;
    cellArea = 0;
}

//Editors

void Cell::deleteNeighbour(int neighbour)
{
    neighbours.erase(neighbours.begin() + neighbour);
}

//Printer

void Cell::printCellBorders(std::vector<Cell> cells, int cellsInSimulation)
{
    for (int cell = 0; cell < cells.size(); ++cell) {
        std::cout << "Cell Nr. " << cell << std::endl;
        for (int point = 0; point < cells[cell].getBorderPointsX().size(); ++point) {
            std::cout << "x: " << cells[cell].getBorderPointsX()[point] << "  ";
            std::cout << "y: " << cells[cell].getBorderPointsY()[point] << "  ";
            std::cout << "z: " << cells[cell].getBorderPointsZ()[point] << "  ";
            std::cout << std::endl;
        }
    }
}








