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
    int mesenchymeThickness;
    std::vector<double> borderPointsX;
    std::vector<double> borderPointsY;
    std::vector<double> borderPointsZ;

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
    int getMesenchymeThickness() const;
    bool isInSimulation() const;
    bool isInCentre() const;
    const std::vector<double> &getBorderPointsX() const;
    const std::vector<double> &getBorderPointsY() const;
    const std::vector<double> &getBorderPointsZ() const;

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
    void setMesenchymeThickness(int mesenchymeThickness);
    void setInSimulation(bool inSimulation);
    void setInCentre(bool inCentre);
    void newBorderPoint(char axis, double point);
    void replaceBorderPoint(char axis, double point, int position);

    //Constructor
    Cell(double x, double y, int ID);

    //Editors
    void deleteNeighbour(int neighbour);

    //Printer
    static void printCellBorders(std::vector<Cell> cells, int cellsInSimulation);


};


#endif //TOOTHMAKER_CELL_H
