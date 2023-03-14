//
// Created by Optimum G on 1/27/2023.
//

#include "MotecSmoothFunction.h"
#include "MotecDerivativeFunction.h"

MUP_NAMESPACE_START

void Derivative::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  //  assert(a_iArgc==2);

  const IValue *arg1 = a_pArg[0].Get(),
               *arg2 = a_pArg[1].Get();

  double dx = 1.0;
  
  if(arg1->GetType() == 'm' && arg2->IsNonComplexScalar()) {
    const matrix_type& a1 = SmoothFunction::Smooth(ret, a_pArg, frequency_);
  
    int size = a1.GetRows();
    matrix_type rv(size);
  
    for (int iterator = 1; iterator < size; iterator++) {
      rv.At(iterator) = (a1.At(iterator).GetFloat() - a1.At(iterator - 1).GetFloat())/dx;
    }
    *ret = rv;
  }
  else{
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, "Not a matrix !" , arg1->GetType(), 'm', 1));
  }
}
}//Namespace