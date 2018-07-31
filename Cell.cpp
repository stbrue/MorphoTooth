//
// Created by Stefanie on 30.07.2018.
//

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

double Cell::getActConcentration() const {
    return ActConcentration;
}

double Cell::getInhConcentration() const {
    return InhConcentration;
}

double Cell::getSec1Concentration() const {
    return Sec1Concentration;
}

double Cell::getSec2Concentration() const {
    return Sec2Concentration;
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

void Cell::setActConcentration(double ActConcentration) {
    Cell::ActConcentration = ActConcentration;
}

void Cell::setInhConcentration(double InhConcentration) {
    Cell::InhConcentration = InhConcentration;
}

void Cell::setSec1Concentration(double Sec1Concentration) {
    Cell::Sec1Concentration = Sec1Concentration;
}

void Cell::setSec2Concentration(double Sec2Concentration) {
    Cell::Sec2Concentration = Sec2Concentration;
}

void Cell::setKnotCell() {
    Cell::knot = true;
}

void Cell::setNeighbour(int neighbourID) {
    Cell::neighbours.push_back(neighbourID);
}


Cell::Cell(double x, double y, double z, int ID, double diffState = 0, double ActConcentration = 0, double InhConcentration = 0,
           double Sec1Concentration = 0, double Sec2Concentration = 0) : x(x), y(y), z(z), ID(ID), diffState(diffState),
                                                                 ActConcentration(ActConcentration),
                                                                 InhConcentration(InhConcentration),
                                                                 Sec1Concentration(Sec1Concentration),
                                                                 Sec2Concentration(Sec2Concentration) {}

bool Cell::isInSimulation() const {
    return inSimulation;
}

void Cell::setInSimulation(bool inSimulation) {
    Cell::inSimulation = inSimulation;
}

bool Cell::isInCentre() const {
    return inCentre;
}

void Cell::setInCentre(bool inCentre) {
    Cell::inCentre = inCentre;
}

int Cell::getMesenchymeThickness() const {
    return mesenchymeThickness;
}

void Cell::setMesenchymeThickness(int mesenchymeThickness) {
    Cell::mesenchymeThickness = mesenchymeThickness;
}
