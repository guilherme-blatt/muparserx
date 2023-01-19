/*
               __________                                 ____  ___
    _____  __ _\______   \_____ _______  ______ __________\   \/  /
    /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     /
    |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \
    |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
          \/                     \/           \/     \/           \_/
    Copyright (C) 2021 Ingo Berg, et al.
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
    ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
    IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
    INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
    NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
    WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.
*/
#include "mpOprtBinCommon.h"
#include <cmath>
#include <limits>


MUP_NAMESPACE_START

//-----------------------------------------------------------------------------------------------
//
// class OprtStrAdd
//
//-----------------------------------------------------------------------------------------------

OprtStrAdd::OprtStrAdd()
    :IOprtBin(_T("//"), (int)prADD_SUB, oaLEFT)
{}

//-----------------------------------------------------------------------------------------------
void OprtStrAdd::Eval(ptr_val_type& ret, const ptr_val_type *arg, int argc)
{
  MUP_VERIFY(argc == 2);
  string_type a = arg[0]->GetString();
  string_type b = arg[1]->GetString();
  *ret = a + b;
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtStrAdd::GetDesc() const
{
  return _T("string concatenation");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtStrAdd::Clone() const
{
  return new OprtStrAdd(*this);
}


//-----------------------------------------------------------------------------------------------
//
// class OprtEQ
//
//-----------------------------------------------------------------------------------------------

OprtEQ::OprtEQ()
    :IOprtBin(_T("=="), (int)prRELATIONAL1, oaLEFT)
{}

//-----------------------------------------------------------------------------------------------
void OprtEQ::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int num)
{
  assert(num==2);
  
  const IValue *arg1 = a_pArg[0].Get();
  const IValue *arg2 = a_pArg[1].Get();
  if (arg1->GetType()=='m' && arg2->GetType()=='m')
  {
    // Vector == Vector
    const matrix_type &a1 = arg1->GetArray(),
        &a2 = arg2->GetArray();
    
    //Gets the smallest size
    int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();
    
    //By default this is not allowed, but we want to support different size operations
//      if (a1.GetRows()!=a2.GetRows())
//        throw ParserError(ErrorContext(ecARRAY_SIZE_MISMATCH, -1, GetIdent(), 'm', 'm', 2));
    
    matrix_type rv(size);
    for (int i=0; i<size; ++i)
    {
      if (!a1.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      if (!a2.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a1.At(i).GetFloat() == a2.At(i).GetFloat();
    }
    
    *ret = rv;
  }
  
  else if (arg1->GetType()=='m' && arg2->IsNonComplexScalar()) {
    // Vector == Scalar
    const matrix_type &a1 = arg1->GetArray();
    
    matrix_type rv(a1.GetRows());
    for (int i = 0; i < a1.GetRows(); ++i) {
      
      if (!a1.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a1.At(i).GetFloat() == arg2->GetFloat();
    }
    
    *ret = rv;
  }
  
  else if(arg1->IsNonComplexScalar() && arg2->GetType()=='m') {
    //Scalar == Vector
    const matrix_type &a2 = arg2->GetArray();
    
    matrix_type rv(a2.GetRows());
    for (int i = 0; i < a2.GetRows(); ++i) {
      
      if (!a2.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a2.At(i).GetFloat() == arg1->GetFloat();
    }
    
    *ret = rv;
  }
  else
  {
    if (!arg1->IsNonComplexScalar())
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));
    
    if (!arg2->IsNonComplexScalar())
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg2->GetType(), 'f', 2));
    
    *ret = arg1->GetFloat() == arg2->GetFloat();
  }
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtEQ::GetDesc() const
{
  return _T("equals operator");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtEQ::Clone() const
{
  return new OprtEQ(*this);
}

//-----------------------------------------------------------------------------------------------
//
// class OprtNEQ
//
//-----------------------------------------------------------------------------------------------

OprtNEQ::OprtNEQ()
    :IOprtBin(_T("!="), (int)prRELATIONAL1, oaLEFT)
{}

//-----------------------------------------------------------------------------------------------
void OprtNEQ::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int num)
{
  assert(num==2);
  
  const IValue *arg1 = a_pArg[0].Get();
  const IValue *arg2 = a_pArg[1].Get();
  if (arg1->GetType()=='m' && arg2->GetType()=='m')
  {
    // If arg1 is a Vector != arg2 is a Vector
    const matrix_type &a1 = arg1->GetArray(),
        &a2 = arg2->GetArray();
    
    //Gets the smallest size
    int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();
    
    //By default this is not allowed, but we want to support different size operations
//      if (a1.GetRows()!= a2.GetRows())
//        throw ParserError(ErrorContext(ecARRAY_SIZE_MISMATCH, -1, GetIdent(), 'm', 'm', 2));

    matrix_type rv(size); //this variable receive the result of operation
    for (int i=0; i<size; ++i) // do the operation between arg1 and agr2 for each element of the smallest array
    {
      if (!a1.At(i).IsNonComplexScalar()) // if the element from array of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a1.At(i).GetFloat() != a2.At(i).GetFloat();
    }
    
    *ret = rv; //that's the return of the function
  }
  
  else if (arg1->GetType()=='m' && arg2->IsNonComplexScalar()) {
    // If arg1 is a Vector != If arg2 is a Scalar
    const matrix_type &a1 = arg1->GetArray();
    
    matrix_type rv(a1.GetRows());//this variable receive the result of operation, your size is equal to arg1 size
    for (int i = 0; i < a1.GetRows(); ++i) { // do the operation between arg1 and agr2 for each element of the arg1 (vector)
      
      if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a1.At(i).GetFloat() != arg2->GetFloat();
    }
    
    *ret = rv;//that's the return of the function
  }
  
  else if(arg1->IsNonComplexScalar() && arg2->GetType()=='m') {
    //If arg1 is a Scalar + If arg2 is a Vector
    const matrix_type &a2 = arg2->GetArray();
    
    matrix_type rv(a2.GetRows());//this variable receive the result of operation, your size is equal to arg2 size
    for (int i = 0; i < a2.GetRows(); ++i) { // do the operation between arg1 and agr2 for each element of the arg2(vector)
      
      if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a2.At(i).GetFloat() != arg1->GetFloat();
    }
    
    *ret = rv;//that's the return of the function
  }
  else
  {//If arg1 is a Scalar != If arg2 is a Scalar
    if (!arg1->IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));
    
    if (!arg2->IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg2->GetType(), 'f', 2));
    
    *ret = arg1->GetFloat() != arg2->GetFloat();//that's the return of the function
  }
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtNEQ::GetDesc() const
{
  return _T("not equal operator");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtNEQ::Clone() const
{
  return new OprtNEQ(*this);
}

//-----------------------------------------------------------------------------------------------
//
// class OprtLT
//
//-----------------------------------------------------------------------------------------------

OprtLT::OprtLT()
    :IOprtBin(_T("<"), (int)prRELATIONAL2, oaLEFT)
{}

//-----------------------------------------------------------------------------------------------
void OprtLT::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int num)
{
  assert(num==2);
  
  const IValue *arg1 = a_pArg[0].Get();
  const IValue *arg2 = a_pArg[1].Get();
  if (arg1->GetType()=='m' && arg2->GetType()=='m')
  {
    // If arg1 is a Vector < If arg2 is a Vector
    const matrix_type &a1 = arg1->GetArray(),
        &a2 = arg2->GetArray();
    
    //Gets the smallest size
    int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();
    
    //By default this is not allowed, but we want to support different size operations
//      if (a1.GetRows()!=a2.GetRows())
//        throw ParserError(ErrorContext(ecARRAY_SIZE_MISMATCH, -1, GetIdent(), 'm', 'm', 2));
    
    matrix_type rv(size);//this variable receive the result of operation
    for (int i=0; i<size; ++i)// do the operation between arg1 and agr2 for each element of the smallest array
    {
      if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a1.At(i).GetFloat() < a2.At(i).GetFloat();
    }
    
    *ret = rv;//that's the return of the function
  }
  
  else if (arg1->GetType()=='m' && arg2->IsNonComplexScalar()) {
    // If arg1 is a Vector < If arg2 is a Scalar
    const matrix_type &a1 = arg1->GetArray();
    
    matrix_type rv(a1.GetRows());//this variable receive the result of operation, your size is equal to arg1 size
    for (int i = 0; i < a1.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg1 (vector)
      
      if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a1.At(i).GetFloat() < arg2->GetFloat();
    }
    
    *ret = rv;
  }
  
  else if(arg1->IsNonComplexScalar() && arg2->GetType()=='m') {
    //Scalar < Vector
    const matrix_type &a2 = arg2->GetArray();
    
    matrix_type rv(a2.GetRows());//this variable receive the result of operation, your size is equal to arg2 size
    for (int i = 0; i < a2.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg2 (vector)
      
      if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a2.At(i).GetFloat() < arg1->GetFloat();
    }
    
    *ret = rv;
  }
  else
  {//If arg1 is a Scalar < If arg2 is a Scalar
    if (!arg1->IsNonComplexScalar())// if the element of arg1 isn't a non-complex scalar
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));
    
    if (!arg2->IsNonComplexScalar())// if the element of arg2 isn't a non-complex scalar
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg2->GetType(), 'f', 2));
    
    *ret = arg1->GetFloat() < arg2->GetFloat();
  }
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtLT::GetDesc() const
{
  return _T("less than operator");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtLT::Clone() const
{
  return new OprtLT(*this);
}

//-----------------------------------------------------------------------------------------------
//
// class OprtGT
//
//-----------------------------------------------------------------------------------------------

OprtGT::OprtGT()
    :IOprtBin(_T(">"), (int)prRELATIONAL2, oaLEFT) {}

//-----------------------------------------------------------------------------------------------
void OprtGT::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int num)
{
  assert(num==2);
  
  const IValue *arg1 = a_pArg[0].Get();
  const IValue *arg2 = a_pArg[1].Get();
  if (arg1->GetType()=='m' && arg2->GetType()=='m')
  {
    // Vector > Vector
    const matrix_type &a1 = arg1->GetArray(),
        &a2 = arg2->GetArray();
    
    //Gets the smallest size
    int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();
    
    //By default this is not allowed, but we want to support different size operations
//      if (a1.GetRows()!=a2.GetRows())
//        throw ParserError(ErrorContext(ecARRAY_SIZE_MISMATCH, -1, GetIdent(), 'm', 'm', 2));
    
    matrix_type rv(size);//this variable receive the result of operatio
    for (int i=0; i<size; ++i)// do the operation between arg1 and agr2 for each element of the smallest array
    {
      if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a1.At(i).GetFloat() > a2.At(i).GetFloat();
    }
    
    *ret = rv;
  }
  
  else if (arg1->GetType()=='m' && arg2->IsNonComplexScalar()) {
    // Vector + Scalar
    const matrix_type &a1 = arg1->GetArray();
    
    matrix_type rv(a1.GetRows());//this variable receive the result of operation, your size is equal to arg1 size
    for (int i = 0; i < a1.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg1 (vector)
      
      if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a1.At(i).GetFloat() > arg2->GetFloat();
    }
    
    *ret = rv;
  }
  
  else if(arg1->IsNonComplexScalar() && arg2->GetType()=='m') {
    //Scalar > Vector
    const matrix_type &a2 = arg2->GetArray();
    
    matrix_type rv(a2.GetRows());//this variable receive the result of operation, your size is equal to arg2 size
    for (int i = 0; i < a2.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg2 (vector)
      
      if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a2.At(i).GetFloat() > arg1->GetFloat();
    }
    
    *ret = rv;
  }
  else
  {//Scalar > Scalar
    if (!arg1->IsNonComplexScalar())// if the element of arg1 isn't a non-complex scalar
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));
    
    if (!arg2->IsNonComplexScalar())// if the element of arg2 isn't a non-complex scalar
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg2->GetType(), 'f', 2));
    
    *ret = arg1->GetFloat() > arg2->GetFloat();
  }
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtGT::GetDesc() const
{
  return _T("greater than operator");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtGT::Clone() const
{
  return new OprtGT(*this);
}

//-----------------------------------------------------------------------------------------------
//
// class OprtLE
//
//-----------------------------------------------------------------------------------------------

OprtLE::OprtLE()
    :IOprtBin(_T("<="), (int)prRELATIONAL2, oaLEFT)
{}

//-----------------------------------------------------------------------------------------------
void OprtLE::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int num)
{
  assert(num==2);
  
  const IValue *arg1 = a_pArg[0].Get();
  const IValue *arg2 = a_pArg[1].Get();
  if (arg1->GetType()=='m' && arg2->GetType()=='m')
  {
    // Vector <= Vector
    const matrix_type &a1 = arg1->GetArray(),
        &a2 = arg2->GetArray();
    
    //Gets the smallest size
    int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();
    
    //By default this is not allowed, but we want to support different size operations
//      if (a1.GetRows()!=a2.GetRows())
//        throw ParserError(ErrorContext(ecARRAY_SIZE_MISMATCH, -1, GetIdent(), 'm', 'm', 2));
    
    matrix_type rv(size);
    for (int i=0; i<size; ++i)
    {
      if (!a1.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      if (!a2.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a1.At(i).GetFloat() <= a2.At(i).GetFloat();
    }
    
    *ret = rv;
  }
  
  else if (arg1->GetType()=='m' && arg2->IsNonComplexScalar()) {
    // Vector <= Scalar
    const matrix_type &a1 = arg1->GetArray();
    
    matrix_type rv(a1.GetRows());
    for (int i = 0; i < a1.GetRows(); ++i) {
      
      if (!a1.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a1.At(i).GetFloat() <= arg2->GetFloat();
    }
    
    *ret = rv;
  }
  
  else if(arg1->IsNonComplexScalar() && arg2->GetType()=='m') {
    //Scalar <= Vector
    const matrix_type &a2 = arg2->GetArray();
    
    matrix_type rv(a2.GetRows());
    for (int i = 0; i < a2.GetRows(); ++i) {
      
      if (!a2.At(i).IsNonComplexScalar())
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a2.At(i).GetFloat() <= arg1->GetFloat();
    }
    
    *ret = rv;
  }
  else
  {
    if (!arg1->IsNonComplexScalar())
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));
    
    if (!arg2->IsNonComplexScalar())
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg2->GetType(), 'f', 2));
    
    *ret = arg1->GetFloat() <= arg2->GetFloat();
  }
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtLE::GetDesc() const
{
  return _T("less or equal operator");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtLE::Clone() const
{
  return new OprtLE(*this);
}

//-----------------------------------------------------------------------------------------------
//
// class OprtGE
//
//-----------------------------------------------------------------------------------------------

OprtGE::OprtGE()
    :IOprtBin(_T(">="), (int)prRELATIONAL2, oaLEFT)
{}

//-----------------------------------------------------------------------------------------------
void OprtGE::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int num)
{
  assert(num==2);
  
  const IValue *arg1 = a_pArg[0].Get();
  const IValue *arg2 = a_pArg[1].Get();
  if (arg1->GetType()=='m' && arg2->GetType()=='m')
  {
    // Vector >= Vector
    const matrix_type &a1 = arg1->GetArray(),
        &a2 = arg2->GetArray();
    
    //Gets the smallest size
    int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();
    
    //By default this is not allowed, but we want to support different size operations
//      if (a1.GetRows()!=a2.GetRows())
//        throw ParserError(ErrorContext(ecARRAY_SIZE_MISMATCH, -1, GetIdent(), 'm', 'm', 2));
    
    matrix_type rv(size);//this variable receive the result of operation
    for (int i=0; i<size; ++i)// do the operation between arg1 and agr2 for each element of the smallest array
    {
      if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a1.At(i).GetFloat() >= a2.At(i).GetFloat();
    }
    
    *ret = rv;
  }
  
  else if (arg1->GetType()=='m' && arg2->IsNonComplexScalar()) {
    // Vector >= Scalar
    const matrix_type &a1 = arg1->GetArray();
    
    matrix_type rv(a1.GetRows());//this variable receive the result of operation, your size is equal to arg1 size
    for (int i = 0; i < a1.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg1 (vector)
      
      if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a1.At(i).GetFloat() >= arg2->GetFloat();
    }
    
    *ret = rv;
  }
  
  else if(arg1->IsNonComplexScalar() && arg2->GetType()=='m') {
    //Scalar >= Vector
    const matrix_type &a2 = arg2->GetArray();
    
    matrix_type rv(a2.GetRows());//this variable receive the result of operation, your size is equal to arg2 size
    for (int i = 0; i < a2.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg2 (vector)
      
      if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = a2.At(i).GetFloat() >= arg1->GetFloat();
    }
    
    *ret = rv;
  }
  else
  {// Scalar >= Scalar
    if (!arg1->IsNonComplexScalar())// if the element of arg1 isn't a non-complex scalar
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));
    
    if (!arg2->IsNonComplexScalar())// if the element of arg2 isn't a non-complex scalar
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg2->GetType(), 'f', 2));
    
    *ret = arg1->GetFloat() >= arg2->GetFloat();
  }
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtGE::GetDesc() const
{
  return _T("greater or equal operator");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtGE::Clone() const
{
  return new OprtGE(*this);
}

//-----------------------------------------------------------------------------------------------
//
// class OprtAnd
//
//-----------------------------------------------------------------------------------------------

OprtAnd::OprtAnd()
    :IOprtBin(_T("&"), (int)prBIT_AND, oaLEFT)
{}

//-----------------------------------------------------------------------------------------------
void OprtAnd::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
{
  MUP_VERIFY(num == 2);
  
  if (!a_pArg[0]->IsScalar())
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[0]->GetType(), 'i', 1));
  
  if (!a_pArg[1]->IsScalar())
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[1]->GetType(), 'i', 2));
  
  float_type a = a_pArg[0]->GetFloat(),
      b = a_pArg[1]->GetFloat();
  
  if (a != (int_type)a)
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, a_pArg[0]->GetIdent(), a_pArg[0]->GetType(), 'i', 1));
  
  if (b != (int_type)b)
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, a_pArg[1]->GetIdent(), a_pArg[1]->GetType(), 'i', 2));
  
  *ret = (float_type)((int_type)a & (int_type)(b));
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtAnd::GetDesc() const
{
  return _T("bitwise and");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtAnd::Clone() const
{
  return new OprtAnd(*this);
}

//-----------------------------------------------------------------------------------------------
//
// class OprtOr
//
//-----------------------------------------------------------------------------------------------

OprtOr::OprtOr()
    :IOprtBin(_T("|"), (int)prBIT_OR, oaLEFT)
{}

//-----------------------------------------------------------------------------------------------
void OprtOr::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
{
  MUP_VERIFY(num == 2);
  
  if (!a_pArg[0]->IsScalar())
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[0]->GetType(), 'i', 1));
  
  if (!a_pArg[1]->IsScalar())
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[1]->GetType(), 'i', 2));
  
  float_type a = a_pArg[0]->GetFloat(),
      b = a_pArg[1]->GetFloat();
  
  if (a != (int_type)a)
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, a_pArg[0]->GetIdent(), a_pArg[0]->GetType(), 'i', 1));
  
  if (b != (int_type)b)
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, a_pArg[1]->GetIdent(), a_pArg[1]->GetType(), 'i', 2));
  
  *ret = (float_type)((int_type)a | (int_type)(b));
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtOr::GetDesc() const
{
  return _T("bitwise or");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtOr::Clone() const
{
  return new OprtOr(*this);
}

//-----------------------------------------------------------------------------------------------
//
// class OprtLOr
//
//-----------------------------------------------------------------------------------------------

OprtLogicOr::OprtLogicOr(const char_type *szIdent)
    :IOprtBin(szIdent, (int)prLOGIC_OR, oaLEFT)
{}

//-----------------------------------------------------------------------------------------------
void OprtLogicOr::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
{
  assert(num==2);
  
  const IValue *arg1 = a_pArg[0].Get();
  const IValue *arg2 = a_pArg[1].Get();
  if (arg1->GetType()=='m' && arg2->GetType()=='m')
  {
    // Vector >= Vector
    const matrix_type &a1 = arg1->GetArray(),
        &a2 = arg2->GetArray();
    
    //Gets the smallest size
    int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();
    
    //By default this is not allowed, but we want to support different size operations
//      if (a1.GetRows()!=a2.GetRows())
//        throw ParserError(ErrorContext(ecARRAY_SIZE_MISMATCH, -1, GetIdent(), 'm', 'm', 2));
    
    matrix_type rv(size);//this variable receive the result of operation
    for (int i=0; i<size; ++i)// do the operation between arg1 and agr2 for each element of the smallest array
    {
      if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = (float_type)(arg1->GetBool() != 0 || arg2->GetBool() !=0);
    }
    
    *ret = rv;
  }
  
  else if (arg1->GetType()=='m' && arg2->IsNonComplexScalar()) {
    // Vector >= Scalar
    const matrix_type &a1 = arg1->GetArray();
    
    matrix_type rv(a1.GetRows());//this variable receive the result of operation, your size is equal to arg1 size
    for (int i = 0; i < a1.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg1 (vector)
      
      if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      rv.At(i) = (float_type)(arg1->GetBool() != 0 || arg2->GetBool() !=0);
    }
    
    *ret = rv;
  }
  
  else if(arg1->IsNonComplexScalar() && arg2->GetType()=='m') {
    //Scalar >= Vector
    const matrix_type &a2 = arg2->GetArray();
    
    matrix_type rv(a2.GetRows());//this variable receive the result of operation, your size is equal to arg2 size
    for (int i = 0; i < a2.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg2 (vector)
      
      if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = (float_type)(arg1->GetBool() != 0 || arg2->GetBool() !=0);
    }
    
    *ret = rv;
  }
  else
  {// Scalar >= Scalar
    if (!arg1->IsNonComplexScalar())// if the element of arg1 isn't a non-complex scalar
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));
    
    if (!arg2->IsNonComplexScalar())// if the element of arg2 isn't a non-complex scalar
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg2->GetType(), 'f', 2));
    
    *ret = (float_type)(arg1->GetBool() != 0 || arg2->GetBool() !=0);
  }
  
  *ret = a_pArg[0]->GetBool() || a_pArg[1]->GetBool();
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtLogicOr::GetDesc() const
{
  return _T("logical or");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtLogicOr::Clone() const
{
  return new OprtLogicOr(*this);
}

//-----------------------------------------------------------------------------------------------
//
// class OprtLAnd
//
//-----------------------------------------------------------------------------------------------

OprtLogicAnd::OprtLogicAnd(const char_type *szIdent)
    :IOprtBin(szIdent, (int)prLOGIC_AND, oaLEFT)
{}

//-----------------------------------------------------------------------------------------------
void OprtLogicAnd::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
{
  assert(num==2);
  
  const IValue *arg1 = a_pArg[0].Get();
  const IValue *arg2 = a_pArg[1].Get();
  if (arg1->GetType()=='m' && arg2->GetType()=='m')
  {
    // Vector >= Vector
    const matrix_type &a1 = arg1->GetArray(),
        &a2 = arg2->GetArray();
    
    //Gets the smallest size
    int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();
    
    //By default this is not allowed, but we want to support different size operations
//      if (a1.GetRows()!=a2.GetRows())
//        throw ParserError(ErrorContext(ecARRAY_SIZE_MISMATCH, -1, GetIdent(), 'm', 'm', 2));
    
    matrix_type rv(size);//this variable receive the result of operation
    for (int i=0; i<size; ++i)// do the operation between arg1 and agr2 for each element of the smallest array
    {
      if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = (float_type)(arg1->GetBool() != 0 && arg2->GetBool() !=0);
    }
    
    *ret = rv;
  }
  
  else if (arg1->GetType()=='m' && arg2->IsNonComplexScalar()) {
    // Vector >= Scalar
    const matrix_type &a1 = arg1->GetArray();
    
    matrix_type rv(a1.GetRows());//this variable receive the result of operation, your size is equal to arg1 size
    for (int i = 0; i < a1.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg1 (vector)
      
      if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
      
      rv.At(i) = (float_type)(arg1->GetBool() != 0 && arg2->GetBool() !=0);
    }
    
    *ret = rv;
  }
  
  else if(arg1->IsNonComplexScalar() && arg2->GetType()=='m') {
    //Scalar >= Vector
    const matrix_type &a2 = arg2->GetArray();
    
    matrix_type rv(a2.GetRows());//this variable receive the result of operation, your size is equal to arg2 size
    for (int i = 0; i < a2.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg2 (vector)
      
      if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
      
      rv.At(i) = (float_type)(arg1->GetBool() != 0 && arg2->GetBool() !=0);
    }
    
    *ret = rv;
  }
  else
  {// Scalar >= Scalar
    if (!arg1->IsNonComplexScalar())// if the element of arg1 isn't a non-complex scalar
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));
    
    if (!arg2->IsNonComplexScalar())// if the element of arg2 isn't a non-complex scalar
      throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg2->GetType(), 'f', 2));
    
    *ret = (float_type)(arg1->GetBool() != 0 && arg2->GetBool() !=0);
  }
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtLogicAnd::GetDesc() const
{
  return _T("logical and");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtLogicAnd::Clone() const
{
  return new OprtLogicAnd(*this);
}


//-----------------------------------------------------------------------------------------------
//
// class OprtShl
//
//-----------------------------------------------------------------------------------------------

OprtShl::OprtShl()
    :IOprtBin(_T("<<"), (int)prSHIFT, oaLEFT)
{}

//-----------------------------------------------------------------------------------------------
void OprtShl::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
{
  MUP_VERIFY(num == 2);
  
  if (!a_pArg[0]->IsScalar())
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, GetExprPos(), GetIdent(), a_pArg[0]->GetType(), 'i', 1));
  
  if (!a_pArg[1]->IsScalar())
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, GetExprPos(), GetIdent(), a_pArg[1]->GetType(), 'i', 2));
  
  float_type a = a_pArg[0]->GetFloat(),
      b = a_pArg[1]->GetFloat();
  
  if (a != (int_type)a)
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, GetExprPos(), a_pArg[0]->GetIdent(), a_pArg[0]->GetType(), 'i', 1));
  
  if (b != (int_type)b)
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, GetExprPos(), a_pArg[1]->GetIdent(), a_pArg[1]->GetType(), 'i', 2));
  
  float_type result = a*std::pow(2, b);
  int numDigits = std::numeric_limits<float_type>::digits10;
  
  if (std::fabs(result) >= std::fabs(std::pow(10.0, numDigits)))
    throw ParserError(ErrorContext(ecOVERFLOW, GetExprPos(), GetIdent()));
  
  if (result > 0)
  {
    *ret = std::floor(result);
  }
  else
  {
    *ret = std::ceil(result);
  }
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtShl::GetDesc() const
{
  return _T("shift left");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtShl::Clone() const
{
  return new OprtShl(*this);
}

//-----------------------------------------------------------------------------------------------
//
// class OprtShr
//
//-----------------------------------------------------------------------------------------------

OprtShr::OprtShr()
    :IOprtBin(_T(">>"), (int)prSHIFT, oaLEFT)
{}

//-----------------------------------------------------------
void OprtShr::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
{
  MUP_VERIFY(num == 2);
  
  if (!a_pArg[0]->IsScalar())
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, GetExprPos(), GetIdent(), a_pArg[0]->GetType(), 'i', 1));
  
  if (!a_pArg[1]->IsScalar())
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, GetExprPos(), GetIdent(), a_pArg[1]->GetType(), 'i', 2));
  
  float_type a = a_pArg[0]->GetFloat(),
      b = a_pArg[1]->GetFloat();
  
  if (a != (int_type)a)
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, GetExprPos(), a_pArg[0]->GetIdent(), a_pArg[0]->GetType(), 'i', 1));
  
  if (b != (int_type)b)
    throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, GetExprPos(), a_pArg[1]->GetIdent(), a_pArg[1]->GetType(), 'i', 2));
  
  float_type result = a*std::pow(2, -b);
  int numDigits = std::numeric_limits<float_type>::digits10;
  
  if (std::fabs(result) >= std::fabs(std::pow(10.0, numDigits)))
    throw ParserError(ErrorContext(ecOVERFLOW, GetExprPos(), GetIdent()));
  
  if (result > 0)
    *ret = std::floor(result);
  else
    *ret = std::ceil(result);
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtShr::GetDesc() const
{
  return _T("shift right");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtShr::Clone() const
{
  return new OprtShr(*this);
}

//-----------------------------------------------------------------------------------------------
//
//  Cast To Float
//
//-----------------------------------------------------------------------------------------------

OprtCastToFloat::OprtCastToFloat()
    :IOprtInfix(_T("(float)"), prINFIX)
{}

//-----------------------------------------------------------------------------------------------
void OprtCastToFloat::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int /*a_iArgc*/)
{
  switch (a_pArg[0]->GetType())
  {
  case 'i':
  case 'f':
  case 'b':
    *ret = a_pArg[0]->GetFloat();
    break;
  
  default:
  {
    ErrorContext err;
    err.Errc = ecINVALID_TYPECAST;
    err.Type1 = a_pArg[0]->GetType();
    err.Type2 = 'f';
    throw ParserError(err);
  }
  } // switch value type
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtCastToFloat::GetDesc() const
{
  return _T("cast a value into a floating point number");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtCastToFloat::Clone() const
{
  return new OprtCastToFloat(*this);
}

//-----------------------------------------------------------------------------------------------
//
//  Cast To Int
//
//-----------------------------------------------------------------------------------------------

OprtCastToInt::OprtCastToInt()
    :IOprtInfix(_T("(int)"), prINFIX)
{}

//-----------------------------------------------------------------------------------------------
void OprtCastToInt::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int /*a_iArgc*/)
{
  switch (a_pArg[0]->GetType())
  {
  case 'f':
  case 'i':
  case 'b':
    *ret = (float_type)((int_type)a_pArg[0]->GetFloat());
    break;
  
  default:
  {
    ErrorContext err;
    err.Errc = ecINVALID_TYPECAST;
    err.Type1 = a_pArg[0]->GetType();
    err.Type2 = 'i';
    throw ParserError(err);
  }
  } // switch value type
}

//-----------------------------------------------------------------------------------------------
const char_type* OprtCastToInt::GetDesc() const
{
  return _T("cast a value into a floating point number");
}

//-----------------------------------------------------------------------------------------------
IToken* OprtCastToInt::Clone() const
{
  return new OprtCastToInt(*this);
}

}
