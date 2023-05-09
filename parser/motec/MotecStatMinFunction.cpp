//
// Created by Optimum G on 1/27/2023.
//

#include "MotecStatMaxFunction.h"

MUP_NAMESPACE_START

void StatMax::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  assert(a_iArgc==3);

  const IValue *arg1 = a_pArg[0].Get(),
               *arg2 = a_pArg[1].Get(),
               *arg3 = a_pArg[2].Get();
  
  if(arg1->GetType() == 'm' && arg2->IsNonComplexScalar() || arg3->GetType() == 'm'){ //comentar depois o 0
    const matrix_type& channel = arg1->GetArray(),
        reset = arg3->GetArray();
    
    int size = channel.GetRows();
    matrix_type rv(size);
    double max = 0.0;
    
    for (int iterator = 1; iterator < size; iterator++){
      for (int iterator2 = 1; iterator2 < size; iterator2++) {
        if ((int) reset.At(iterator2).GetFloat() <= (int) reset.At(iterator2 - 1).GetFloat()) {
          if (channel.At(iterator2 - 1).GetFloat() > max)
            max = channel.At(iterator2 -1).GetFloat();
        }
        else {
          max = 0.0;
        }
      }
      rv.At(iterator) = max;
    }
    
    *ret = rv;
  }
  
  else if(arg1->GetType() == 'm' && arg2->GetType() == 'm' && arg2->GetType() == 'm'){
    const matrix_type& channel = arg1->GetArray(),
        condition = arg2->GetArray(),
        reset = arg3->GetArray();
    
    int size = channel.GetRows() < condition.GetRows() ? channel.GetRows() : condition.GetRows();
    matrix_type rv(size);
    double max = 0.0;
    
    for (int iterator = 0; iterator < size; iterator++) {
      for (int iterator2 = 0; iterator2 < size; iterator2++) {
        if (condition.At(iterator2).GetFloat() != 0) {
          if (channel.At(iterator2).GetFloat() > max)
            max = channel.At(iterator2).GetFloat();
        }
        
        if ((int) reset.At(iterator2).GetFloat() > (int) reset.At(iterator2 - 1).GetFloat()) {
          max = 0.0;
        }
      }
      rv.At(iterator) = max;
    }
    
    *ret = rv;
  }
  
  else{
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, "Not a matrix !" , arg1->GetType(), 'm', 1));
  }
}
}//Namespace