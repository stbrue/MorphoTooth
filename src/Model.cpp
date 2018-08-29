//
// Created by Stefanie on 13.08.2018.
//

#include <cmath>
#include <algorithm>
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
                if (layer != 0) { // if we are not within the epithelial layer
                    upDiffusion(cells, cell, layer, protein, pCellArea);
                    if (layer < (cells[cell].getMesenchymeThickness() - 1)) { // if its not the lowest layer
                        downDiffusion(cells, cell, layer, protein, pCellArea);
                    } else { // if its the lowest layer -> vertical sink
                        sink(cells, cell, layer, protein, pCellArea);
                    }
                    horizontalDiffusion(cells, cell, layer, protein, pDiffusionArea);
                } else if (layer == 0) { // if we are in the epithelium, do only horizontal Diffusion

                    horizontalDiffusion(cells, cell, layer, protein, eDiffusionArea);
                }
            }
        }
    }

    // Calculate the final protein concentrations (including diffusion coefficients and delta)
    for (int cell = 0; cell < params.getCellsInSimulation(); ++cell) {
        for (int protein = 0; protein < 4; ++protein) {
            for (int layer = 0; layer < cells[cell].getMesenchymeThickness(); ++layer) {
                double newConcentration = params.getDelta() * params.getDiffusionRates()[protein] *
                                          cells[cell].getTempProteinConcentrations()[protein][layer];
                cells[cell].addProteinConcentration(protein, layer, newConcentration);
            }
        }
        //Reset the temporary protein concentration matrix
        cells[cell].resetTempProteinConcentrations();
    }
}

void Model::reaction(std::vector<Cell> &cells, Parameters &params) {
    for (int cell = 0; cell < params.getCellsInSimulation(); ++cell) {
        EKDifferentiation(cells, params, cell);
        ActReactionAndDegradation(cells, params, cell);
        InhProduction(cells, params, cell);
        Sec1Production(cells, params, cell);
        Sec2Production(cells, params, cell);
    }

    //Error handling (test if new concentrations are too high)?

    //Update the final protein concentrations (including delta)
    for (int cell = 0; cell < params.getCellsInSimulation(); ++cell) {
        for (int protein = 0; protein < 4; ++protein) {
            for (int layer = 0; layer < cells[cell].getMesenchymeThickness(); ++layer) {
                double newConcentration =
                        params.getDelta() * cells[cell].getTempProteinConcentrations()[protein][layer];
                cells[cell].addProteinConcentration(protein, layer, newConcentration);
                //Remove negative concentration values
                if (cells[cell].getProteinConcentrations()[protein][layer] < 0) {
                    cells[cell].setProteinConcentration(protein, layer, 0);
                }
            }
        }
        //Reset the temporary protein concentration matrix
        cells[cell].resetTempProteinConcentrations();
    }
}

void Model::buccalLingualBias(std::vector<Cell> &cells, Parameters &params) {
    //for all center cells
    for (int cell = 0; cell < params.getCellsInCenter(); ++cell) {
        if (cells[cell].getY() < -params.getSwi()) {
            cells[cell].setProteinConcentration(0, 0, params.getLbi());
        } else if (cells[cell].getY() > params.getSwi()) {
            cells[cell].setProteinConcentration(0, 0, params.getBbi());
        }
    }
}

void Model::differenciation(std::vector<Cell> &cells, Parameters &params) {
    for (int cell = 0; cell < params.getCellsInSimulation(); ++cell) {
        //Increase the diff state of each cell
        double epithelialSec1Concentration = cells[cell].getProteinConcentrations()[2][0];
        double addDiff = params.getDff() * epithelialSec1Concentration;
        cells[cell].addDiffState(addDiff);
    }
}

void Model::epithelialProliferation(std::vector<Cell> &cells, Parameters &params) {
    double dx = 0;
    double dy = 0;
    double dz = 0;
    double xDeviation = 0;
    double yDeviation = 0;
    double zDeviation = 0;
    double totalDeviation = 0;

    //for all cells in the center
    for (int cell = 0; cell < params.getCellsInCenter(); ++cell) {
        bool isKnotCell = cells[cell].isKnotCell();
        if (isKnotCell) {
            continue;
        }

        for (int neighbour = 0; neighbour < cells[cell].getNeighbours().size(); ++neighbour) {
            int neighbourID = cells[cell].getNeighbours()[neighbour];
            bool neighbourIsInSimulation = cells[neighbourID].isInSimulation();
            if (neighbourIsInSimulation == false) {
                continue;
            }
            dz = cells[cell].getZ() - cells[neighbourID].getZ();
            // if the neighbour is a certain amount higher than cell, calculate the relative x/y/z deviations
            if (dz < -0.0001) {
                double distance3D = Geometrics::centerDistance3D(cells[cell], cells[neighbour]);
                dx = cells[cell].getX() - cells[neighbourID].getX();
                dy = cells[cell].getY() - cells[neighbourID].getY();
                xDeviation -= dx / distance3D;
                yDeviation -= dy / distance3D;
                zDeviation -= dz / distance3D;
            }
        }

        totalDeviation = Geometrics::vectorNorm3D(std::vector<double>{xDeviation, yDeviation, zDeviation});

        if (totalDeviation > 0) {
            double deviationFactor = 0;
            double diffFactor = 0;
            double cellDrift = 0;

            deviationFactor = params.getEgr() / totalDeviation;

            // the higher the differentiation, the lower the effect of deviations in position
            diffFactor = 1 - cells[cell].getDiffState();
            if (diffFactor < 0) {
                diffFactor = 0;
            }

            cellDrift = deviationFactor * diffFactor;

            cells[cell].addTempX(xDeviation * cellDrift);
            cells[cell].addTempY(yDeviation * cellDrift);
            cells[cell].addTempZ(zDeviation * cellDrift);
        }
    }

    //for border cells (within simulation)
    for (int cell = params.getCellsInCenter(); cell < params.getCellsInSimulation(); ++cell) {
        double angle1 = -0.3;
        double angle2 = 0;
        double angle3 = 0;
        double aa = 0;
        double bb = 0;
        double uuux = 0;
        double uuuy = 0;
        double duux = 0;
        double duuy = 0;
        double uaa = 0;
        double ubb = 0;
        double distance2D = 0;
        double a = 0;
        double b = 0;
        double c = 0;
        double d = 0;
        double dd = 0;
        double ddd = 0;
        double factor = 0;

        for (int neighbour = 0; neighbour < cells[cell].getNeighbours().size(); ++neighbour) {
            int neighbourID = cells[cell].getNeighbours()[neighbour];
            bool neighbourIsInSimulation = cells[neighbourID].isInSimulation();
            if (neighbourIsInSimulation == false) {
                continue;
            }
            bool neighbourIsCenterCell = cells[neighbourID].isInCentre();

            dx = cells[cell].getX() - cells[neighbourID].getX();
            dy = cells[cell].getY() - cells[neighbourID].getY();
            // z-differences does not matter here
            distance2D = Geometrics::centerDistance2D(cells[cell], cells[neighbourID]);

            if (neighbourIsCenterCell) {
                if (distance2D > 0) {
                    angle3 = acos(dx / distance2D);
                    if (dy < 0) {
                        angle3 = 2 * M_PI - angle3;
                    }
                }
            } else { //if neighbour is within simulation but not in the center (as cell)
                if (distance2D > 0) {
                    if (angle1 == -0.3) {
                        angle1 = acos(dx / distance2D);
                        if (dy < 0) {
                            angle1 = 2 * M_PI - angle1;
                        }
                        uuux = -dy / distance2D;
                        uuuy = dx / distance2D;
                        uaa = acos(uuux);

                        if (uuuy < 0) {
                            uaa = 2 * M_PI - uaa;
                        }
                    } else {
                        angle2 = acos(dx / distance2D);
                        if (dy < 0) {
                            angle2 = 2 * M_PI - angle2;
                        }
                        duux = -dy / distance2D;
                        duuy = dx / distance2D;
                        ubb = acos(uuux);

                        if (duuy < 0) {
                            ubb = 2 * M_PI - ubb;
                        }
                    }
                }
            }
        }

        if (angle1 < angle2) {
            distance2D = angle1;
            angle1 = angle2;
            angle2 = distance2D;
        }

        if (angle3 < angle1 && angle3 > angle2) {
            if (uaa < angle1 && uaa > angle2) {
                uuux = -uuux;
                uuuy = -uuuy;
            }
            if (ubb < angle1 && ubb > angle2) {
                duux = -duux;
                duuy = -duuy;
            }
        } else {
            if (uaa > angle1 || uaa < angle2) {
                uuux = -uuux;
                uuuy = -uuuy;
            }
            if (ubb > angle1 || ubb < angle2) {
                duux = -duux;
                duuy = -duuy;
            }
        }

        aa = -uuux - duux;
        bb = -uuuy - duuy;

        a = cells[cell].getX() + aa;
        b = cells[cell].getY() + bb;
        c = cells[cell].getX() - aa;
        d = cells[cell].getY() - bb;

        dd = sqrt(a * a + b * b);
        ddd = sqrt(c * c + d * d);

        if (ddd > dd) {
            aa = -aa;
            bb = -bb;
        }

        d = sqrt(aa * aa + bb * bb);
        double epithelialSec1Concentration = cells[cell].getProteinConcentrations()[2][0];
        if (d > 0) {
            factor = (d + params.getMgr() * epithelialSec1Concentration) / d;
            aa = aa * factor;
            bb = bb * factor;
        }

        d = sqrt(aa * aa + bb * bb + params.getDgr() * params.getDgr());
        if (d > 0) {
            factor = params.getEgr() / d;
            double invertDiffState = 1 - cells[cell].getDiffState();
            if (invertDiffState < 0) {
                invertDiffState = 0;
            }

            factor = factor * invertDiffState;

            cells[cell].addTempX(aa * factor);
            cells[cell].addTempY(bb * factor);
            cells[cell].addTempZ(params.getDgr() * factor);
        }
    }
}

void Model::buoyancy(std::vector<Cell> &cells, Parameters &params) {
    for (int cell = 0; cell < params.getCellsInSimulation(); ++cell) {
        double distanceToOrigin2D = Geometrics::centerDistanceToOrigin2D(cells[cell]);
        if (distanceToOrigin2D > 0) {
            double distanceToOrigin3D = Geometrics::centerDistanceToOrigin3D(cells[cell]);
            double relativeZDistance = -cells[cell].getZ() / distanceToOrigin3D;
            double XRelativeToZ = cells[cell].getX() * relativeZDistance;
            double YRelativeToZ = cells[cell].getY() * relativeZDistance;
            double relativeDistance = sqrt(XRelativeToZ * XRelativeToZ + YRelativeToZ * YRelativeToZ +
                                           distanceToOrigin2D * distanceToOrigin2D);
            double epithelialSec1Concentration = cells[cell].getProteinConcentrations()[2][0];
            relativeDistance = params.getBoy() * epithelialSec1Concentration / relativeDistance;

            if (relativeDistance > 0) {
                double inverseDiffState = 1 - cells[cell].getDiffState();
                if (inverseDiffState < 0) {
                    inverseDiffState = 0;
                }
                double newX = cells[cell].getX() * relativeDistance * inverseDiffState;
                double newY = cells[cell].getY() * relativeDistance * inverseDiffState;
                double newZ = distanceToOrigin2D * relativeDistance * inverseDiffState;

                cells[cell].addTempX(newX);
                cells[cell].addTempY(newY);
                cells[cell].addTempZ(newZ);

            }
        }
    }
}

void Model::repulsion(std::vector<Cell> &cells, Parameters &params) {
    std::vector<std::vector<double>> compressionMatrixNeighbour = Model::setUpCompressionMatrix();
    std::vector<std::vector<double>> compressionMatrixNonNeighbour = Model::setUpCompressionMatrix();

    for (int cell1 = 0; cell1 < params.getCellsInSimulation(); ++cell1) {
        resetCompressionMatrix(compressionMatrixNeighbour);
        resetCompressionMatrix(compressionMatrixNonNeighbour);

        for (int cell2 = 0; cell2 < params.getCellsInSimulation(); ++cell2) {
            if (cell1 == cell2) {
                continue;
            }

            double x1 = cells[cell1].getX();
            double y1 = cells[cell1].getY();
            double z1 = cells[cell1].getZ();
            double x2 = cells[cell2].getX();
            double y2 = cells[cell2].getY();
            double z2 = cells[cell2].getZ();

            double dx = x2 - x1;
            double dy = y2 - y1;
            double dz = z2 - z1;

            double distance3D = Geometrics::centerDistance3D(cells[cell1], cells[cell2]);
            double distance2D = Geometrics::centerDistance2D(cells[cell1], cells[cell2]);

            //Check for the situation
            bool cell2IsNeighbour = Model::isNeighbourOf(cells, cell1, cell2);
            bool neighbourIsInSimulation = cells[cell2].isInSimulation();
            bool cell1IsEKCell = cells[cell1].isKnotCell();
            bool cell2IsEKCell = cells[cell2].isKnotCell();
            bool cell1IsInCenter = cells[cell1].isInCentre();

            if (cell2IsNeighbour && neighbourIsInSimulation) {
                Model::repulsionBetweenNeighbours(dx, dy, dz, distance3D, distance2D, compressionMatrixNeighbour,
                                                  cell1IsEKCell, cell2IsEKCell, cell1IsInCenter, params.getAdh());
            } else if (cell2IsNeighbour == false) {
                Model::repulsionBetweenNonNeighbours(dx, dy, dz, distance3D, compressionMatrixNonNeighbour);
            }

            Model::updateTempPositions(cells, params, cell1, compressionMatrixNonNeighbour, false);
            Model::updateTempPositions(cells, params, cell1, compressionMatrixNeighbour, true);
        }
    }

}

void Model::nucleusTraction(std::vector<Cell> &cells, Parameters params) {
    for (int cell = 0; cell < params.getCellsInSimulation(); ++cell) {
        double totalX = 0;
        double totalY = 0;
        double totalZ = 0;
        int numberOfNeighboursInSimulation = 0;

        bool cellIsInCenter = cells[cell].isInCentre();
        if (cellIsInCenter) {
            for (int neighbour = 0; neighbour < cells[cell].getNeighbours().size(); ++neighbour) {
                int neighbourID = cells[cell].getNeighbours()[neighbour];
                bool neighbourIsInSimulation = cells[neighbourID].isInSimulation();

                //only neighbours that are within simulation are taken into account
                if (neighbourIsInSimulation) {
                    numberOfNeighboursInSimulation += 1;
                    totalX += cells[neighbourID].getX();
                    totalY += cells[neighbourID].getY();
                    totalZ += cells[neighbourID].getZ();
                }
            }
        } else {
            for (int neighbour = 0; neighbour < cells[cell].getNeighbours().size(); ++neighbour) {
                int neighbourID = cells[cell].getNeighbours()[neighbour];
                bool neighbourIsInSimulation = cells[neighbourID].isInSimulation();
                bool neighbourIsInCenter = cells[neighbourID].isInCentre();

                //only the neighbours that are within simulation but not in the center are taken into account
                if (neighbourIsInSimulation && (neighbourIsInCenter == false)) {
                    numberOfNeighboursInSimulation += 1;
                    totalX += cells[neighbourID].getX();
                    totalY += cells[neighbourID].getY();
                    totalZ += cells[neighbourID].getZ();
                }
            }
        }

        double averageX = totalX / numberOfNeighboursInSimulation;
        double averageY = totalY / numberOfNeighboursInSimulation;
        double averageZ = totalZ / numberOfNeighboursInSimulation;

        double XDeviationFromAverage = averageX - cells[cell].getX();
        double YDeviationFromAverage = averageY - cells[cell].getY();
        double ZDeviationFromAverage = averageZ - cells[cell].getZ();

        // Ntr: Parameter for nuclear traction
        cells[cell].addTempX(XDeviationFromAverage * params.getDelta() * params.getNtr());
        cells[cell].addTempY(YDeviationFromAverage * params.getDelta() * params.getNtr());
        // only if the cell isn't a EK cell, the z-position is affected by nuclear traction
        if (cells[cell].isKnotCell() == false) {
            double inverseDiffState = 1 - cells[cell].getDiffState();
            if (inverseDiffState < 0) {
                inverseDiffState = 0;
            }
            cells[cell].addTempZ(ZDeviationFromAverage * params.getDelta() * params.getNtr() * inverseDiffState);
        }
    }

}

void Model::repulsionBetweenNeighbours(double dx, double dy, double dz, double distance3D, double distance2D,
                                       std::vector<std::vector<double>> compressionMatrixNeighbours, bool cell1IsEKCell,
                                       bool cell2IsEKCell, bool cell1IsInCenter, double adh) {
    //rounding
    if (fabs(dx) < 1.0e-15) {
        dx = 0;
    }
    if (fabs(dy) < 1.0e-15) {
        dy = 0;
    }
    if (fabs(dz) < 1.0e-15) {
        dz = 0;
    }
    if (distance2D < 1.0e-8) {
        distance2D = 0;
    }
    if (distance3D < 1.0e-8) {
        distance3D = 0;
    }

    //if both cells are enamel knot cells or the 3D distance is shorter than the 2D distance
    if ((cell1IsEKCell && cell2IsEKCell) || (distance3D < distance2D)) {
        double deviation = distance3D - distance2D;
        double relativeDeviation = deviation / distance3D;

        compressionMatrixNeighbours[0].push_back(dx * relativeDeviation);
        compressionMatrixNeighbours[1].push_back(dy * relativeDeviation);
        compressionMatrixNeighbours[2].push_back(dz * relativeDeviation);
    }
        // or if cell1 is in center
        // adh: parameter for cell repulsion/adhesion
    else if (cell1IsInCenter) {
        compressionMatrixNeighbours[0].push_back(dx * adh);
        compressionMatrixNeighbours[1].push_back(dy * adh);
        compressionMatrixNeighbours[2].push_back(dz * adh);
    }
}

void Model::repulsionBetweenNonNeighbours(double dx, double dy, double dz, double distance3D,
                                          std::vector<std::vector<double>> compressionMatrixNonNeighbours) {

    //If the cell is enough far away (in any dimension) the is no repulsion
    if (dx > 1.4 || dy > 1.4 || dz > 1.4) {
        return;
    }

    //rounding
    if (fabs(dx) < 1.0e-15) {
        dx = 0;
    }
    if (fabs(dy) < 1.0e-15) {
        dy = 0;
    }
    if (fabs(dz) < 1.0e-15) {
        dz = 0;
    }

    if (distance3D < 1.4) {
        //the smaller the distance, the even higher the force
        double relativeDistance = 1 / pow((distance3D + 1), 8);
        double factor = relativeDistance / distance3D;
        factor = static_cast<int>(fabs(factor * 1.0e8)) * 1.0e-8;

        compressionMatrixNonNeighbours[0].push_back(-dx * factor);
        compressionMatrixNonNeighbours[1].push_back(-dy * factor);
        compressionMatrixNonNeighbours[2].push_back(-dz * factor);
    }
}

void Model::updateTempPositions(std::vector<Cell> &cells, Parameters params, int cell,
                                std::vector<std::vector<double>> compressionMatrix, bool isNeighbour) {
    double rep = params.getRep();
    // Rep: Parameter for repulsion between different tissues and morphology parts

    //if it is a neighbour cell, the repulsion parameter is maximally 1
    if (isNeighbour) {
        if (rep > 1) {
            rep = 1;
        }
    }

    cells[cell].addTempX(Geometrics::vectorSum(compressionMatrix[0]) * rep);
    cells[cell].addTempY(Geometrics::vectorSum(compressionMatrix[1]) * rep);
    cells[cell].addTempZ(Geometrics::vectorSum(compressionMatrix[2]) * rep);

}

std::vector<std::vector<double>> Model::setUpCompressionMatrix() {
    std::vector<double> XCompression;
    std::vector<double> YCompression;
    std::vector<double> ZCompression;

    std::vector<std::vector<double>> compressionMatrix = {XCompression, YCompression, ZCompression};

    return compressionMatrix;
}

void Model::resetCompressionMatrix(std::vector<std::vector<double>> &compressionMatrix) {
    for (int dimension = 0; dimension < 3; ++dimension) {
        compressionMatrix[dimension].clear();
    }
}

bool Model::isNeighbourOf(std::vector<Cell> &cells, int cell, int potentialNeighbour) {
    std::vector<int> neighbours = cells[cell].getNeighbours();
    if (std::find(neighbours.begin(), neighbours.end(), potentialNeighbour) != neighbours.end()) {
        return true;
    } else {
        return false;
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
        if (cells[neighbourID].isInSimulation()) {
            double neighbourConcentration = cells[neighbourID].getProteinConcentrations()[protein][layer];
            double pPerimeterPart = (cells[cell].getPerimeterParts()[neighbour] / diffusionArea);
            newConcentration += (pPerimeterPart * (neighbourConcentration - oldConcentration));
            cells[cell].addTempConcentration(protein, layer, newConcentration);
        } else {          // if the neighbour is not within simulation, there is a sink
            sink(cells, cell, layer, protein, diffusionArea);
        }
    }
}

void Model::EKDifferentiation(std::vector<Cell> &cells, Parameters &params, int cell) {
    //if the Act concentration in the epithelial layer is high enough
    //and if it is in the centre, then it becomes/is a knot cell
    if (cells[cell].getProteinConcentrations()[0][0] > 1) {
        if (cells[cell].isInCentre()) {
            cells[cell].setKnotCell(true);
        }
    }
}

void Model::ActReactionAndDegradation(std::vector<Cell> &cells, Parameters &params, int cell) {
    double epithelialActConcentration = cells[cell].getProteinConcentrations()[0][0];
    double epithelialInhConcentration = cells[cell].getProteinConcentrations()[1][0];
    double epithelialSec2Concentration = cells[cell].getProteinConcentrations()[3][0];

    double positiveTerm = params.getAct() * epithelialActConcentration - epithelialSec2Concentration;
    if (positiveTerm < 0) {
        positiveTerm = 0;
    }
    double negativeTerm = 1 + params.getInh() * epithelialInhConcentration;
    double degradation = params.getMu() * epithelialActConcentration;

    //concentration difference: reaction - degradation
    double newConcentration = positiveTerm / negativeTerm - degradation;
    cells[cell].addTempConcentration(0, 0, newConcentration);
}

void Model::InhProduction(std::vector<Cell> &cells, Parameters &params, int cell) {
    //Inh is produced if diff state is higher than threshold or if the cell is an EK cell
    double diffState = cells[cell].getDiffState();
    double epithelialInhConcentration = cells[cell].getProteinConcentrations()[1][0];
    double epithelialActConcentration = cells[cell].getProteinConcentrations()[0][0];
    bool isKnotCell = cells[cell].isKnotCell();
    double newConcentration;

    if (diffState > params.getInT()) {
        newConcentration = epithelialActConcentration * diffState - params.getMu() * epithelialInhConcentration;
    } else if (isKnotCell) {
        newConcentration = epithelialActConcentration - params.getMu() * epithelialInhConcentration;
    }
    cells[cell].addTempConcentration(1, 0, newConcentration);
}

void Model::Sec1Production(std::vector<Cell> &cells, Parameters &params, int cell) {
    double diffState = cells[cell].getDiffState();
    double epithelialSec1Concentration = cells[cell].getProteinConcentrations()[2][0];
    bool isKnotCell = cells[cell].isKnotCell();
    double newConcentration;

    if (diffState > params.getSet()) {
        newConcentration = params.getSec() * diffState - params.getMu() * epithelialSec1Concentration;
    } else if (isKnotCell) {
        newConcentration = params.getSec() - params.getMu() * epithelialSec1Concentration;
    }

    if (newConcentration < 0) {
        newConcentration = 0;
    }
    cells[cell].addTempConcentration(2, 0, newConcentration);
}

void Model::Sec2Production(std::vector<Cell> &cells, Parameters &params, int cell) {
    double epithelialActConcentration = cells[cell].getProteinConcentrations()[0][0];
    double epithelialSec1Concentration = cells[cell].getProteinConcentrations()[2][0];
    double epithelialSec2Concentration = cells[cell].getProteinConcentrations()[3][0];

    double newConcentration =
            params.getAct() * epithelialActConcentration - params.getMu() * epithelialSec2Concentration -
            params.getSec2Inhibition() * epithelialSec1Concentration;
    if (newConcentration < 0) {
        newConcentration = 0;
    }

    cells[cell].addTempConcentration(3, 0, newConcentration);
}