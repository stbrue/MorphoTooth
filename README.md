# MorphoTooth

## Input
### ImplementParams
Contains the settings that on one hand define some environmental conditions of the model (e.g. how strong the sink of the model is, or the size of the initial epithelium) and on the other hand the simulation type can be chosen (parameter scanning, noise scanning, or normal simulation). 

Parameter | Meaning | Possible Value
--------- | ------- | ----------
initialRadius | number of cell rings at the start of the simulation | 2
distanceCellDivisions | neighbouring cells that have this or a greater distance to each other will divide (a new cell is placed in between them) | 2
EKThreshold | a cell becomes an enamel knot cell if its Act concentration exceeds this threshold | 1.1
repDistance | all non-neighbouring cells that are closer to each other than this distance are affected by non-neighbour repulsion | 1.68
powerOfRep | in the calculation for non-neighbouring repulsion the denominator is taken to the power of this value. Thus the higher this value, the lower repulsion between non-neighbouring cells | 8
sinkAmount | proteins in cell compartements at the border (the lowest mesenchyme layer or cells at the tissue border) diffuse out of the system. sinkAmount defines how strong this sink is | 0.3
maxNrOfIterations | the simulation will run until this number of iteration is achieved (if no end-determing condition is fulfilled earlier) | 10000
minNrOfCells | at every multiple of this number of cells an output is generated. Ideally 20 or 10 should be chosen | 20
OutputInterval | at every OutputInterval-th iteration an output is generated. If set to zero, no additional outputs are  generated | 0
PrintInterval | at every PrintInterval-th iteration the number of iteration and the current number of cells is printed in the console | 100
outputPrecision | the number of decimals in the output file | 14
repetitions | when doing a simulation with noise, repetition defines how many simulations are done | 1
parameterWithNoise | this has to be a string with the name of the parameter that should have noise. This value is only relevant if the noiseType is set to 1 (global noise on only one parameter) | "Act"
sd | defines how big the fluctuations around the normal values are. It is the standard deviation of the normal distribution from which the values are taken that are added to the initial values. In the case of noise on a parameter the standard deviation is this value multiplied with the parameter value. In the other cases it is the absolute standard deviation | 0.01
noiseInterval | in the case of parameter-independent noise (noise on the position or concentration), this value defines how often (at which iteration intervals) noise happens. However, in the case of parameter noise, a certain parameter value stays constant for this amount of iterations until a new value is calculated | 200
noiseType | an integer that defines the type of the noise (see list below) | 1
parameterToChange | string of the parameter name that one likes to change step by step between the simulations. | ""
totalPlusMinusScope | the parameterToChange will be changed from its original value to plus and minus "totalPlusMinusScope"-percent. E.g. if set to 0.5, the parameter will be changed from -50% of the original to +50% of the original value | 0.5
percentageStep | in the parameter scanning the step size from one parameter value to the next is x of the initial value | 0.5

*Note* that parameter scanning and noise scanning are mutually exclusive meaning that either parameterToChange has to be set to -1 or noiseType has to be set to zero.

#### Noise Types

Noise Type | Effect
-----------| ---------
 0 | no noise
 1 | global noise on 1 parameter
 2 | global noise on all parameters
 3 | cell-specific noise on all parameters
 4 | global noise on x,y,z coordinates
 5 | cell-specific noise on x,y,z coordinates
 6 | global noise on protein concentrations
 7 | cell-specific noise on protien concentrations

### ModelParams

Parameter | Meaning | Seal Value
--------- | ------- | ----------
ActDiffusionRate | Diffusion rate of the activator | 0.2
InhDiffusionRate| Diffusion rate of the inhibitor | 0.2
SecDiffusionRate | Diffusion rate of the secondary product | 0.2
Delta | defines the strength of all mechanisms | 0.1
 Act | how strong the effect of Act activating itself is | 1.1
 Inh | how strong the effect of Inh inhibiting Act is | 35
 EpithelialDegradation | Degradation rate of gene products in the epithelium | 0.1
 MesenchymeDegradation | Degradation rate of gene products in the mesenchyme | 0
 Int | Fgf threshold. If the concentration of Act is higher than this threshold Sec (ECM) gets produced | 0.1
 Set | Sec (ECM) production rate | 0.95
 Lbi | lingual bias. Act concentration beyond +/- Swi lingually | 1
 Bbi | buccal bias. Act concentration bayond +/- Swi buccally | 1
 Swi | Distance of initial BMP from midline, i.e. range where buccal-lingual-bias does apply | 1
 Dff | Differentiation rate of the cells | 0.0002
 Egr | Epithelial proliferation rate | 0.017
 Mgr | Mesenchymal proliferation rate | 300
 Dgr | Downgrowth (cervical loop) | 6500
 Boy | Buoyancy, determined by the espression of Inh | 0
 Rep | Repulsion between different tissues and different morphology parts | 1
 Adh | Neighbour traction (effect of adhesion and repulsion between neighbours) | 0.0007
 Ntr | nuclear traction. Leads to roundening of cells | 0.00001
 Bwi | Distance at which anterior-posterior bias applies | 0.8
 Abi | anterior bias by mechanical asymmetries | 45
 Pbi | posterior bias by mechanical asymmetries | 45
 Bgr | border growth. Bias in z-direction | 1
