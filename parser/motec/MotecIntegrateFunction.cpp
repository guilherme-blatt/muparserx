//
// Created by Optimum G on 1/27/2023.
//

#include "MotecSmoothFunction.h"
#include "MotecIntegrateFunction.h"

MUP_NAMESPACE_START

void Integrate::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  //  assert(a_iArgc==2);

  const IValue *arg1 = a_pArg[0].Get(),
               *arg2 = a_pArg[1].Get(),
               *arg3 = a_pArg[2].Get();
  
  if(arg1->GetType() == 'm' && arg2->IsNonComplexScalar() || arg3->GetType() == 'm'){
    const matrix_type& channel = arg1->GetArray(),
                       reset = arg3->GetArray();
    
    int size = channel.GetRows();
    matrix_type rv(size);
    double sum = 0.0;
    
    for (int iterator = 1; iterator < size; iterator++){
      if (reset.At(iterator).GetFloat() > reset.At(iterator-1).GetFloat()){
        sum += ((channel.At(iterator).GetFloat() + channel.At(iterator-1).GetFloat()) / 2.0);
        rv.At(iterator) = sum / frequency_;
      }
      else
        rv.At(iterator) = 0.0;
    }
    *ret = rv;
  }
  
  else if(arg1->GetType() == 'm' && arg2->GetType() == 'm' && arg2->GetType() == 'm'){
    const matrix_type& channel = arg1->GetArray(),
                       condition = arg2->GetArray(),
                       reset = arg3->GetArray();

    int size = channel.GetRows() < condition.GetRows() ? channel.GetRows() : condition.GetRows();
    matrix_type rv(size);
    double sum = 0;
    
    for (int iterator = 1; iterator < size; iterator++) {
      if (reset.At(iterator+1).GetFloat() > reset.At(iterator).GetFloat() && condition.At(iterator).GetFloat() == 0){
        sum += ((channel.At(iterator).GetFloat() + channel.At(iterator-1).GetFloat()) / 2.0);
        rv.At(iterator) = sum / frequency_;
      }
      else if (reset.At(iterator).GetFloat() == 1){
        rv.At(iterator) = 0.0;
      }
      else
        rv.At(iterator) = rv.At(iterator-1).GetFloat();
    }
    *ret = rv;
  }
  
  else{
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, "Not a matrix !" , arg1->GetType(), 'm', 1));
  }
}
}//Namespace