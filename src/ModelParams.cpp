//
// Created by Stefanie on 28.02.2019.
//

#include <vector>
#include "ModelParams.h"

std::vector<std::string> getModelParameterNamesList() {
    std::vector<std::string> names = {"delta", "act", "inh", "mu", "inT", "set", "sec", "lbi", "bbi", "swi", "dff",
                                      "egr", "mgr", "dgr", "boy", "rep", "adh", "ntr", "bwi", "abi", "pbi", "bgr",
                                      "ActDiffusion", "InhDiffusion", "SecDiffusion"};
    return names;
}
