//
// Created by Stefanie on 13.08.2018.
//

#include <cmath>
#include <algorithm>
#include <iostream>
#include "Model.h"
#include "Geometrics.h"
#include "ImplementParams.h"
#include "consts.h"
#include "Noise.h"
#include "Utility.h"


void Model::iterationStep(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams, ModelParams &modelParams) {
    //Noise::doNoise(cells, params);
    Model::diffusion(cells, implementParams);
    Model::reaction(cells, implementParams);
    Model::buccalLingualBias(cells, implementParams);
    Model::differentiation(cells, implementParams);
    Model::epithelialProliferation(cells, implementParams);
    //Model::newEpithelialProliferation(cells, params);
    Model::buoyancy(cells, implementParams);
    Model::repulsionAndAdhesion(cells, implementParams);
    Model::nucleusTraction(cells, implementParams);
    Model::anteriorPosteriorBias(cells, implementParams);
    Model::applyForces(cells, implementParams);
    Model::cellDivision(cells, implementParams, modelParams);
    Geometrics::calculateCellBorders(cells, implementParams.nrCellsInSimulation);
    Utility::errorTesting(cells, implementParams);
    //Noise::updateParams(implementParams);

}

void Model::diffusion(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {

    //Calculate for each cell its perimeter and area
    Geometrics::calculatePerimeterAndArea(cells, implementParams);

    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {

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
        for (int protein = 0; protein < nrOfProteins; ++protein) {
            for (int layer = 0; layer < cells[cell].getMesenchymeThickness(); ++layer) {
                //Layer 0 is Epithel, Layer 2 - 4 are Mesenchyme
                if (layer != 0) { // if we are not within the epithelial layer
                    upDiffusion(cells, cell, layer, protein, relativeDiffusionAreaMesenchyme);
                    if (layer < (cells[cell].getMesenchymeThickness() - 1)) { // if its not the lowest layer
                        downDiffusion(cells, cell, layer, protein, relativeDiffusionAreaMesenchyme);
                    } else { // if its the lowest layer -> vertical sink
                        sink(cells, cell, layer, protein, relativeDiffusionAreaMesenchyme, implementParams);
                    }
                    horizontalDiffusion(cells, cell, layer, protein, mTotalDiffusionArea, implementParams);
                } else if (layer == 0) { // if we are in the epithelium, do no up Diffusion
                    horizontalDiffusion(cells, cell, layer, protein, eTotalDiffusionArea, implementParams);
                    downDiffusion(cells, cell, layer, protein, relativeDiffusionAreaEpithel);
                }
            }
        }
    }

    // Calculate the final protein concentrations (including diffusion coefficients and delta)
    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
        for (int protein = 0; protein < nrOfProteins; ++protein) {
            for (int layer = 0; layer < cells[cell].getMesenchymeThickness(); ++layer) {
                double delta = cells[cell].getModelParams().delta;
                double diffusionRate;
                switch (protein) {
                    case PAct:
                        diffusionRate = cells[cell].getModelParams().ActDiffusion;
                        break;
                    case PInh:
                        diffusionRate = cells[cell].getModelParams().InhDiffusion;
                        break;
                    case PSec:
                        diffusionRate = cells[cell].getModelParams().SecDiffusion;
                        break;
                    default:
                        implementParams.error = true;
                        std::cout << "The diffusion rate is not accessible" << std::endl;
                        std::cout.flush();
                }

                double tempConcentration = cells[cell].getTempProteinConcentrations()[protein][layer];
                double newConcentration = delta * diffusionRate * tempConcentration;
                cells[cell].addProteinConcentration(protein, layer, newConcentration);
            }
        }
        //Reset the temporary protein concentration matrix
        cells[cell].resetTempProteinConcentrations();
    }
}


void Model::upDiffusion(Cell (&cells)[totalNrOfCells], int cell, int layer, int protein, double relativeDiffusionArea) {
    double oldConcentration = cells[cell].getProteinConcentrations()[protein][layer];
    double neighbourConcentration = cells[cell].getProteinConcentrations()[protein][layer - 1];
    double newConcentration = (relativeDiffusionArea * (neighbourConcentration - oldConcentration));

    cells[cell].addTempConcentration(protein, layer, newConcentration);
}

void
Model::downDiffusion(Cell (&cells)[totalNrOfCells], int cell, int layer, int protein, double relativeDiffusionArea) {
    double oldConcentration = cells[cell].getProteinConcentrations()[protein][layer];
    double neighbourConcentration = cells[cell].getProteinConcentrations()[protein][layer + 1]; // a layer below
    double newConcentration = (relativeDiffusionArea * (neighbourConcentration - oldConcentration));

    cells[cell].addTempConcentration(protein, layer, newConcentration);
}

void Model::sink(Cell (&cells)[totalNrOfCells], int cell, int layer, int protein, double relativeDiffusionArea,
                 ImplementParams &implementParams) {
    double oldConcentration = cells[cell].getProteinConcentrations()[protein][layer];
    double newConcentration = (relativeDiffusionArea *
                               (-oldConcentration *
                                implementParams.sinkAmount));

    cells[cell].addTempConcentration(protein, layer, newConcentration);
}

void
Model::horizontalDiffusion(Cell (&cells)[totalNrOfCells], int cell, int layer, int protein, double totalDiffusionArea,
                           ImplementParams &implementParams) {
    double oldConcentration = cells[cell].getProteinConcentrations()[protein][layer];
    double newConcentration = 0;
    //bool borderDiffusionDone = false;
    for (int neighbour = 0; neighbour < cells[cell].getNrOfNeighbours(); ++neighbour) {
        int neighbourID = cells[cell].getNeighbours()[neighbour];

        // if neighbour is in simulation
        if (neighbourID < totalNrOfCells) {
            double neighbourConcentration = cells[neighbourID].getProteinConcentrations()[protein][layer];
            double pPerimeterPart = (cells[cell].getPerimeterParts()[neighbour] / totalDiffusionArea);
            newConcentration = (pPerimeterPart * (neighbourConcentration - oldConcentration));
            cells[cell].addTempConcentration(protein, layer, newConcentration);
        }
            // if the neighbour is not within simulation and the borderDiffusion has not yet been calculated, there is a sink
        else /*if (borderDiffusionDone == false)*/ {
            double pMargin = cells[cell].getMargin() / totalDiffusionArea;
            sink(cells, cell, layer, protein, pMargin, implementParams);
            //borderDiffusionDone = true;
        }
    }
}

void Model::reaction(Cell (&cells)[totalNrOfCells], ImplementParams &params) {
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        ActReactionAndDegradation(cells, params, cell);
        InhReactionAndDegradation(cells, params, cell);
        SecReactionAndDegradation(cells, params, cell);
    }

    //Update the final protein concentrations (including delta)
    for (int cell = 0; cell < params.nrCellsInSimulation; ++cell) {
        for (int protein = 0; protein < nrOfProteins; ++protein) {
            for (int layer = 0; layer < cells[cell].getMesenchymeThickness(); ++layer) {
                double delta = cells[cell].getModelParams().delta;
                double newConcentration =
                        delta * cells[cell].getTempProteinConcentrations()[protein][layer];
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

void Model::buccalLingualBias(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {
    //for all border cells
    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
        double swi = cells[cell].getModelParams().swi;
        double lbi = cells[cell].getModelParams().lbi;
        double bbi = cells[cell].getModelParams().bbi;
        bool cellIsInCentre = cells[cell].isInCentre();
        if (cellIsInCentre) {
            continue;
        } else if (cells[cell].getY() < -swi) {                     //swi: distance of initial BMPs from mid line
            cells[cell].setProteinConcentration(PAct, LEpithelium,
                                                lbi);  //lbi: lingual bias by initial BMP distribution
        } else if (cells[cell].getY() > swi) {
            cells[cell].setProteinConcentration(PAct, LEpithelium,
                                                bbi);  //bbi: buccal bias by initial BMP distribution
        }
    }
}

void Model::differentiation(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {
    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
        //Increase the diff state of each cell
        double dff = cells[cell].getModelParams().dff;
        double epithelialSecConcentration = cells[cell].getProteinConcentrations()[PSec][LEpithelium];
        double addDiff = dff * epithelialSecConcentration;
        cells[cell].addDiffState(addDiff);
    }
}

void Model::epithelialProliferation(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {
    double dx = 0;
    double dy = 0;
    double dz = 0;

    //for all cells in the center
    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
        double xDeviation = 0;
        double yDeviation = 0;
        double zDeviation = 0;
        double totalDeviation = 0;

        bool isInCentre = cells[cell].isInCentre();
        bool isKnotCell = cells[cell].isKnotCell();

        if (!isInCentre) {
            continue;
        }

        if (isKnotCell) {
            continue;
        }

        for (int neighbour = 0; neighbour < cells[cell].getNrOfNeighbours(); ++neighbour) {
            int neighbourID = cells[cell].getNeighbours()[neighbour];
            // if neighbour is out of simulation (cannot be)
            if (neighbourID > totalNrOfCells) {
                std::cout << "Something very strange in Epithelial Proliferation happened 1" << std::endl;
                implementParams.error = true;
                continue;
            }
            dz = cells[cell].getZ() - cells[neighbourID].getZ();
            // if the neighbour is higher than cell, calculate the relative x/y/z deviations
            if (dz < 0) {
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
            double egr = cells[cell].getModelParams().egr;
            deviationFactor =
                    egr / totalDeviation;      //egr: epithelial proliferation rate

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
    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {

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

        for (int neighbour = 0; neighbour < cells[cell].getNrOfNeighbours(); ++neighbour) {
            int neighbourID = cells[cell].getNeighbours()[neighbour];
            //if neighbour is not in simulation
            if (neighbourID > totalNrOfCells) {
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
            } else { //if neighbour is in centre
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
            double temp = angle1;
            angle1 = angle2;
            angle2 = temp;
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
        double epithelialSecConcentration = cells[cell].getProteinConcentrations()[PSec][LEpithelium];
        if (d > 0) {
            double mgr = cells[cell].getModelParams().mgr;
            factor = (d + mgr * epithelialSecConcentration) /
                     d;        //mgr: mesenchymal proliferation rate
            aa = aa * factor;
            bb = bb * factor;
        }

        double dgr = cells[cell].getModelParams().dgr;
        d = sqrt(aa * aa + bb * bb + dgr *
                                     dgr);                  //dgr: downgrowth
        if (d > 0) {
            double egr = cells[cell].getModelParams().egr;
            factor = egr / d;
            double invertDiffState = 1 - cells[cell].getDiffState();
            if (invertDiffState < 0) {
                invertDiffState = 0;
            }

            factor = factor * invertDiffState;

            cells[cell].addTempX(aa * factor);
            cells[cell].addTempY(bb * factor);
            cells[cell].addTempZ(dgr * factor);
        }
    }
}

void Model::buoyancy(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {
    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
        double distanceToOrigin2D = Geometrics::centerDistanceToOrigin2D(cells[cell]);
        if (distanceToOrigin2D > 0) {
            double distanceToOrigin3D = Geometrics::centerDistanceToOrigin3D(cells[cell]);
            double relativeZDistance = -cells[cell].getTempZ() / distanceToOrigin3D;
            double XRelativeToZ = cells[cell].getTempX() * relativeZDistance;
            double YRelativeToZ = cells[cell].getTempY() * relativeZDistance;
            double relativeDistance1 = sqrt(XRelativeToZ * XRelativeToZ + YRelativeToZ * YRelativeToZ +
                                            distanceToOrigin2D * distanceToOrigin2D);
            double epithelialSecConcentration = cells[cell].getProteinConcentrations()[PSec][LEpithelium];
            double boy = cells[cell].getModelParams().boy;
            double relativeDistance2 = boy * epithelialSecConcentration /
                                       relativeDistance1;     //boy: buoyancy

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

void Model::repulsionAndAdhesion(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {
    //These matrices store a value that represents the amount of deviation from the desired distance
    std::vector<std::vector<double>> compressionMatrixNeighbour = Model::setUpCompressionMatrix();
    std::vector<std::vector<double>> compressionMatrixNonNeighbour = Model::setUpCompressionMatrix();

    for (int cell1 = 0; cell1 < implementParams.nrCellsInSimulation; ++cell1) {
        resetCompressionMatrix(compressionMatrixNeighbour);
        resetCompressionMatrix(compressionMatrixNonNeighbour);

        for (int cell2 = 0; cell2 < implementParams.nrCellsInSimulation; ++cell2) {
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
                int *neighboursOfCell1 = cells[cell1].getNeighbours();
                bool positionFound = false;
                for (int neighbour = 0; neighbour < cells[cell1].getNrOfNeighbours(); ++neighbour) {
                    if (neighboursOfCell1[neighbour] == cell2) {
                        positionOfCell2 = neighbour;
                        positionFound = true;
                        break;
                    }
                }

                if (!positionFound) {
                    implementParams.error = true;
                    std::cout << "There was an error in updating neighbour relationships" << std::endl;
                    return;
                }
                double originalDistance = cells[cell1].getOriginalDistances()[positionOfCell2];

                double adh = cells[cell1].getModelParams().adh;
                Model::repulsionAndAdhesionBetweenNeighbours(dx, dy, dz, currentDistance, originalDistance,
                                                             compressionMatrixNeighbour,
                                                             cell1IsEKCell, cell2IsEKCell, cell1IsInCenter,
                                                             adh);
            } else {
                Model::repulsionBetweenNonNeighbours(dx, dy, dz, currentDistance, compressionMatrixNonNeighbour,
                                                     implementParams);
            }
        }

        Model::updateTempPositions(cells, cell1, compressionMatrixNonNeighbour, false);
        Model::updateTempPositions(cells, cell1, compressionMatrixNeighbour, true);
    }

}

void Model::nucleusTraction(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {
    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {

        if (cells[cell].getDiffState() == 1) {
            continue;
        }

        double xShift = 0;
        double yShift = 0;
        double zShift = 0;

        double totalX = 0;
        double totalY = 0;
        double totalZ = 0;
        int numberOfNeighboursInSimulation = 0;

        bool cellIsInCenter = cells[cell].isInCentre();
        if (cellIsInCenter) {
            for (int neighbour = 0; neighbour < cells[cell].getNrOfNeighbours(); ++neighbour) {
                int neighbourID = cells[cell].getNeighbours()[neighbour];

                //only neighbours that are within simulation are taken into account
                if (neighbourID < totalNrOfCells) {
                    numberOfNeighboursInSimulation += 1;
                    totalX += cells[neighbourID].getX();
                    totalY += cells[neighbourID].getY();
                    totalZ += cells[neighbourID].getZ();
                }
            }
        } else {
            for (int neighbour = 0; neighbour < cells[cell].getNrOfNeighbours(); ++neighbour) {
                int neighbourID = cells[cell].getNeighbours()[neighbour];

                if (neighbourID > totalNrOfCells) {
                    continue;
                } else {
                    bool neighbourIsInCenter = cells[neighbourID].isInCentre();

                    //only the neighbours that are within simulation but not in the center are taken into account
                    if (neighbourID < totalNrOfCells && !neighbourIsInCenter) {
                        numberOfNeighboursInSimulation += 1;
                        totalX += cells[neighbourID].getX();
                        totalY += cells[neighbourID].getY();
                        totalZ += cells[neighbourID].getZ();
                    }
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
        double ntr = cells[cell].getModelParams().ntr;
        double delta = cells[cell].getModelParams().delta;
        xShift = XDeviationFromAverage * delta *
                 ntr; // ntr: parameter for nucleus traction
        yShift = YDeviationFromAverage * delta * ntr;

        // only if the cell isn't a EK cell, the z-position is affected by nuclear traction
        if (!cells[cell].isKnotCell()) {
            double inverseDiffState = 1 - cells[cell].getDiffState();
            if (inverseDiffState < 0) {
                inverseDiffState = 0;
            }
            zShift = ZDeviationFromAverage * delta * ntr *
                     inverseDiffState;
        }

        // Add the shifts directly to the coordinates (it's not handled as tempX, etc.)
        cells[cell].addX(xShift);
        cells[cell].addY(yShift);
        cells[cell].addZ(zShift);
    }
}

void Model::anteriorPosteriorBias(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {
    // only for cells that are not in the center
    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
        bool cellIsCentreCell = cells[cell].isInCentre();
        if (cellIsCentreCell) {
            continue;
        }
        //Bwi: parameter (distance where anterior-posterior bias applies)
        double bwi = cells[cell].getModelParams().bwi;
        double abi = cells[cell].getModelParams().abi;
        double pbi = cells[cell].getModelParams().pbi;
        double bgr = cells[cell].getModelParams().bgr;
        if (fabs(cells[cell].getY()) < bwi) {
            if (cells[cell].getX() > 0) {
                cells[cell].multiplyTempX(abi); //Abi: Parameter for anterior bias
                cells[cell].multiplyTempZ(
                        bgr); //Bgr: Parameter for border growth (bias in z-direction)
            } else if (cells[cell].getX() < 0) {
                cells[cell].multiplyTempX(pbi); //Abi: Parameter for anterior bias
                cells[cell].multiplyTempZ(
                        bgr); //Bgr: Parameter for border growth (bias in z-direction)
            }
        }
    }
}

void Model::applyForces(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {
    // for each cell in simulation apply the force vector on the cell's position
    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
        cells[cell].updateCoordinates();
        cells[cell].resetTempCoordinates();
    }
}

void Model::repulsionAndAdhesionBetweenNeighbours(double dx, double dy, double dz, double currentDistance,
                                                  double originalDistance,
                                                  std::vector<std::vector<double>> &compressionMatrixNeighbours,
                                                  bool cell1IsEKCell,
                                                  bool cell2IsEKCell, bool cell1IsInCenter, double adh) {
    //rounding
    if (fabs(dx) < round1) {
        dx = 0;
    }
    if (fabs(dy) < round1) {
        dy = 0;
    }
    if (fabs(dz) < round1) {
        dz = 0;
    }
    if (originalDistance < round2) {
        originalDistance = 0;
    }
    if (currentDistance < round2) {
        currentDistance = 0;
    }

    //if both cells are enamel knot cells or the cells are too close
    if ((cell1IsEKCell && cell2IsEKCell) || (currentDistance < originalDistance)) {
        double deviation =
                currentDistance - originalDistance; //is negative -> the resulting vector is in opposite direction
        double relativeDeviation = deviation / currentDistance;

        //This is a vector showing in the opposite direction as cell1->cell2, with a length proportional to the deviation
        compressionMatrixNeighbours[X].push_back(dx * relativeDeviation);
        compressionMatrixNeighbours[Y].push_back(dy * relativeDeviation);
        compressionMatrixNeighbours[Z].push_back(dz * relativeDeviation);
    }

        //if they are not too close, there is adhesion (for all cells in the centre)
        //adh: Parameter describing how strong adhesion is
        //This is just a vector showing in the same direction as cell1->cell2, but elongated by Adh
    else if (cell1IsInCenter) {
        compressionMatrixNeighbours[X].push_back(dx * adh);
        compressionMatrixNeighbours[Y].push_back(dy * adh);
        compressionMatrixNeighbours[Z].push_back(dz * adh);
    }
}

void Model::repulsionBetweenNonNeighbours(double dx, double dy, double dz, double currentDistance,
                                          std::vector<std::vector<double>> &compressionMatrixNonNeighbours,
                                          ImplementParams &implementParams) {

    //If the cell is enough far away (in any dimension) there is no repulsion
    if (dx > implementParams.repDistance || dy > implementParams.repDistance || dz > implementParams.repDistance) {
        return;
    }

    //rounding
    if (fabs(dx) < round1) {
        dx = 0;
    }
    if (fabs(dy) < round1) {
        dy = 0;
    }
    if (fabs(dz) < round1) {
        dz = 0;
    }

    if (currentDistance < implementParams.repDistance) {
        //the smaller the distance, the even higher the force
        double relativeDistance = 1 / pow((currentDistance + 1), implementParams.powerOfRep);
        double factor = relativeDistance / currentDistance;
        //rounding
        factor = static_cast<int>(fabs(factor * 1.0e8)) * 1.0e-8;

        // a vector showing in the opposite direction (-> -dx) as cell1->cell2, and the longer the nearer they are
        compressionMatrixNonNeighbours[0].push_back(-dx * factor);
        compressionMatrixNonNeighbours[1].push_back(-dy * factor);
        compressionMatrixNonNeighbours[2].push_back(-dz * factor);
    }
}

void Model::updateTempPositions(Cell (&cells)[totalNrOfCells], int cell,
                                std::vector<std::vector<double>> compressionMatrix, bool isNeighbour) {
    double rep = cells[cell].getModelParams().rep;
    // Rep: Parameter for repulsion between different tissues and morphology parts

    //if it is a neighbour cell, the repulsion parameter is maximally 1
    if (isNeighbour) {
        if (rep > 1) {
            rep = 1;
        }
    }

    cells[cell].addTempX(Geometrics::vectorSum(compressionMatrix[X]) * rep);
    cells[cell].addTempY(Geometrics::vectorSum(compressionMatrix[Y]) * rep);
    cells[cell].addTempZ(Geometrics::vectorSum(compressionMatrix[Z]) * rep);
}

std::vector<std::vector<double>> Model::setUpCompressionMatrix() {
    std::vector<double> XCompression;
    std::vector<double> YCompression;
    std::vector<double> ZCompression;

    std::vector<std::vector<double>> compressionMatrix = {XCompression, YCompression, ZCompression};

    return compressionMatrix;
}

void Model::resetCompressionMatrix(std::vector<std::vector<double>> &compressionMatrix) {
    for (int dimension = 0; dimension < dimensions; ++dimension) {
        compressionMatrix[dimension].clear();
    }
}

bool Model::isNeighbourOf(Cell (&cells)[totalNrOfCells], int cell, int potentialNeighbour) {
    int *neighbours = cells[cell].getNeighbours();
    for (int neighbour = 0; neighbour < cells[cell].getNrOfNeighbours(); ++neighbour) {
        if (neighbours[neighbour] == potentialNeighbour) {
            return true;
        }
    }
    return false;
}

void Model::EKDifferentiation(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams, int cell) {
    //if the Act concentration in the epithelial layer is high enough
    //and if it is in the centre, then it becomes/is a knot cell
    if (cells[cell].getProteinConcentrations()[PAct][LEpithelium] > implementParams.EKThreshold) {
        if (cells[cell].isInCentre()) {
            cells[cell].setKnotCell(true);
        }
    }
}

void Model::ActReactionAndDegradation(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams, int cell) {
    Model::EKDifferentiation(cells, implementParams, cell);

    double epithelialActConcentration = cells[cell].getProteinConcentrations()[PAct][LEpithelium];
    double epithelialInhConcentration = cells[cell].getProteinConcentrations()[PInh][LEpithelium];

    double act = cells[cell].getModelParams().act;
    double inh = cells[cell].getModelParams().inh;
    double mu = cells[cell].getModelParams().mu;
    double positiveTerm = act * epithelialActConcentration;
    if (positiveTerm < 0) {
        positiveTerm = 0;
    }
    double negativeTerm = 1 + inh * epithelialInhConcentration;
    if (negativeTerm == 0) {
        std::cout << "negative Term = 0 -> divide by zero" << std::endl;
        std::cout.flush();
    }
    double degradation = mu * epithelialActConcentration;

    //concentration difference: reaction - degradation
    double newConcentration = (positiveTerm / negativeTerm) - degradation;
    cells[cell].addTempConcentration(PAct, LEpithelium, newConcentration);
}

void Model::InhReactionAndDegradation(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams, int cell) {
    double diffState = cells[cell].getDiffState();
    double epithelialInhConcentration = cells[cell].getProteinConcentrations()[PInh][LEpithelium];
    double epithelialActConcentration = cells[cell].getProteinConcentrations()[PAct][LEpithelium];
    bool isKnotCell = cells[cell].isKnotCell();
    double newConcentration = 0;
    double mu = cells[cell].getModelParams().mu;
    double inT = cells[cell].getModelParams().inT;

    if (implementParams.newInhAndSecProduction == 0) {
        //original version
        //Inh is produced if diff state is higher than threshold or if the cell is an EK cell

        if (isKnotCell) {
            newConcentration =
                    epithelialActConcentration - mu * epithelialInhConcentration;
        } else if (diffState > inT) {           //int: inductive threshold
            newConcentration = epithelialActConcentration * diffState -
                               mu * epithelialInhConcentration;
        }
    } else {
        // new version
        //Inh is produced if diff state is higher than threshold or if the cell is an EK cell

        if (isKnotCell || diffState > inT) {
            newConcentration =
                    epithelialActConcentration - mu * epithelialInhConcentration;
        }
    }

    cells[cell].addTempConcentration(PInh, LEpithelium, newConcentration);

}

void Model::SecReactionAndDegradation(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams, int cell) {
    double diffState = cells[cell].getDiffState();
    double epithelialSecConcentration = cells[cell].getProteinConcentrations()[PSec][LEpithelium];
    bool isKnotCell = cells[cell].isKnotCell();
    double newConcentration = 0;
    double sec = cells[cell].getModelParams().sec;
    double mu = cells[cell].getModelParams().mu;
    double set = cells[cell].getModelParams().set;

    if (implementParams.newInhAndSecProduction == 0) {
        //original version
        if (isKnotCell) {
            newConcentration =
                    sec - mu * epithelialSecConcentration;
        } else if (diffState > set) {
            newConcentration = sec * diffState -
                               mu * epithelialSecConcentration;
        }
    } else {
        if (isKnotCell || diffState > set) {
            newConcentration =
                    sec - mu * epithelialSecConcentration;
        }
    }

    // [Sec] does not get smaller (except by diffusion)
    if (newConcentration < 0) {
        newConcentration = 0;
    }
    cells[cell].addTempConcentration(PSec, LEpithelium, newConcentration);
}

std::vector<int> Model::searchMotherCells(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {

    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
        for (int neighbour = 0; neighbour < cells[cell].getNrOfNeighbours(); ++neighbour) {
            int neighbourID = cells[cell].getNeighbours()[neighbour];
            //if neighbour is in simulation
            if (neighbourID < totalNrOfCells) {
                double distance = Geometrics::centerDistance3D(cells[cell], cells[neighbourID]);
                //if distance >2 and cell has to be smaller than the neighbour (in that way we look at each pair of cells only once)
                if (distance >= implementParams.distanceCellDivision && cell < neighbourID) {
                    std::vector<int> motherCells;
                    motherCells.push_back(cell);
                    motherCells.push_back(neighbourID);
                    //std::cout << "Cell division between cell " << cell << " and " << neighbourID << std::endl;
                    //std::cout.flush();
                    // If a pair is found, return it instantly
                    return motherCells;
                }
            }
        }
    }
    // if no pair is found, return a vector (0,0)
    std::vector<int> motherCells = {0, 0};
    return motherCells;
}

std::vector<int>
Model::findCommonNeighbours(int M1, int M2, Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {
    int *neighboursOfM1 = cells[M1].getNeighbours();
    int N1 = 0;         // Common neighbour 1
    int N2 = 0;         // Common neighbour 2

    for (int neighbour = 0; neighbour < cells[M1].getNrOfNeighbours(); ++neighbour) {
        int IDOfNeighbour = neighboursOfM1[neighbour];
        bool isNeighbourOfM2 = Model::isNeighbourOf(cells, M2, IDOfNeighbour);
        if (isNeighbourOfM2 && N1 == 0) {
            N1 = IDOfNeighbour;
        } else if (isNeighbourOfM2 && N2 == 0) {
            N2 = IDOfNeighbour;
        } else if (isNeighbourOfM2) {
            std::cout << "there are too many common neighbours" << std::endl;
            implementParams.error = true;
        }
    }
    std::vector<int> commonNeighbours = {N1, N2};
    return commonNeighbours;
}

void Model::updateNeighbourRelations(int M1, int M2, int N1, int N2, Cell &newCell, Cell (&cells)[totalNrOfCells]) {
    // Set the neighbours of the new cell (only the order is important)
    newCell.addNeighbour(M1);
    newCell.addNeighbour(N1);
    newCell.addNeighbour(M2);
    newCell.addNeighbour(N2);

    // replace the new Cell as new neighbour of the mother cells
    cells[M1].replaceNeighbour(M2, newCell.getID());
    cells[M2].replaceNeighbour(M1, newCell.getID());

    // The neighbours of N1 and N2 should include the mother cells (adjacent)
    int *neighboursOfN1 = cells[N1].getNeighbours();
    int *neighboursOfN2 = cells[N2].getNeighbours();

    // the common neighbours of the mother cells have the new cell as new neighbour (between the two adjacent mother cells)
    int M1Position = 0;         //M1 is the ...th neighbour of a common neighbour
    int M2Position = 0;         //M2 is the ...th neighbour of a common neighbour
    int newCellPosition = 0;    //the new cell will have this position in the neighbour sequence of a common neighbour

    // Insert the new cell as neighbour of N1 if N1 is InSimulation
    if (N1 < totalNrOfCells) {
        for (int neighbour = 0; neighbour < cells[N1].getNrOfNeighbours(); ++neighbour) {
            if (neighboursOfN1[neighbour] == M1) {
                M1Position = neighbour;
            }
            if (neighboursOfN1[neighbour] == M2) {
                M2Position = neighbour;
            }
        }

        // The new cell inherits the higher position. In the extreme case this is the last position (equal to the first)
        if (M1Position > M2Position) {
            // if M1 is the last neighbour of N1 and M2 the first, insert the new cell at last position -> M1Position + 1
            if (neighboursOfN1[M1Position + 1] == -1) {
                newCellPosition = M1Position + 1;
            } else { // else, insert it at position of M1
                newCellPosition = M1Position;
            }

        } else if (M1Position < M2Position) {
            newCellPosition = M2Position;
        }

        cells[N1].insertNeighbour(newCell.getID(), newCellPosition);
    }

    // Same for N2
    if (N2 < totalNrOfCells) {
        for (int neighbour = 0; neighbour < cells[N2].getNrOfNeighbours(); ++neighbour) {
            if (neighboursOfN2[neighbour] == M1) {
                M1Position = neighbour;
            }
            if (neighboursOfN2[neighbour] == M2) {
                M2Position = neighbour;
            }
        }

        // if M1 is the last neighbour of N2 and M2 the first, insert the new cell at last position -> M1Position + 1
        if (M1Position > M2Position) {
            if (neighboursOfN2[M1Position + 1] == -1) {
                newCellPosition = M1Position + 1;
            } else { // else, insert it at position of M1
                newCellPosition = M1Position;
            }
        } else if (M1Position < M2Position) {
            newCellPosition = M2Position;
        }

        cells[N2].insertNeighbour(newCell.getID(), newCellPosition);
    }
}

void
Model::setMeanProteinConcentrations(int M1, int M2, Cell &newCell, Cell (&cells)[totalNrOfCells]) {
    std::vector<std::vector<double>> M1Concentrations = cells[M1].getProteinConcentrations();
    std::vector<std::vector<double>> M2Concentrations = cells[M2].getProteinConcentrations();

    for (int protein = 0; protein < nrOfProteins; ++protein) {
        for (int layer = 0; layer < newCell.getMesenchymeThickness(); ++layer) {
            double numberOfMotherCells = 2;
            double M1Concentration = M1Concentrations[protein][layer];
            double M2Concentration = M2Concentrations[protein][layer];
            double newConcentration = (M1Concentration + M2Concentration) / numberOfMotherCells;
            newCell.setProteinConcentration(protein, layer, newConcentration);
        }
    }
}

void Model::defineIfNewCellInCentre(Cell &newCell, Cell (&cells)[totalNrOfCells]) {
    //The new cell is in the centre if it has no neighbours that are out of simulation
    int *neighbours = newCell.getNeighbours();
    bool isInCentre = true;
    for (int neighbour = 0; neighbour < newCell.getNrOfNeighbours(); ++neighbour) {
        int IDNeighbour = neighbours[neighbour];
        if (IDNeighbour > totalNrOfCells) {
            isInCentre = false;
        }
    }

    newCell.setInCentre(isInCentre);
}

void Model::cellDivision(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams, ModelParams &modelParams) {
    while (true) {
        // do only cell division if maxNrOfCells is not reached yet
        if (implementParams.nrCellsInSimulation == maxNrOfCells) {
            return;
        }

        //Check if two neighbouring cells are too far away (>distanceCellDivision) and write the pair into vector motherCells
        std::vector<int> motherCells = Model::searchMotherCells(cells, implementParams);

        // If the vector is (0,0), there is no more pair of mother cells found -> return
        // else, do insert a new cell between these two mother cells
        if (motherCells[first] == 0 && motherCells[second] == 0) {
            return;
        } else {
            // Print that there is a cell division
            std::cout << "new cell: " << implementParams.nrCellsInSimulation << std::endl;
            std::cout << "at iteration: " << implementParams.currentIteration << std::endl;

            int M1 = motherCells[first];               // Mother Cell 1
            int M2 = motherCells[second];              // Mother Cell 2

            //Find common neighbours of both mother cells
            int N1 = Model::findCommonNeighbours(M1, M2, cells, implementParams)[first];         // Common neighbour 1
            int N2 = Model::findCommonNeighbours(M1, M2, cells, implementParams)[second];         // Common neighbour 2

            // Calculate the position of the new cell (between the mother cells)
            double numberOfMothercells = 2;
            double newX = (cells[M1].getX() + cells[M2].getX()) / numberOfMothercells;
            double newY = (cells[M1].getY() + cells[M2].getY()) / numberOfMothercells;
            double newZ = (cells[M1].getZ() + cells[M2].getZ()) / numberOfMothercells;

            // Create the instance of the new cell
            Cell newCell;
            newCell.setX(newX);
            newCell.setY(newY);
            newCell.setZ(newZ);
            newCell.setID(implementParams.nrCellsInSimulation);
            newCell.setModelParams(modelParams);

            implementParams.nrCellsInSimulation += 1;

            //The new cell is anyway not a knot cell (set in the constructor)
            //The new cell is also in Simulation
            newCell.setInSimulation(true);
            //The new cell has the mean of the mother cell's protein concentrations
            Model::setMeanProteinConcentrations(M1, M2, newCell, cells);
            // Update the neighbour relationships
            Model::updateNeighbourRelations(M1, M2, N1, N2, newCell, cells);
            // Check if a common neighbour (N1 or N2) has a full neighbour - vector, if so, end the simulation
            Utility::checkForFullNeighbourVector(cells, implementParams, N1);
            Utility::checkForFullNeighbourVector(cells, implementParams, N2);
            // Test if a neighbour is multiple times in the neighbour-vector
            bool multipleNeighbours = Model::multipleNeighbour(cells, implementParams);
            if (multipleNeighbours) {
                return;
            }
            //The new cell is in centre if it has no neighbours that are out of simulation
            Model::defineIfNewCellInCentre(newCell, cells);

            //Insert the new cell into the cells array (no problem for next new cells, because it is inserted at the end of
            // in-simulation-cells)
            cells[implementParams.nrCellsInSimulation - 1] = newCell;

            //calculate new OriginalDistances
            Model::calculateNewOriginalDistances(cells, newCell, M1, M2, N1, N2);
        }
        // Do only further cell division if the maximal nr of cells is not achieved yet in this iteration
        if (implementParams.nrCellsInSimulation == implementParams.minNrOfCells) {
            return;
        }
        // Do only continue cell divisions if no neighbour vector is full
        if (implementParams.endOfSimulation) {
            return;
        }
    }
}

void
Model::calculateNewOriginalDistances(Cell (&cells)[totalNrOfCells], Cell &newCell, int M1, int M2,
                                     int N1, int N2) {
    int *neighboursOfNewCell = newCell.getNeighbours();

    for (int neighbour = 0; neighbour < newCell.getNrOfNeighbours(); ++neighbour) {
        int oldCell = neighboursOfNewCell[neighbour];

        // if old Cell is in Simulation
        if (oldCell < totalNrOfCells) {
            double distance2D = Geometrics::centerDistance2D(newCell, cells[oldCell]);

            //Do it for all neighbours of the new cell
            cells[newCell.getID()].addOriginalDistance(distance2D, neighbour);

            //We have to know which position newCell has in the neighbour list of the old cell
            int positionOfNewCell;
            int *neighboursOfOldCell = cells[oldCell].getNeighbours();
            for (int neighbourOfOldCell = 0;
                 neighbourOfOldCell < cells[oldCell].getNrOfNeighbours(); ++neighbourOfOldCell) {
                if (neighboursOfOldCell[neighbourOfOldCell] == newCell.getID()) {
                    positionOfNewCell = neighbourOfOldCell;
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

void Model::newEpithelialProliferation(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {
    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
        bool cellIsEKCell = cells[cell].isKnotCell();
        if (cellIsEKCell) {
            continue;
        }

        double xComponent = 0;
        double yComponent = 0;
        double zComponent = 0;

        //Calculate unit vectors from cell to all its neighbours and add the components to xComponent, etc.
        int *neighbours = cells[cell].getNeighbours();
        for (int neighbour = 0; neighbour < cells[cell].getNrOfNeighbours(); ++neighbour) {
            int neighbourID = neighbours[neighbour];

            // if neighbour is in simulation
            if (neighbourID < implementParams.nrCellsInSimulation) {
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

        double egr = cells[cell].getModelParams().egr;
        double xShift = (xComponent / lengthOfSum) * egr * inverseDiffState;
        double yShift = (yComponent / lengthOfSum) * egr * inverseDiffState;
        double zShift = (zComponent / lengthOfSum) * egr * inverseDiffState;

        cells[cell].addTempX(xShift);
        cells[cell].addTempY(yShift);
        cells[cell].addTempZ(zShift);

        if (!cells[cell].isInCentre()) {
            //Downgrowth (cervical loop formation)
            Model::downGrowth(cells, xShift, yShift, cell);
        }
    }
}

void Model::downGrowth(Cell (&cells)[totalNrOfCells], double xShift, double yShift, int cell) {

    double epithelialSecConcentration = cells[cell].getProteinConcentrations()[PSec][LEpithelium];
    double inverseDiffState = 1 - cells[cell].getDiffState();
    if (inverseDiffState < 0) {
        inverseDiffState = 0;
    }

    double shift2D = Geometrics::vectorNorm2D(std::vector<double>{xShift, yShift});
    if (shift2D > 0) {
        double mgr = cells[cell].getModelParams().mgr;
        double mesenchymalForce = (shift2D + mgr * epithelialSecConcentration) / shift2D;
        xShift = xShift * mesenchymalForce;
        yShift = yShift * mesenchymalForce;
    }

    double epithelialGrowth = 0;
    double dgr = cells[cell].getModelParams().dgr;
    double egr = cells[cell].getModelParams().egr;

    double shift3D = Geometrics::vectorNorm3D(std::vector<double>{xShift, yShift, dgr});
    if (shift3D > 0) {
        epithelialGrowth = egr * inverseDiffState / shift3D;
    }

    cells[cell].addTempX(xShift * epithelialGrowth);
    cells[cell].addTempY(yShift * epithelialGrowth);
    cells[cell].addTempZ(dgr * epithelialGrowth);

}

bool Model::multipleNeighbour(Cell (&cells)[totalNrOfCells], ImplementParams &implementParams) {
    for (int cell = 0; cell < implementParams.nrCellsInSimulation; ++cell) {
        int *neighbours = cells[cell].getNeighbours();
        for (int neighbour1 = 0; neighbour1 < maxNrOfNeighbours; ++neighbour1) {
            int lastNeighbour = neighbours[neighbour1];
            if (lastNeighbour == -1) {
                continue;
            }
            for (int neighbour2 = neighbour1 + 1; neighbour2 < maxNrOfNeighbours; ++neighbour2) {
                int nextNeighbour = neighbours[neighbour2];
                if (nextNeighbour == -1) {
                    continue;
                }
                if (lastNeighbour == nextNeighbour) {
                    std::cout << "Cell " << lastNeighbour << " appears multiple times in the neighbour vector of cell "
                              << cell << " in iteration " << implementParams.currentIteration << std::endl;
                    implementParams.error = true;
                    return true;
                }
            }
        }
    }
    return false;
}
