//
// Created by Stefanie on 30.07.2018.
//

#ifndef TOOTHMAKER_CELL_H
#define TOOTHMAKER_CELL_H

#include <vector>

class Cell {
private:
    double x;
    double y;
    double z;
    int ID;
    std::vector<int> neighbours;
    double diffState;
    double ActConcentration;
    double InhConcentration;
    double Sec1Concentration;
    double Sec2Concentration;
    bool knot;
    bool inSimulation;
    bool inCentre;
public:
    bool isInSimulation() const;

    void setInSimulation(bool inSimulation);

    bool isInCentre() const;

    void setInCentre(bool inCentre);

public:
    //Getter
    double getX() const;
    double getY() const;
    double getZ() const;
    int getID() const;
    double getDiffState() const;
    double getActConcentration() const;
    double getInhConcentration() const;
    double getSec1Concentration() const;
    double getSec2Concentration() const;
    bool isKnotCell() const;
    std::vector<int> getNeighbours() const;

    //Setter
    void setX(double x);
    void setY(double y);
    void setZ(double z);
    void setID(int ID);
    void setDiffState(double diffState);
    void setActConcentration(double ActConcentration);
    void setInhConcentration(double InhConcentration);
    void setSec1Concentration(double Sec1Concentration);
    void setSec2Concentration(double Sec2Concentration);
    void setKnotCell();
    void setNeighbour(int neighbourID);

    Cell(double x, double y, double z, int ID, double diffState, double ActConcentration, double InhConcentration,
         double Sec1Concentration, double Sec2Concentration);
};


#endif //TOOTHMAKER_CELL_H
