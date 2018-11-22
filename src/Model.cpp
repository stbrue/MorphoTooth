//
// Created by Stefanie on 13.08.2018.
//

#include <cmath>
#include <algorithm>
#include <iostream>
#include "Model.h"
#include "Geometrics.h"
#include "Parameters.h"
#include "consts.h"


void Model::iterationStep(std::vector<Cell> &cells, Parameters &params, int iteration) {
    //if (iteration == 600) {
    //    std::cout << "Hello" << std::endl;
    //}

    Model::diffusion(cells, params);
    Model::reaction(cells, params);
    Model::buccalLingualBias(cells, params);
    Model::differentiation(cells, params);
    Model::epithelialProliferation(cells, params);
    //Model::newEpithelialProliferation(cells, params);
    Model::buoyancy(cells, params);
    Model::repulsionAndAdhesion(cells, params);
    Model::nucleusTraction(cells, params);
    Model::anteriorPosteriorBias(cells, params);
    Model::applyForces(cells, params);
    Model::cellDivision(cells, params);
    Geometrics::calculateCellBorders(cells, params.nrCellsInSimulation);
    Model::errorTesting(cells, params);

    /* Resetting of matrices:
     Resetting of tempConcentrations is done in the loop within the diffusion function itself
     Resetting of tempConcentrations is done in the loop within the reaction function itself
     The tempPosition Matrix gets resetted in the function applyForces */
}

bool Model::NanIsPresent(double x, double y, double z) {
    if (x != x) {
        std::cout << "x value is Nan" << std::endl;
        return true;
    } else if (y != y) {
        std::cout << "y value is Nan" << std::endl;
        return true;
    } else if (z != z) {
        std::cout << "z value is Nan" << std::endl;
        return true;
    }
    return false;
}

void Model::errorTesting(std::vector<Cell> cells, Parameters &params) {
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        double x = cells[cell].getX();
        double y = cells[cell].getY();
        double z = cells[cell].getZ();

        if (Model::NanIsPresent(x, y, z)) {
            //params.error = true;
            std::cout << "There is a fucking Nan in iteration " << params.currentIteration << std::endl;
        }
    }
}

void Model::diffusion(std::vector<Cell> &cells, Parameters &params) {

    //Calculate for each cell its perimeter and area
    Geometrics::calculatePerimeterAndArea(cells, params);

    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {

        double perimeter = cells[cell].getPerimeter();
        double cellArea = cells[cell].getCellArea();

        //For mesenchymal Diffusion: Total diffusion area = perimeter + 2 * area (bottom and top area)
        double mTotalDiffusionArea = perimeter + (2 * cellArea);
        //For Epithelial Diffusion: Total diffusion area = perimeter + 1 * area (only bottom)
        double eTotalDiffusionArea = perimeter + cellArea;

        // Set cell area relative to total diffusion area
        double relativeDiffusionAreaMesenchyme = cellArea / mTotalDiffusionArea;
        double relativeDiffusionAreaEpithel = cellArea / eTotalDiffusionArea;

        //Diffusion in all layers in all directions
        for (int protein = 0; protein < 4; ++protein) {
            for (int layer = 0; layer < cells[cell].getMesenchymeThickness(); ++layer) {
                //Layer 0 is Epithel, Layer 2 - 4 are Mesenchyme
                if (layer != 0) { // if we are not within the epithelial layer
                    upDiffusion(cells, cell, layer, protein, relativeDiffusionAreaMesenchyme);
                    if (layer < (cells[cell].getMesenchymeThickness() - 1)) { // if its not the lowest layer
                        downDiffusion(cells, cell, layer, protein, relativeDiffusionAreaMesenchyme);
                    } else { // if its the lowest layer -> vertical sink
                        sink(cells, cell, layer, protein, relativeDiffusionAreaMesenchyme);
                    }
                    horizontalDiffusion(cells, cell, layer, protein, mTotalDiffusionArea);
                } else if (layer == 0) { // if we are in the epithelium, do no up Diffusion
                    horizontalDiffusion(cells, cell, layer, protein, eTotalDiffusionArea);
                    downDiffusion(cells, cell, layer, protein, relativeDiffusionAreaEpithel);
                }
            }
        }
    }

    // Calculate the final protein concentrations (including diffusion coefficients and delta)
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        for (int protein = 0; protein < 4; ++protein) {
            for (int layer = 0; layer < cells[cell].getMesenchymeThickness(); ++layer) {
                double delta = params.delta;
                double diffusionRate = params.diffusionRates[protein];
                double tempConcentration = cells[cell].getTempProteinConcentrations()[protein][layer];
                double newConcentration = delta * diffusionRate * tempConcentration;
                cells[cell].addProteinConcentration(protein, layer, newConcentration);
            }
        }
        //Reset the temporary protein concentration matrix
        cells[cell].resetTempProteinConcentrations();
    }
}

void Model::upDiffusion(std::vector<Cell> &cells, int cell, int layer, int protein, double relativeDiffusionArea) {
    double oldConcentration = cells[cell].getProteinConcentrations()[protein][layer];
    double neighbourConcentration = cells[cell].getProteinConcentrations()[protein][layer - 1];
    double newConcentration = (relativeDiffusionArea * (neighbourConcentration - oldConcentration));

    cells[cell].addTempConcentration(protein, layer, newConcentration);
}

void Model::downDiffusion(std::vector<Cell> &cells, int cell, int layer, int protein, double relativeDiffusionArea) {
    double oldConcentration = cells[cell].getProteinConcentrations()[protein][layer];
    double neighbourConcentration = cells[cell].getProteinConcentrations()[protein][layer + 1]; // a layer below
    double newConcentration = (relativeDiffusionArea * (neighbourConcentration - oldConcentration));

    cells[cell].addTempConcentration(protein, layer, newConcentration);
}

void Model::sink(std::vector<Cell> &cells, int cell, int layer, int protein, double relativeDiffusionArea) {
    double oldConcentration = cells[cell].getProteinConcentrations()[protein][layer];
    double newConcentration = (relativeDiffusionArea *
                               (-oldConcentration *
                                0.44));    //0.44 is an arbitrary value from Salazar-Ciudad & Jernvall

    cells[cell].addTempConcentration(protein, layer, newConcentration);
}

void Model::horizontalDiffusion(std::vector<Cell> &cells, int cell, int layer, int protein, double totalDiffusionArea) {
    double oldConcentration = cells[cell].getProteinConcentrations()[protein][layer];
    double newConcentration = 0;
    bool borderDiffusionDone = false;
    for (int neighbour = 0; neighbour < cells[cell].getNeighbours().size(); ++neighbour) {
        int neighbourID = cells[cell].getNeighbours()[neighbour];

        if (cells[neighbourID].isInSimulation()) {
            double neighbourConcentration = cells[neighbourID].getProteinConcentrations()[protein][layer];
            double pPerimeterPart = (cells[cell].getPerimeterParts()[neighbour] / totalDiffusionArea);
            newConcentration = (pPerimeterPart * (neighbourConcentration - oldConcentration));
            cells[cell].addTempConcentration(protein, layer, newConcentration);
        }
            // if the neighbour is not within simulation and the borderDiffusion has not yet been calculated, there is a sink
        else if (borderDiffusionDone == false) {
            double pMargin = cells[cell].getMargin() / totalDiffusionArea;
            sink(cells, cell, layer, protein, pMargin);
            borderDiffusionDone = true;
        }
    }
}

void Model::reaction(std::vector<Cell> &cells, Parameters &params) {
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        ActReactionAndDegradation(cells, params, cell);
        InhReactionAndDegradation(cells, params, cell);
        Sec1ReactionAndDegradation(cells, params, cell);
        //Sec2ReactionAndDegradation(cells, params, cell); // not used, since [Sec2] is always = 0
    }

    //Update the final protein concentrations (including delta)
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        for (int protein = 0; protein < 4; ++protein) {
            for (int layer = 0; layer < cells[cell].getMesenchymeThickness(); ++layer) {
                double newConcentration =
                        params.delta * cells[cell].getTempProteinConcentrations()[protein][layer];
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
    //for all border cells
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        bool cellIsInCentre = cells[cell].isInCentre();
        if (cellIsInCentre) {
            continue;
        } else if (cells[cell].getY() < -params.swi) {                     //swi: distance of initial BMPs from mid line
            cells[cell].setProteinConcentration(PAct, LEpithelium,
                                                params.lbi);  //lbi: lingual bias by initial BMP distribution
        } else if (cells[cell].getY() > params.swi) {
            cells[cell].setProteinConcentration(PAct, LEpithelium,
                                                params.bbi);  //bbi: buccal bias by initial BMP distribution
        }
    }
}

void Model::differentiation(std::vector<Cell> &cells, Parameters &params) {
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        //Increase the diff state of each cell
        double epithelialSec1Concentration = cells[cell].getProteinConcentrations()[PSec1][LEpithelium];
        double addDiff = params.dff * epithelialSec1Concentration;
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
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        bool isInCentre = cells[cell].isInCentre();
        bool isKnotCell = cells[cell].isKnotCell();

        if (isInCentre == false) {
            continue;
        }

        if (isKnotCell) {
            continue;
        }

        for (int neighbour = 0; neighbour < cells[cell].getNeighbours().size(); ++neighbour) {
            int neighbourID = cells[cell].getNeighbours()[neighbour];
            bool neighbourIsInSimulation = cells[neighbourID].isInSimulation();
            if (neighbourIsInSimulation == false) {
                std::cout << "Something very strange in Epithelial Proliferation happened 1" << std::endl;
                continue;
            }
            dz = cells[cell].getZ() - cells[neighbourID].getZ();
            // if the neighbour is a certain amount higher than cell, calculate the relative x/y/z deviations
            if (dz < -0.0001) {
                double distance3D = Geometrics::centerDistance3D(cells[cell], cells[neighbourID]);
                dx = cells[cell].getX() - cells[neighbourID].getX(); //<0 if neighbour is more right
                dy = cells[cell].getY() - cells[neighbourID].getY();
                xDeviation -= dx / distance3D;
                yDeviation -= dy / distance3D;
                zDeviation -= dz / distance3D;
            }
        }

        totalDeviation = Geometrics::vectorNorm3D(std::vector<double>{xDeviation, yDeviation, zDeviation});

        if (totalDeviation > 0) {
            double deviationFactor = 0;
            double inverseDiffFactor = 0;
            double cellDrift = 0;

            if (totalDeviation == 0) {
                std::cout << "Total deviation = 0 -> divide by zero" << std::endl;
                std::cout.flush();
            }
            deviationFactor = params.egr / totalDeviation;      //egr: epithelial proliferation rate

            // the higher the differentiation, the lower the effect of deviations in position
            inverseDiffFactor = 1 - cells[cell].getDiffState();
            if (inverseDiffFactor < 0) {
                inverseDiffFactor = 0;
            }

            cellDrift = deviationFactor * inverseDiffFactor;

            cells[cell].addTempX(xDeviation * cellDrift);
            cells[cell].addTempY(yDeviation * cellDrift);
            cells[cell].addTempZ(zDeviation * cellDrift);
        }
    }

    //for border cells (within simulation)
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {

        if (cells[cell].isInCentre()) {
            continue;
        }

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
                        ubb = acos(duux);

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
        double epithelialSec1Concentration = cells[cell].getProteinConcentrations()[PSec1][LEpithelium];
        if (d > 0) {
            factor = (d + params.mgr * epithelialSec1Concentration) / d;        //mgr: mesenchymal proliferation rate
            aa = aa * factor;
            bb = bb * factor;
        }

        d = sqrt(aa * aa + bb * bb + params.dgr * params.dgr);                  //dgr: downgrowth
        if (d > 0) {
            factor = params.egr / d;
            double invertDiffState = 1 - cells[cell].getDiffState();
            if (invertDiffState < 0) {
                invertDiffState = 0;
            }

            factor = factor * invertDiffState;

            cells[cell].addTempX(aa * factor);
            cells[cell].addTempY(bb * factor);
            cells[cell].addTempZ(params.dgr * factor);
        }
    }
}

void Model::buoyancy(std::vector<Cell> &cells, Parameters &params) {
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        double distanceToOrigin2D = Geometrics::centerDistanceToOrigin2D(cells[cell]);
        if (distanceToOrigin2D > 0) {
            double distanceToOrigin3D = Geometrics::centerDistanceToOrigin3D(cells[cell]);
            double relativeZDistance = -cells[cell].getTempZ() / distanceToOrigin3D;
            double XRelativeToZ = cells[cell].getTempX() * relativeZDistance;
            double YRelativeToZ = cells[cell].getTempY() * relativeZDistance;
            double relativeDistance1 = sqrt(XRelativeToZ * XRelativeToZ + YRelativeToZ * YRelativeToZ +
                                            distanceToOrigin2D * distanceToOrigin2D);
            double epithelialSec1Concentration = cells[cell].getProteinConcentrations()[2][0];
            double relativeDistance2 = params.boy * epithelialSec1Concentration / relativeDistance1;     //boy: buoyancy

            if (relativeDistance2 > 0) {
                double inverseDiffState = 1 - cells[cell].getDiffState();
                if (inverseDiffState < 0) {
                    inverseDiffState = 0;
                }
                double newX = XRelativeToZ * relativeDistance2 * inverseDiffState;
                double newY = YRelativeToZ * relativeDistance2 * inverseDiffState;
                double newZ = distanceToOrigin2D * relativeDistance2 * inverseDiffState;

                cells[cell].addTempX(-newX);
                cells[cell].addTempY(-newY);
                cells[cell].addTempZ(-newZ);

            }
        }
    }
}

void Model::repulsionAndAdhesion(std::vector<Cell> &cells, Parameters &params) {
    //These matrices store a value that represents the amount of deviation from the desired distance
    std::vector<std::vector<double>> compressionMatrixNeighbour = Model::setUpCompressionMatrix();
    std::vector<std::vector<double>> compressionMatrixNonNeighbour = Model::setUpCompressionMatrix();

    for (int cell1 = 0; cell1 < params.nrCellsInSimulation; ++cell1) {
        resetCompressionMatrix(compressionMatrixNeighbour);
        resetCompressionMatrix(compressionMatrixNonNeighbour);

        for (int cell2 = 0; cell2 < params.nrCellsInSimulation; ++cell2) {
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

            double currentDistance = Geometrics::centerDistance3D(cells[cell1], cells[cell2]);

            //Check for the situation
            bool cell2IsNeighbour = Model::isNeighbourOf(cells, cell1, cell2);
            bool cell1IsEKCell = cells[cell1].isKnotCell();
            bool cell2IsEKCell = cells[cell2].isKnotCell();
            bool cell1IsInCenter = cells[cell1].isInCentre();

            if (cell2IsNeighbour) {
                //For knowing the originalDistance we have to know which position cell2 has in the neighbour list of cell1
                int positionOfCell2;
                std::vector<int> neighboursOfCell1 = cells[cell1].getNeighbours();
                for (int neighbour = 0; neighbour < neighboursOfCell1.size(); ++neighbour) {
                    if (neighboursOfCell1[neighbour] == cell2) {
                        positionOfCell2 = neighbour;
                        break;
                    }
                }

                double originalDistance = cells[cell1].getOriginalDistances()[positionOfCell2];

                Model::repulsionAndAdhesionBetweenNeighbours(dx, dy, dz, currentDistance, originalDistance,
                                                             compressionMatrixNeighbour,
                                                             cell1IsEKCell, cell2IsEKCell, cell1IsInCenter, params.adh);
            } else {
                Model::repulsionBetweenNonNeighbours(dx, dy, dz, currentDistance, compressionMatrixNonNeighbour);
            }
        }

        Model::updateTempPositions(cells, params, cell1, compressionMatrixNonNeighbour, false);
        Model::updateTempPositions(cells, params, cell1, compressionMatrixNeighbour, true);
    }

}

void Model::nucleusTraction(std::vector<Cell> &cells, Parameters &params) {
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        double xShift = 0;
        double yShift = 0;
        double zShift = 0;

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
        xShift = XDeviationFromAverage * params.delta * params.ntr; // ntr: parameter for nucleus traction
        yShift = YDeviationFromAverage * params.delta * params.ntr;

        // only if the cell isn't a EK cell, the z-position is affected by nuclear traction
        if (cells[cell].isKnotCell() == false) {
            double inverseDiffState = 1 - cells[cell].getDiffState();
            if (inverseDiffState < 0) {
                inverseDiffState = 0;
            }
            zShift = ZDeviationFromAverage * params.delta * params.ntr * inverseDiffState;
        }

        // Add the shifts directly to the coordinates (it's not handled as tempX, etc.)
        cells[cell].addX(xShift);
        cells[cell].addY(yShift);
        cells[cell].addZ(zShift);
    }
}

void Model::anteriorPosteriorBias(std::vector<Cell> &cells, Parameters &params) {
    // only for cells that are not in the center
    int firstBorderCell = params.nrCellsInCenter;
    for (int cell = firstBorderCell; cell < params.nrCellsInSimulation; ++cell) {
        //Bwi: parameter (distance where anterior-posterior bias applies)
        if (fabs(cells[cell].getY()) < params.bwi) {
            if (cells[cell].getX() > 0) {
                cells[cell].multiplyTempX(params.abi); //Abi: Parameter for anterior bias
                cells[cell].multiplyTempZ(params.bgr); //Bgr: Parameter for border growth (bias in z-direction)
            } else if (cells[cell].getX() < 0) {
                cells[cell].multiplyTempX(params.abi); //Abi: Parameter for anterior bias
                cells[cell].multiplyTempZ(params.bgr); //Bgr: Parameter for border growth (bias in z-direction)
            }
        }
    }
}

void Model::applyForces(std::vector<Cell> &cells, Parameters &params) {
    // for each cell in simulation apply the force vector on the cell's position
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        cells[cell].updateCoordinates(params.delta);
        cells[cell].resetTempCoordinates();
    }
}

void Model::repulsionAndAdhesionBetweenNeighbours(double dx, double dy, double dz, double currentDistance,
                                                  double originalDistance,
                                                  std::vector<std::vector<double>> &compressionMatrixNeighbours,
                                                  bool cell1IsEKCell,
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
    if (originalDistance < 1.0e-8) {
        originalDistance = 0;
    }
    if (currentDistance < 1.0e-8) {
        currentDistance = 0;
    }

    //if both cells are enamel knot cells or the cells are too close
    if ((cell1IsEKCell && cell2IsEKCell) || (currentDistance < originalDistance)) {
        double deviation =
                currentDistance - originalDistance; //is negative -> the resulting vector is in opposite direction
        double relativeDeviation = deviation / currentDistance;

        //This is a vector showing in the opposite direction as cell1->cell2, with a length proportional to the deviation
        compressionMatrixNeighbours[0].push_back(dx * relativeDeviation);
        compressionMatrixNeighbours[1].push_back(dy * relativeDeviation);
        compressionMatrixNeighbours[2].push_back(dz * relativeDeviation);
    }

        //if they are not too close, there is adhesion (for all cells in the centre)
        //adh: Parameter describing how strong adhesion is
        //This is just a vector showing in the same direction as cell1->cell2, but elongated by Adh
    else if (cell1IsInCenter) {
        compressionMatrixNeighbours[0].push_back(dx * adh);
        compressionMatrixNeighbours[1].push_back(dy * adh);
        compressionMatrixNeighbours[2].push_back(dz * adh);
    }
}

void Model::repulsionBetweenNonNeighbours(double dx, double dy, double dz, double currentDistance,
                                          std::vector<std::vector<double>> &compressionMatrixNonNeighbours) {

    //If the cell is enough far away (in any dimension) there is no repulsion
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

    if (currentDistance < 1.4) {
        //the smaller the distance, the even higher the force
        double relativeDistance = 1 / pow((currentDistance + 1), 8);
        double factor = relativeDistance / currentDistance;
        factor = static_cast<int>(fabs(factor * 1.0e8)) * 1.0e-8;

        // a vector showing in the opposite direction (-> -dx) as cell1->cell2, and the longer the nearer they are
        compressionMatrixNonNeighbours[0].push_back(-dx * factor);
        compressionMatrixNonNeighbours[1].push_back(-dy * factor);
        compressionMatrixNonNeighbours[2].push_back(-dz * factor);
    }
}

void Model::updateTempPositions(std::vector<Cell> &cells, Parameters &params, int cell,
                                std::vector<std::vector<double>> compressionMatrix, bool isNeighbour) {
    double rep = params.rep;
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

void Model::EKDifferentiation(std::vector<Cell> &cells, Parameters &params, int cell) {
    //if the Act concentration in the epithelial layer is high enough
    //and if it is in the centre, then it becomes/is a knot cell
    if (cells[cell].getProteinConcentrations()[PAct][LEpithelium] > 1) {
        if (cells[cell].isInCentre()) {
            cells[cell].setKnotCell(true);
        }
    }
}

void Model::ActReactionAndDegradation(std::vector<Cell> &cells, Parameters &params, int cell) {
    Model::EKDifferentiation(cells, params, cell);

    double epithelialActConcentration = cells[cell].getProteinConcentrations()[PAct][LEpithelium];
    double epithelialInhConcentration = cells[cell].getProteinConcentrations()[PInh][LEpithelium];
    //double epithelialSec2Concentration = cells[cell].getProteinConcentrations()[PSec2][LEpithelium];

    double positiveTerm = params.act * epithelialActConcentration; //- epithelialSec2Concentration
    // not necessary since [Sec2] is always = 0
    if (positiveTerm < 0) {
        positiveTerm = 0;
    }
    double negativeTerm = 1 + params.inh * epithelialInhConcentration;
    if (negativeTerm == 0) {
        std::cout << "negative Term = 0 -> divide by zero" << std::endl;
        std::cout.flush();
    }
    double degradation = params.mu * epithelialActConcentration;

    //concentration difference: reaction - degradation
    double newConcentration = (positiveTerm / negativeTerm) - degradation;
    cells[cell].addTempConcentration(PAct, LEpithelium, newConcentration);
}

void Model::InhReactionAndDegradation(std::vector<Cell> &cells, Parameters &params, int cell) {
    //Inh is produced if diff state is higher than threshold or if the cell is an EK cell
    double diffState = cells[cell].getDiffState();
    double epithelialInhConcentration = cells[cell].getProteinConcentrations()[PInh][LEpithelium];
    double epithelialActConcentration = cells[cell].getProteinConcentrations()[PAct][LEpithelium];
    bool isKnotCell = cells[cell].isKnotCell();
    double newConcentration = 0;

    if (diffState > params.inT) {           //int: inductive threshold
        newConcentration = epithelialActConcentration * diffState - params.mu * epithelialInhConcentration;
    } else if (isKnotCell) {
        newConcentration = epithelialActConcentration - params.mu * epithelialInhConcentration;
    }
    cells[cell].addTempConcentration(PInh, LEpithelium, newConcentration);
}

void Model::Sec1ReactionAndDegradation(std::vector<Cell> &cells, Parameters &params, int cell) {
    double diffState = cells[cell].getDiffState();
    double epithelialSec1Concentration = cells[cell].getProteinConcentrations()[PSec1][LEpithelium];
    bool isKnotCell = cells[cell].isKnotCell();
    double newConcentration = 0;

    if (diffState > params.set) {
        newConcentration = params.sec * diffState - params.mu * epithelialSec1Concentration;
    } else if (isKnotCell) {
        newConcentration = params.sec - params.mu * epithelialSec1Concentration;
    }

    // [Sec1] does not get smaller (except by diffusion)
    if (newConcentration < 0) {
        newConcentration = 0;
    }
    cells[cell].addTempConcentration(PSec1, LEpithelium, newConcentration);
}


/**
 * This method is not used, because the parameter acec (influence of activator on sec2) is zero, meaning that there is no
 * Sec2 production at all.
 */
/*void Model::Sec2ReactionAndDegradation(std::vector<Cell> &cells, Parameters &params, int cell) {
    double epithelialActConcentration = cells[cell].getProteinConcentrations()[PAct][LEpithelium];
    double epithelialSec1Concentration = cells[cell].getProteinConcentrations()[PSec1][LEpithelium];
    double epithelialSec2Concentration = cells[cell].getProteinConcentrations()[PSec2][LEpithelium];

    double newConcentration =
            params.acec * epithelialActConcentration -                   //Act activates Sec2 production
            params.mu * epithelialSec2Concentration -                   //Minus normal degradation of Sec2
            params.sec2Inhibition * epithelialSec1Concentration;        //Minus Inhibition by Sec1
    if (newConcentration < 0) {
        newConcentration = 0;
    }

    cells[cell].addTempConcentration(3, 0, newConcentration);
}*/

std::vector<std::vector<int>> Model::searchMotherCells(std::vector<Cell> &cells, Parameters &params) {
    std::vector<std::vector<int>> motherCells;
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        for (int neighbour = 0; neighbour < cells[cell].getNeighbours().size(); ++neighbour) {
            int neighbourID = cells[cell].getNeighbours()[neighbour];
            bool neighbourIsInSimulation = cells[neighbourID].isInSimulation();
            if (neighbourIsInSimulation) {
                double squareDistance = Geometrics::squareCenterDistance3D(cells[cell], cells[neighbourID]);
                //if distance >2 and cell has to be smaller than the neighbour (in that way we look at each pair of cells only once)
                if (squareDistance >= 4 && cell < neighbourID) {
                    std::vector<int> pair = {cell, neighbourID};
                    motherCells.push_back(pair);
                    std::cout << "Cell division between cell " << cell << " and " << neighbourID << std::endl;
                    std::cout.flush();
                    params.cellDivisionCount += 1;
                }
            }
        }
    }
    return motherCells;
}

std::vector<int> Model::findCommonNeighbours(int M1, int M2, std::vector<Cell> &cells, Parameters &params) {
    std::vector<int> neighboursOfM1 = cells[M1].getNeighbours();
    int N1 = 0;         // Common neighbour 1
    int N2 = 0;         // Common neighbour 2

    for (int neighbour = 0; neighbour < neighboursOfM1.size(); ++neighbour) {
        int IDOfNeighbour = neighboursOfM1[neighbour];
        bool isNeighbourOfM2 = Model::isNeighbourOf(cells, M2, IDOfNeighbour);
        if (isNeighbourOfM2 && N1 == 0) {
            N1 = IDOfNeighbour;
        } else if (isNeighbourOfM2 && N2 == 0) {
            N2 = IDOfNeighbour;
        } else if (isNeighbourOfM2) {
            std::cout << "there are too many common neighbours" << std::endl;
            params.error = true;
        }
    }
    std::vector<int> commonNeighbours = {N1, N2};
    return commonNeighbours;
}

void Model::updateNeighbourRelations(int M1, int M2, int N1, int N2, Cell &newCell, std::vector<Cell> &cells,
                                     Parameters &params) {
    // Set the neighbours of the new cell (only the order is important)
    newCell.addNeighbour(M1);
    newCell.addNeighbour(N1);
    newCell.addNeighbour(M2);
    newCell.addNeighbour(N2);

    // replace the new Cell as new neighbour of the mother cells
    cells[M1].replaceNeighbour(M2, newCell.getID());
    cells[M2].replaceNeighbour(M1, newCell.getID());

    // The neighbours of N1 and N2 should include the mother cells (adjacent)
    std::vector<int> neighboursOfN1 = cells[N1].getNeighbours();
    std::vector<int> neighboursOfN2 = cells[N2].getNeighbours();

    // the common neighbours of the mother cells have the new cell as new neighbour (between the two adjacent mother cells)
    int M1Position = 0;         //M1 is the ...th neighbour of a common neighbour
    int M2Position = 0;         //M2 is the ...th neighbour of a common neighbour
    int newCellPosition = 0;    //the new cell will have this position in the neighbour sequence of a common neighbour

    // Insert the new cell as neighbour of N1 if N1 is InSimulation
    bool N1IsInSimulation = cells[N1].isInSimulation();
    if (N1IsInSimulation) {
        for (int neighbour = 0; neighbour < neighboursOfN1.size(); ++neighbour) {
            if (neighboursOfN1[neighbour] == M1) {
                M1Position = neighbour;
            }
            if (neighboursOfN1[neighbour] == M2) {
                M2Position = neighbour;
            }
        }

        // The new cell inherits the higher position. In the extreme case this is the last position (equal to the first)
        if (M1Position > M2Position) {
            newCellPosition = M1Position;
        } else if (M1Position < M2Position) {
            newCellPosition = M2Position;
        }

        cells[N1].insertNeighbour(newCell.getID(), newCellPosition + 1);
    }

    // Same for N2
    bool N2IsInSimulation = cells[N2].isInSimulation();
    if (N2IsInSimulation) {
        for (int neighbour = 0; neighbour < neighboursOfN2.size(); ++neighbour) {
            if (neighboursOfN2[neighbour] == M1) {
                M1Position = neighbour;
            }
            if (neighboursOfN2[neighbour] == M2) {
                M2Position = neighbour;
            }
        }

        if (M1Position > M2Position) {
            newCellPosition = M1Position;
        } else if (M1Position < M2Position) {
            newCellPosition = M2Position;
        }

        cells[N2].insertNeighbour(newCell.getID(), newCellPosition);
    }
}

void Model::setMeanProteinConcentrations(int M1, int M2, Cell &newCell, std::vector<Cell> &cells, Parameters &params) {
    std::vector<std::vector<double>> M1Concentrations = cells[M1].getProteinConcentrations();
    std::vector<std::vector<double>> M2Concentrations = cells[M2].getProteinConcentrations();

    for (int protein = 0; protein < 4; ++protein) {
        for (int layer = 0; layer < newCell.getMesenchymeThickness(); ++layer) {
            double M1Concentration = M1Concentrations[protein][layer];
            double M2Concentration = M2Concentrations[protein][layer];
            double newConcentration = (M1Concentration + M2Concentration) / 2;
            newCell.setProteinConcentration(protein, layer, newConcentration);
        }
    }
}

void Model::defineIfNewCellInCentre(int N1, int N2, Cell &newCell, std::vector<Cell> &cells, Parameters &params) {
    //The new cell is in the centre if it has no neighbours that are out of simulation
    bool N1InCentre = cells[N1].isInSimulation();
    bool N2InCentre = cells[N2].isInSimulation();
    // the mother cells are anyway in simulation (otherwise they would not be mother cells)

    if (N1InCentre == false || N2InCentre == false) {
        newCell.setInCentre(false);
    } else {
        newCell.setInCentre(true);
        params.nrCellsInCenter += 1;
    }
}

void Model::cellDivision(std::vector<Cell> &cells, Parameters &params) {
    //Check if two neighbouring cells are too far away (>2) and write the pair into vector motherCells
    std::vector<std::vector<int>> motherCells = Model::searchMotherCells(cells, params);

    // for all pairs, create a new cell between them and update the neighbour relationships
    for (int pair = 0; pair < motherCells.size(); ++pair) {

        // Increase the IDs of all out-of-simulation cells by 1
        for (int cell = 0; cell < cells.size(); ++cell) {
            int IDofCell = cells[cell].getID();
            if (IDofCell >= params.nrCellsInSimulation) {
                cells[cell].setID(IDofCell + 1);
            }
            // Also increase in the neighbour vectors the IDs of out-of-simulation cells by 1
            std::vector<int> neighbours = cells[cell].getNeighbours();
            for (int neighbour = 0; neighbour < neighbours.size(); ++neighbour) {
                if (neighbours[neighbour] >= params.nrCellsInSimulation) {
                    int IDofNeighbour = neighbours[neighbour];
                    cells[cell].setNeighbour(neighbour, IDofNeighbour + 1);
                }
            }
        }

        int M1 = motherCells[pair][0];      // Mother Cell 1
        int M2 = motherCells[pair][1];      // Mother Cell 2

        //Find common neighbours of both mother cells
        std::vector<int> neighboursOfM1 = cells[M1].getNeighbours();
        int N1 = Model::findCommonNeighbours(M1, M2, cells, params)[0];         // Common neighbour 1
        int N2 = Model::findCommonNeighbours(M1, M2, cells, params)[1];         // Common neighbour 2

        // Calculate the position of the new cell (between the mother cells)
        double newX = (cells[M1].getX() + cells[M2].getX()) / 2;
        double newY = (cells[M1].getY() + cells[M2].getY()) / 2;
        double newZ = (cells[M1].getZ() + cells[M2].getZ()) / 2;

        // Create the instance of the new cell
        Cell newCell(newX, newY, newZ, params.nrCellsInSimulation);
        std::cout << "new cell: " << params.nrCellsInSimulation << std::endl;
        params.nrCellsInSimulation += 1;
        //The new cell is anyway not a knot cell (set in the constructor)
        //The new cell is also in Simulation
        newCell.setInSimulation(true);
        //The new cell has the mean of the mother cell's protein concentrations
        Model::setMeanProteinConcentrations(M1, M2, newCell, cells, params);
        //The new cell is in centre if it has no neighbours that are out of simulation
        Model::defineIfNewCellInCentre(N1, N2, newCell, cells, params);
        // Update the neighbour relationships
        Model::updateNeighbourRelations(M1, M2, N1, N2, newCell, cells, params);

        //Insert the new cell into the cells vector (no problem for next new cells, because it is inserted at the end of
        // in-simulation-cells)
        cells.insert(cells.begin() + params.nrCellsInSimulation - 1, newCell);

        //calculate new OriginalDistances
        Model::calculateNewOriginalDistances(cells, params, newCell, M1, M2, N1, N2);
    }
}

void Model::calculateNewOriginalDistances(std::vector<Cell> &cells, Parameters &params, Cell &newCell, int M1, int M2,
                                          int N1, int N2) {
    std::vector<int> neighboursOfNewCell = newCell.getNeighbours();

    for (int neighbour = 0; neighbour < neighboursOfNewCell.size(); ++neighbour) {
        int oldCell = neighboursOfNewCell[neighbour];

        bool oldCellIsInSimulation = cells[oldCell].isInSimulation();

        if (oldCellIsInSimulation) {
            double distance2D = Geometrics::centerDistance2D(newCell, cells[oldCell]);

            //Do it for all neighbours of the new cell
            cells[newCell.getID()].addOriginalDistance(distance2D, neighbour);

            //We have to know which position newCell has in the neighbour list of the old cell
            int positionOfNewCell;
            std::vector<int> neighboursOfOldCell = cells[oldCell].getNeighbours();
            for (int neighbour = 0; neighbour < neighboursOfOldCell.size(); ++neighbour) {
                if (neighboursOfOldCell[neighbour] == newCell.getID()) {
                    positionOfNewCell = neighbour;
                    break;
                }
            }

            //For the mothercells: replace the original distance with the one to the other mothercell
            if (oldCell == M1 || oldCell == M2) {
                cells[oldCell].replaceOriginalDistance(distance2D, positionOfNewCell);
            }
            //For the common neighbours: insert a new original distance to the new cell
            if (oldCell == N1 || oldCell == N2) {
                cells[oldCell].addOriginalDistance(distance2D, positionOfNewCell);
            }
        } else {
            cells[newCell.getID()].addOriginalDistance(0, neighbour);
        }
    }

}

void Model::newEpithelialProliferation(std::vector<Cell> &cells, Parameters &params) {
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        bool cellIsEKCell = cells[cell].isKnotCell();
        if (cellIsEKCell) {
            continue;
        }

        double xComponent = 0;
        double yComponent = 0;
        double zComponent = 0;

        //Calculate unit vectors from cell to all its neighbours and add the components to xComponent, etc.
        std::vector<int> neighbours = cells[cell].getNeighbours();
        for (int neighbour = 0; neighbour < neighbours.size(); ++neighbour) {
            int neighbourID = neighbours[neighbour];
            bool neighbourIsInSimulation = cells[neighbourID].isInSimulation();

            if (neighbourIsInSimulation) {
                double xDifference = cells[cell].getX() - cells[neighbourID].getX();
                double yDifference = cells[cell].getY() - cells[neighbourID].getY();
                double zDifference = cells[cell].getZ() - cells[neighbourID].getZ();

                double length = Geometrics::vectorNorm3D(std::vector<double>{xDifference, yDifference, zDifference});

                // Normalize Differences
                double normX = xDifference / length;
                double normY = yDifference / length;
                double normZ = zDifference / length;

                xComponent += normX;
                yComponent += normY;
                zComponent += normZ;
            }
        }

        //Normalize the sum of unit vectors
        double lengthOfSum = Geometrics::vectorNorm3D(std::vector<double>{xComponent, yComponent, zComponent});

        double inverseDiffState = (1 - cells[cell].getDiffState());
        if (inverseDiffState < 0) {
            inverseDiffState = 0;
        }

        if (lengthOfSum == 0) {
            continue;
        }

        double xShift = (xComponent / lengthOfSum) * params.egr * inverseDiffState;
        double yShift = (yComponent / lengthOfSum) * params.egr * inverseDiffState;
        double zShift = (zComponent / lengthOfSum) * params.egr * inverseDiffState;

        if (cells[cell].isInCentre()) {
            cells[cell].addTempX(xShift);
            cells[cell].addTempY(yShift);
            cells[cell].addTempZ(zShift);
        } else {
            //Downgrowth (cervical loop formation)
            Model::downGrowth(cells, params, xShift, yShift, int cell);
        }
    }
}

void Model::downGrowth(std::vector<Cell> &cells, Parameters &params, double xShift, double yShift, int cell) {

}