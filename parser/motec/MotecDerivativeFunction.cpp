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
  int sample_qtd = 0;
  int windows_size = 0;
  int step_foward = 0;
  double dx = 1.0;
  
  if(arg1->GetType() == 'm' && arg2->IsNonComplexScalar()) {
    const matrix_type& a1 = SmoothFunction::Smooth(ret, a_pArg, frequency_);
    
    int size = a1.GetRows();
    if (arg2->GetType() == 'f'){
      float a2 = arg2->GetFloat();
      std::cout << "Float: time interval in seconds" << std::endl;
      
      sample_qtd = (int_type) (a2 * frequency_);
    }
    
    if(arg2->GetType() == 'i') {
      int a2 = arg2->GetInteger();
      std::cout << "Integer: sample points" << std::endl;
      
      sample_qtd = a2;
    }
    
    if(size < ((sample_qtd - 1) / 2) || (sample_qtd/2))
      *ret = a1;
    
    matrix_type rv(size);
    
    if(sample_qtd <= 1) {
      sample_qtd = 2;
    }
    
    else if(sample_qtd % 2 != 0) {
      windows_size = (sample_qtd - 1) / 2;
      step_foward = windows_size;
    }
    
    else{
      windows_size = sample_qtd / 2;
      step_foward = windows_size - 1;
    }
    
    for (int iterator = 0; iterator < size; iterator++) {
      if (!a1.At(iterator).IsNonComplexScalar())
        throw ParserError(
            ErrorContext(ecTYPE_CONFLICT_FUN, -1, "Wrong Type for SmoothFunction", a1.At(iterator).GetType(), 'f', 1));
  
      double samples_count = 0.0;
      for (int j = iterator - windows_size; j <= iterator + step_foward; j++) {
        if (j >= 0 && j < size) {
          samples_count += j * a1.At(iterator + j).GetFloat();
        }
        rv.At(iterator) = samples_count / (dx * sample_qtd);
      }
  
      for (int i = 0; i < windows_size; i++) {
        rv.At(i) = (a1.At(i+1).GetFloat() - a1.At(i).GetFloat()) / dx;
      }
      for (int i = size- windows_size; i < size; i++) {
        rv.At(i) = (a1.At(i).GetFloat() - a1.At(i-1).GetFloat()) / dx;
      }
      *ret = rv;
    }
  }
  else{
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, "Not a matrix !" , arg1->GetType(), 'm', 1));
  }
}
}//Namespace