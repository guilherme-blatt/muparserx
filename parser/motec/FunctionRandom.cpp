//
// Created by Optimum G on 1/27/2023.
//

#include "FunctionRandom.h"

MUP_NAMESPACE_START

void RandValue::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  *ret = (double)std::rand() / (double)RAND_MAX ;;
}

}//Namespace
