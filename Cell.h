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

    std::vector<std::vector<double>> proteinConcentrations;

    std::vector<std::vector<double>> tempProteinConcentrations;

    bool knot;

    bool inSimulation;

    bool inCentre;

    int mesenchymeThickness;

    std::vector<double> borderPointsX;

    std::vector<double> borderPointsY;

    std::vector<double> borderPointsZ;

    std::vector<double> perimeterParts;

    std::vector<double> areaParts;

    double perimeter;

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

    //Setter
    void setX(double x);

    void setY(double y);

    void setZ(double z);

    void setID(int ID);

    void setDiffState(double diffState);

    void setKnotCell(bool knot);

    void setNeighbour(int neighbourID);

    void setMesenchymeThickness(int mesenchymeThickness);

    void setInSimulation(bool inSimulation);

    void setInCentre(bool inCentre);

    void newBorderPoint(char axis, double point);

    void replaceBorderPoint(char axis, double point, int position);

    void newPerimeterPart(double perimeterPart);

    void newAreaPart(double areaPart);

    void setPerimeter(double perimeter);

    void setCellArea(double cellArea);

    void addProteinConcentration(int protein, int layer, double newConcentration);

    void addTempConcentration(int protein, int layer, double addedConcentration);

    void setProteinConcentration(int protein, int layer, double newConcentration);

    //Constructor
    Cell(double x, double y, int z, int ID);

    //Editors
    void deleteNeighbour(int neighbour);

    void resetTempProteinConcentrations();

    //Printer
    static void printCellBorders(std::vector<Cell> cells, int cellsInSimulation);


};


#endif //TOOTHMAKER_CELL_H
