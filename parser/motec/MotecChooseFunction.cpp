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
  
//  std::cout << "Arg1: " << arg1->GetFloat() << std::endl;
//  std::cout << "Arg2: " << arg2->GetFloat()<< std::endl;
//  std::cout << "Arg3: " << arg3->GetFloat() << std::endl;
  
  if (arg1->GetType()=='m' &&  arg2->GetType()=='m' && !arg3->IsNonComplexScalar()){
    const matrix_type &a1 = arg1->GetArray(),
                      &a2 = arg2->GetArray();
    
    //Gets the smallest size
    int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();
  
    matrix_type rv(size);
    for (int i=0; i<size; ++i)
    {
      if (!a1.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
    
      if (!a2.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
  
      if (a1.At(i).GetFloat() != 0)
        rv.At(i) = a2.At(i);

      else
        rv.At(i) = arg3->GetFloat();
    }
    *ret = rv;
  }
  
  else if (arg1->GetType()=='m' && arg2->IsNonComplexScalar() && !arg3->GetType()=='m'){
    const matrix_type &a1 = arg1->GetArray(),
        &a3 = arg3->GetArray();
  
    //Gets the smallest size
    int size = a1.GetRows() < a3.GetRows() ? a1.GetRows() : a3.GetRows();
  
    matrix_type rv(size);
    for (int i=0; i<size; ++i)
    {
      if (!a1.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
    
      if (!a3.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a3.At(i).GetType(), 'f', 1));
    
      if (a1.At(i).GetFloat() != 0)
        rv.At(i) = arg2->GetFloat();
    
      else
        rv.At(i) = a3.At(i);
    }
    *ret = rv;
  }

  else if (arg1->GetType()=='m' && arg2->GetType()=='m' && !arg3->GetType()=='m'){
    const matrix_type &a1 = arg1->GetArray(),
        &a2 = arg2->GetArray(),
        &a3 = arg3->GetArray();
  
    //Gets the smallest size
    int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();
    size = size < a3.GetRows() ? size : a3.GetRows();
  
    matrix_type rv(size);
    for (int i=0; i<size; ++i)
    {
      if (!a1.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
  
      if (!a2.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
  
      if (!a3.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a3.At(i).GetType(), 'f', 1));
    
      if (a1.At(i).GetFloat() != 0)
        rv.At(i) = a2.At(i);
    
      else
        rv.At(i) = a3.At(i);
    }
    *ret = rv;
  }

  else{
    /* Arg1 scalar */                                                                                                     \
    if (!arg1->IsNonComplexScalar())/* if the element of arg1 isn't a non-complex scalar*/                          \
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));               \
    
    if (arg1->GetFloat() != 0)
      *ret = arg2->GetType() == 'm' ? arg2->GetArray() : arg2->GetFloat();
    
    else
      *ret = arg3->GetType() == 'm' ? arg3->GetArray() : arg3->GetFloat();
    
  }
}
}//Namespace
