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
        
          if(i == 0) {
            int n = 0;
            for(int l = i; l < (a2 +1)/2; l ++){
              rv.At(i) = rv.At(i).GetFloat() + a1.At(l).GetFloat();
              n++;
            }
            rv.At(i) = rv.At(i).GetFloat() / (float_type) n;
          }
          
          if(i == size-1){
            int n = 0;
            for(int l = i; l > ; l--){
              rv.At(i) = rv.At(i).GetFloat() + a1.At(l).GetFloat();
              n++;
            }
            rv.At(i) = rv.At(i).GetFloat() / (float_type) n;
          }
//
//          for (int l = i; l < a2; l++) {
//            rv.At(i) = rv.At(i).GetFloat() + a1.At(l).GetFloat();
//          }
//          rv.At(i) = rv.At(i).GetFloat() / (float_type) a2;
        }
        *ret = rv;
      }
    }
  
    if (arg2->GetType() == 'f')
      std::cout << "Float: time interval in seconds" << std::endl;

//    if(arg3->GetType() == 'm')
//      size = std::min(size, arg3->GetRows());

//    matrix_type  rv(size);
//
//    for(int i=0; i<size; i++){
//      if (!a1.At(i).IsNonComplexScalar())
//        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
//
//      if(a1.At(i).GetFloat() != 0) {
//        rv.At(i) = arg2->GetType() == 'm' ? arg2->GetArray().At(i) : arg2->GetFloat();
//        if (!rv.At(i).IsNonComplexScalar())
//          throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), rv.At(i).GetType(), 'f', 1));
//      }
//      else{
//        rv.At(i) = arg3->GetType() == 'm' ? arg3->GetArray().At(i) : arg3->GetFloat();
//        if (!rv.At(i).IsNonComplexScalar())
//          throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), rv.At(i).GetType(), 'f', 1));
//      }
//    }
//    *ret = rv;
//  }
//
//  else{
//    /* Arg1 scalar */
//    if (!arg1->IsNonComplexScalar())/* if the element of arg1 isn't a non-complex scalar*/
//      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));
//
//  }
  }
}
}//Namespace
