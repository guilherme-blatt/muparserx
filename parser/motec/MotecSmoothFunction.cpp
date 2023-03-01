//
// Created by Optimum G on 1/27/2023.
//

#include "MotecSmoothFunction.h"

MUP_NAMESPACE_START

void Smooth::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  assert(a_iArgc==2);
  const IValue *arg1 = a_pArg[0].Get(),
               *arg2 = a_pArg[1].Get();


  if(arg1->GetType() == 'm') {
    const matrix_type& a1 = arg1->GetArray();
  
    int size = a1.GetRows();
  
    if(arg2->GetType() == 'i') {
      int a2 = arg2->GetInteger();
      std::cout << "Integer: sample points" << std::endl;
    
      matrix_type rv(size);
    
      if(a2 <= 1) {
        for(int i = 0; i < size; i++) {
          rv.At(i) = a1.At(i);
        }
      }
    
      if(a2 % 2 != 0) {
        for (int i = 0; i < size; i++) {
          if(!a1.At(i).IsNonComplexScalar())
            throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
        
            int windows_size = (a2 - 1) / 2;
            int samples_count = 0;
            for (int j = i - windows_size; j <= i + windows_size; j++ ){
              if (j >= 0 && j < size){
                samples_count++;
                rv.At(i) = rv.At(i).GetFloat() + a1.At(j).GetFloat();
              }
            }
            rv.At(i) = rv.At(i).GetFloat() / (float_type) samples_count;
        }
        *ret = rv;
      }
    }
  
    if (arg2->GetType() == 'f')
      std::cout << "Float: time interval in seconds" << std::endl;
    
  }
}
}//Namespace
