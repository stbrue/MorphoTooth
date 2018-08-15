//
// Created by Stefanie on 13.08.2018.
//

#include <cmath>
#include "Model.h"
#include "Geometrics.h"
#include "Parameters.h"

void Model::diffusion(std::vector<Cell> &cells, Parameters &params) {

    //Calculate for each cell its perimeter and area
    Geometrics::calculatePerimeterAndArea(cells, params.getCellsInSimulation());

    for (int cell = 0; cell < params.getCellsInSimulation(); ++cell) {
        //Total diffusion area = perimeter + 2 * area (bottom and top area)
        double perimeter = cells[cell].getPerimeter();
        double cellArea = cells[cell].getCellArea();

        double pDiffusionArea = perimeter + (2 * cellArea);
        double eDiffusionArea = perimeter + cellArea;

        // Set cell area relative to total diffusion area
        double pCellArea = cellArea / pDiffusionArea;
        double eCellArea = cellArea / eDiffusionArea;


        //Diffusion in all layers in all directions
        for (int protein = 0; protein < 4; ++protein) {
            for (int layer = 0; layer < cells[cell].getMesenchymeThickness(); ++layer) {
                if (layer != 0){ // if we are not within the epithelial layer
                    upDiffusion(cells, cell, layer, protein, pCellArea);
                        if (layer != cells[cell].getMesenchymeThickness()){ // if its not the lowest layer
                            downDiffusion(cells, cell, layer, protein, pCellArea);
                        }
                        else { // if its the lowest layer -> vertical sink
                            sink(cells, cell, layer, protein, pCellArea);
                        }
                    horizontalDiffusion(cells, cell, layer, protein, pDiffusionArea);
                }
                else if (layer == 0) { // if we are in the epithelium, do only horizontal Diffusion

                    horizontalDiffusion(cells, cell, layer, protein, eDiffusionArea);
                }
            }
        }
    }

    // Calculate the final protein concentrations (including diffusion coefficients and delta)
    for (int cell = 0; cell < params.getCellsInSimulation(); ++cell) {
        for (int protein = 0; protein < 4; ++protein) {
            for (int layer = 0; layer < cells[cell].getMesenchymeThickness(); ++layer) {
                double newConcentration = params.getDelta() * params.getDiffusionRates()[protein] * cells[cell].getTempProteinConcentrations()[protein][layer];
                cells[cell].addProteinConcentration(protein, layer, newConcentration);
            }
        }
    }
}

void Model::upDiffusion(std::vector<Cell> &cells, int cell, int layer, int protein, double pCellArea) {
    double oldConcentration = cells[cell].getProteinConcentrations()[protein][layer];
    double neighbourConcentration = cells[cell].getProteinConcentrations()[protein][layer - 1];
    double newConcentration = (pCellArea * (neighbourConcentration - oldConcentration));

    cells[cell].addTempConcentration(protein, layer, newConcentration);
}

void Model::downDiffusion(std::vector<Cell> &cells, int cell, int layer, int protein, double pCellArea) {
    double oldConcentration = cells[cell].getProteinConcentrations()[protein][layer];
    double neighbourConcentration = cells[cell].getProteinConcentrations()[protein][layer + 1];
    double newConcentration = (pCellArea * (neighbourConcentration - oldConcentration));

    cells[cell].addTempConcentration(protein, layer, newConcentration);
}

void Model::sink(std::vector<Cell> &cells, int cell, int layer, int protein, double contactArea) {
    double oldConcentration = cells[cell].getProteinConcentrations()[protein][layer];
    double newConcentration = (contactArea * (-oldConcentration * 0.4));

    cells[cell].addTempConcentration(protein, layer, newConcentration);
}

void Model::horizontalDiffusion(std::vector<Cell> &cells, int cell, int layer, int protein, double diffusionArea) {
    double oldConcentration = cells[cell].getProteinConcentrations()[protein][layer];
    double newConcentration = 0;
    for (int neighbour = 0; neighbour < cells[cell].getNeighbours().size(); ++neighbour) {
        int neighbourID = cells[cell].getNeighbours()[neighbour];
        if (cells[neighbourID].isInSimulation()){
            double neighbourConcentration = cells[neighbourID].getProteinConcentrations()[protein][layer];
            double pPerimeterPart = (cells[cell].getPerimeterParts()[neighbour] / diffusionArea);
            newConcentration += (pPerimeterPart * (neighbourConcentration - oldConcentration));
            cells[cell].addTempConcentration(protein, layer, newConcentration);
        }
        else {          // if the neighbour is not within simulation, there is a sink
            sink(cells, cell, layer, protein, diffusionArea);
        }
    }
}