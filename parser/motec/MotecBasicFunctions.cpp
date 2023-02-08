//
// Created by Optimum G on 1/27/2023.
//

#include "MotecBasicFunctions.h"
//#include <time.h>

MUP_NAMESPACE_START

void RandValue::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  static std::mt19937 generator(time(nullptr));
  std::uniform_real_distribution<double> distribution(0.0, 1.0);
  double random = distribution(generator);
  
  *ret = random;
}

void MotecInt::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  assert(a_iArgc==1);
  const IValue *arg1 = a_pArg[0].Get();
  if (arg1->GetType()=='m')
  {
    /* Vector */
    const matrix_type &a1 = arg1->GetArray();
    matrix_type rv(a1.GetRows());
    /* do the operation for each element in arg1 */
    for (int i=0; i<a1.GetRows(); ++i)
    {
      if (!a1.At(i).IsNonComplexScalar())/* if the element from array of arg1 isn't a non-complex scalar*/
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
        
      rv.At(i) = (mup::float_type) ((int) a1.At(i).GetFloat());
    }
    *ret = rv;
  }
  else
  {/* Scalar */
    if (!arg1->IsNonComplexScalar())/* if the element of arg1 isn't a non-complex scalar*/
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));
      
    *ret = (mup::float_type)((int) arg1->GetFloat());
  }
}

void MotecIsFinite::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  assert(a_iArgc==1);
  const IValue *arg1 = a_pArg[0].Get();
  if (arg1->GetType()=='m')
  {
    /* Vector */
    const matrix_type &a1 = arg1->GetArray();
    matrix_type rv(a1.GetRows());
    /* do the operation for each element in arg1 */
    for (int i=0; i<a1.GetRows(); ++i)
    {
      if (!a1.At(i).IsNonComplexScalar())/* if the element from array of arg1 isn't a non-complex scalar*/
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
        
      rv.At(i) = std::isfinite(a1.At(i).GetFloat());
    }
    *ret = rv;
  }
  else
  {/* Scalar */
    if (!arg1->IsNonComplexScalar())/* if the element of arg1 isn't a non-complex scalar*/
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));

    *ret = std::isfinite(arg1->GetFloat());
  }
}

void MotecSquare::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  assert(a_iArgc==1);
  const IValue *arg1 = a_pArg[0].Get();
  if (arg1->GetType()=='m')
  {
    /* Vector */
    const matrix_type &a1 = arg1->GetArray();
    matrix_type rv(a1.GetRows());
    /* do the operation for each element in arg1 */
    for (int i=0; i<a1.GetRows(); ++i)
    {
      if (!a1.At(i).IsNonComplexScalar())/* if the element from array of arg1 isn't a non-complex scalar*/
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));

      rv.At(i) = std::pow(a1.At(i).GetFloat(),2);
    }
    *ret = rv;
  }
  else
  {/* Scalar */
    if (!arg1->IsNonComplexScalar())/* if the element of arg1 isn't a non-complex scalar*/
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));

    *ret = std::pow(arg1->GetFloat(),2);
  }
}

void MotecToDouble::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  assert(a_iArgc==1);
  const IValue *arg1 = a_pArg[0].Get();
  if (arg1->GetType()=='m')
  {
    /* Vector */
    const matrix_type &a1 = arg1->GetArray();
    matrix_type rv(a1.GetRows());
    /* do the operation for each element in arg1 */
    for (int i=0; i<a1.GetRows(); ++i)
    {
      if (!a1.At(i).IsNonComplexScalar())/* if the element from array of arg1 isn't a non-complex scalar*/
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
        
      rv.At(i) = (double) a1.At(i).GetFloat();
    }
    *ret = rv;
  }
  else
  {/* Scalar */
    if (!arg1->IsNonComplexScalar())/* if the element of arg1 isn't a non-complex scalar*/
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));
      
    *ret = (double) arg1->GetFloat();
  }
}

void MotecFrac::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  assert(a_iArgc==1);
  const IValue *arg1 = a_pArg[0].Get();
  if (arg1->GetType()=='m')
  {
    /* Vector */
    const matrix_type &a1 = arg1->GetArray();
    matrix_type rv(a1.GetRows());
    /* do the operation for each element in arg1 */
    for (int i=0; i<a1.GetRows(); ++i)
    {
      if (!a1.At(i).IsNonComplexScalar())/* if the element from array of arg1 isn't a non-complex scalar*/
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));

      rv.At(i) = a1.At(i).GetFloat() - trunc(a1.At(i).GetFloat());
    }
    *ret = rv;
  }
  else
  {/* Scalar */
    if (!arg1->IsNonComplexScalar())/* if the element of arg1 isn't a non-complex scalar*/
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));

    *ret = arg1->GetFloat() - trunc(arg1->GetFloat());
  }
}

void MotecInvalid::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc){
  *ret = (float_type) NAN;
}

void MotecSgn::Eval(ptr_val_type &ret, const ptr_val_type* a_pArg, int a_iArgc)
{
  assert(a_iArgc==1);
  const IValue *arg1 = a_pArg[0].Get();
  if (arg1->GetType()=='m')
  {
    /* Vector */
    const matrix_type &a1 = arg1->GetArray();
    matrix_type rv(a1.GetRows());
    /* do the operation for each element in arg1 */
    for (int i=0; i<a1.GetRows(); ++i)
    {
      if (!a1.At(i).IsNonComplexScalar())/* if the element from array of arg1 isn't a non-complex scalar*/
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      if(a1.At(i).GetFloat() > 0)
        rv.At(i) = (float_type) 1;
      
      else if(a1.At(i).GetFloat() < 0)
        rv.At(i) = (float_type) -1;

      else
        rv.At(i) = (float_type) 0;
    }
    *ret = rv;
  }
  else
  {/* Scalar */
    if (!arg1->IsNonComplexScalar())/* if the element of arg1 isn't a non-complex scalar*/
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));

    if(arg1->GetFloat() > 0)
      *ret = (float_type) 1;
  
    else if(arg1->GetFloat() < 0)
      *ret = (float_type) -1;
  
    else
      *ret = (float_type) 0;
  }
}
}//Namespace
