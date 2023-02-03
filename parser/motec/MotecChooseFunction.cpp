//
// Created by Optimum G on 1/27/2023.
//

#include "MotecChooseFunction.h"

MUP_NAMESPACE_START

void Choose::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  assert(a_iArgc==3);
  const IValue *arg1 = a_pArg[0].Get(),
               *arg2 = a_pArg[1].Get(),
               *arg3 = a_pArg[2].Get();
  
  if (arg1->GetType()=='m'){
    std::cout << "Nothing to do for now !" << std::endl;
  }

  else{
    /* Arg1 scalar */                                                                                                     \
    if (!arg1->IsNonComplexScalar())/* if the element of arg1 isn't a non-complex scalar*/                          \
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));               \
    
    if (arg1->GetFloat() == 1)
      *ret = arg2;
    
    if (arg2->GetFloat() == 0)
      *ret = arg3;
    
  }
}
}//Namespace
