//
// Created by Stefanie on 07.09.2018.
//

#ifndef MORPHOTOOTH_INPUT_H
#define MORPHOTOOTH_INPUT_H

#include "Parameters.h"


/**
 * @brief   Reading and assignment of the input Parameters
 */
class Input {
public:

    /**
     * @brief   Returns a struct with the parameters for a seal tooth (for testing purpose only)
     * @return  params  struct containing all parameter values
     */
    static Parameters defineParametersSealTest();

};


#endif //MORPHOTOOTH_INPUT_H
