//
// Created by Optimum G on 1/27/2023.
//

#ifndef MUPARSERX_MOTECDEFINITION_H
#define MUPARSERX_MOTECDEFINITION_H

#include "../mpParser.h"

#include "MotecBasicFunctions.h"
#include "MotecChooseFunction.h"
#include "MotecSmoothFunction.h"
#include "MotecDerivativeFunction.h"
#include "MotecIntegrateFunction.h"
#include "MotecIntegrateDistFunction.h"
#include "MotecStatMeanFunction.h"

MUP_NAMESPACE_START

class motecDefinition {

public:
  static void add_motec_functions(ParserX* parserX, int frequency);
  
};

#endif //MUPARSERX_MOTECDEFINITION_H

}//Namespace end
