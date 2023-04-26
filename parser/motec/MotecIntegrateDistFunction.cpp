//
// Created by Optimum G on 1/27/2023.
//

#include "MotecIntegrateDistFunction.h"

MUP_NAMESPACE_START

void IntegrateDist::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  //assert(a_iArgc==2);

  const IValue *arg1 = a_pArg[0].Get(),
               *arg2 = a_pArg[1].Get(),
               *arg3 = a_pArg[2].Get(),
               *arg4 = a_pArg[3].Get();
  
  const matrix_type& dist = arg4->GetArray();
  
  if(arg1->GetType() == 'm' && arg2->IsNonComplexScalar() || arg3->GetType() == 'm'){ //comentar depois o 0
    const matrix_type& channel = arg1->GetArray(),
        reset = arg3->GetArray();
    
    int size = channel.GetRows();
    matrix_type rv(size);
    double sum = 0.0;
    
    for (int iterator = 1; iterator < size; iterator++){
      if ((int) reset.At(iterator).GetFloat() <= (int) reset.At(iterator-1).GetFloat()){
        float h = dist.At(iterator).GetFloat() - dist.At(iterator-1).GetFloat();
        sum += ((channel.At(iterator).GetFloat() + channel.At(iterator-1).GetFloat()) / 2.0) * h;
        rv.At(iterator) = sum ;
      }
      else {
        rv.At(iterator) = 0.0;
        sum = 0.0;
      }
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
      if (condition.At(iterator).GetFloat()!= 0){
        sum += channel.At(iterator).GetFloat();
        rv.At(iterator) = sum * (dist.At(iterator).GetFloat() -  dist.At(iterator-1).GetFloat());
      }
      else
        rv.At(iterator) = rv.At(iterator-1).GetFloat();
      
      if ((int) reset.At(iterator).GetFloat() > (int) reset.At(iterator-1).GetFloat()){
        sum = 0.0;
        rv.At(iterator) = 0.0;
      }
    }
    *ret = rv;
  }
  
  else{
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, "Not a matrix !" , arg1->GetType(), 'm', 1));
  }
}
}//Namespace