# MorphoTooth

## Input
### ImplementParams01.json
Contains the settings that on one hand define some environmental conditions of the model (e.g. how strong the sink of the model is, or the size of the initial epithelium) and on the other hand the simulation type can be chosen (parameter scanning, noise scanning, or normal simulation). 

* initialRadius: number of cell rings at the start of the simulation (2 -> 7 cells, 3 -> 19 cells)
* distanceCelllDivisions: neighbouring cells that have this or a greater distance to each other will divide (a new cell is placed in between them)
* EKThreshold: a cell becomes an enamel knot cell if its Act concentration exceeds this threshold
* repDistance: all non-neighbouring cells that are closer to each other than this distance are affected by non-neighbour repulsion
* powerOfRep: in the calculation for non-neighbouring repulsion the denominator is taken to the power of this value. Thus the higher this value, the lower repulsion between non-neighbouring cells
* sinkAmount: proteins in cell compartements at the border (the lowest mesenchyme layer or cells at the tissue border) diffuse out of the system. sinkAmount defines how strong this sink is
* newInhAndSecProduction:
* maxNrOfIterations: the simulation will run until this number of iteration is achieved (if no end-determing condition is fulfilled earlier)
* minNrOfCells: at every multiple of this number of cells an output is generated. Ideally 20 or 10 should be chosen
* OutputInterval: at every OutputInterval-th iteration an output is generated. If set to zero, no additional outputs are  generated
* PrintInterval: at every PrintInterval-th iteration the number of iteration and the current number of cells is printed in the console
* outputPrecision: the number of decimals in the output file
* repetitions: when doing a simulation with noise, repetition defines how many simulations are done
* parameterWithNoise: this has to be a string with the name of the parameter that should have noise. This value is only relevant if the noiseType is set to 1 (global noise on only one parameter)
* sd: defines how big the fluctuations around the normal values are. It is the standard deviation of the normal distribution from which the values are taken that are added to the initial values. In the case of noise on a parameter the standard deviation is this value multiplied with the parameter value. In the other cases it is the absolute standard deviation
* noiseDuration: in the case of parameter-independent noise (noise on the position or concentration), this value defines how often (at which iteration intervals) noise happens. However, in the case of parameter noise, a certain parameter value stays constant for this amount of iterations until a new value is calculated
* noiseType: an integer that defines the type of the noise (see list below)
* parameterToChange: string of the parameter name that one likes to change step by step between the simulations. If set to -1, no parameter is changed. 
* totalPlusMinusScope: the parameterToChange will be changed from its original value to plus and minus "totalPlusMinusScope"-percent. E.g. if set to 0.5, the parameter will be changed from -50% of the original to +50% of the original value
* percentageStep: defines the step size in the parameter scanning. E.g. if set to 0.1 the parameter is in each repetition changed by 10% of its original value.

*Note* that parameter scanning and noise scanning are mutually exclusive meaning that either parameterToChange has to be set to -1 or noiseType has to be set to zero.

#### Noise Types

* 0: no noise
* 1: global noise on 1 parameter
* 2: global noise on all parameters
* 3: cell-specific noise on all parameters
* 4: global noise on x,y,z coordinates
* 5: cell-specific noise on x,y,z coordinates
* 6: global noise on protein concentrations
* 7: cell-specific noise on protien concentrations

### ModelParams01.json

* ActDiffusionRate
* InhDiffusionRate
* SecDiffusionRate
* Delta: defines the strength of all mechanisms
* Act: how strong the effect of Act activating itself is
* Inh: how strong the effect of Inh inhibiting Act is
* Mu: Degradation rates of gene products
* Int: Fgf threshold. If the concentration of Act is higher than this threshold Sec (ECM) gets produced
* Set: Sec (ECM) production rate
* Lbi: lingual bias. Act concentration beyond +/- Swi lingually
* Bbi: buccal bias. Act concentration bayond +/- Swi buccally
* Swi: Distance of initial BMP from midline, i.e. range where buccal-lingual-bias does apply
* Dff: Differentiation rate of the cells
* Egr: Epithelial proliferation rate
* Mgr: Mesenchymal proliferation rate
* Dgr: Downgrowth (cervical loop)
* Boy: Buoyancy, determined by the espression of Inh
* Rep: Repulsion between different tissues and different morphology parts
* Adh: Neighbour traction (effect of adhesion **and** repulsion between neighbours)
* Ntr: nuclear traction. Leads to roundening of cells
* Bwi: Distance at which anterior-posterior bias applies
* Abi: anterior bias by mechanical asymmetries
* Pbi: posterior bias by mechanical asymmetries
* Bgr: border growth. Bias in z-direction
