/*
               __________                                 ____  ___
    _____  __ _\______   \_____ _______  ______ __________\   \/  /
   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     / 
  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \ 
  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
        \/                     \/           \/     \/           \_/
                                       Copyright (C) 2016 Ingo Berg
                                       All rights reserved.

  muParserX - A C++ math parser library with array and string support
  Copyright (c) 2016, Ingo Berg
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
#include "mpOprtElementWise.h"

MUP_NAMESPACE_START

  //------------------------------------------------------------------------------
  //
  //  Sign operator
  //
  //------------------------------------------------------------------------------

  OprtSignElementWise::OprtSignElementWise()
    :IOprtInfix( _T("-"), prINFIX)
  {}

  //------------------------------------------------------------------------------
  void OprtSignElementWise::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  { 
      MUP_VERIFY(a_iArgc == 1);

    if (a_pArg[0]->IsScalar())
    {
      *ret = -a_pArg[0]->GetFloat();
    }
    else if (a_pArg[0]->GetType()=='m')
    {
      Value v(a_pArg[0]->GetRows(), 0);
      for (int i=0; i<a_pArg[0]->GetRows(); ++i)
      {
        v.At(i) = -a_pArg[0]->At(i).GetFloat();
      }
      *ret = v;
    }
    else
    {
        ErrorContext err;
        err.Errc = ecINVALID_TYPE;
        err.Type1 = a_pArg[0]->GetType();
        err.Type2 = 's';
        throw ParserError(err);
    }
  }

  //------------------------------------------------------------------------------
  const char_type* OprtSignElementWise::GetDesc() const
  { 
    return _T("-x - negative sign operator"); 
  }

  //------------------------------------------------------------------------------
  IToken* OprtSignElementWise::Clone() const
  { 
    return new OprtSignElementWise(*this);
  }

  //------------------------------------------------------------------------------
  //
  //  Sign operator
  //
  //------------------------------------------------------------------------------

  OprtSignPosElementWise::OprtSignPosElementWise()
    :IOprtInfix( _T("+"), prINFIX)
  {}

  //------------------------------------------------------------------------------
  void OprtSignPosElementWise::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc)
  { 
      MUP_VERIFY(a_iArgc == 1);

    if (a_pArg[0]->IsScalar())
    {
      *ret = a_pArg[0]->GetFloat();
    }
    else if (a_pArg[0]->GetType()=='m')
    {
      Value v(a_pArg[0]->GetRows(), 0);
      for (int i=0; i<a_pArg[0]->GetRows(); ++i)
      {
        v.At(i) = a_pArg[0]->At(i).GetFloat();
      }
      *ret = v;
    }
    else
    {
        ErrorContext err;
        err.Errc = ecINVALID_TYPE;
        err.Type1 = a_pArg[0]->GetType();
        err.Type2 = 's';
        throw ParserError(err);
    }
  }

  //------------------------------------------------------------------------------
  const char_type* OprtSignPosElementWise::GetDesc() const
  { 
    return _T("+x - positive sign operator"); 
  }

  //------------------------------------------------------------------------------
  IToken* OprtSignPosElementWise::Clone() const
  { 
    return new OprtSignPosElementWise(*this);
  }

//-----------------------------------------------------------
//
// class OprtAdd
//
//-----------------------------------------------------------

  OprtAddElementWise::OprtAddElementWise()
    :IOprtBin(_T("+"), (int)prADD_SUB, oaLEFT) 
  {}

  //-----------------------------------------------------------
/** \brief Implements the Addition operator.
\throw ParserError in case one of the arguments if
       nonnumeric.
*/
  void OprtAddElementWise::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int num)
  { 
    assert(num==2);

    const IValue *arg1 = a_pArg[0].Get();
    const IValue *arg2 = a_pArg[1].Get();
    if (arg1->GetType()=='m' && arg2->GetType()=='m')
    {
      // Vector + Vector
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

        rv.At(i) = a1.At(i).GetFloat() + a2.At(i).GetFloat();
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
  
        rv.At(i) = a1.At(i).GetFloat() + arg2->GetFloat();
      }
  
      *ret = rv;
    }
    
    else if(arg1->IsNonComplexScalar() && arg2->GetType()=='m') {
      //Scalar + Vector
      const matrix_type &a2 = arg2->GetArray();
  
      matrix_type rv(a2.GetRows());//this variable receive the result of operation, your size is equal to arg2 size
  
      for (int i = 0; i < a2.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg1 (vector)
    
        if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
          throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
    
        rv.At(i) = a2.At(i).GetFloat() + arg1->GetFloat();
      }
  
      *ret = rv;
    }
    else
    {//Scalar + Scalar
      if (!arg1->IsNonComplexScalar())// if the element of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1)); 

      if (!arg2->IsNonComplexScalar())// if the element of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg2->GetType(), 'f', 2)); 
      
      *ret = arg1->GetFloat() + arg2->GetFloat(); 
    }
  }

  //-----------------------------------------------------------
  const char_type* OprtAddElementWise::GetDesc() const
  { 
    return _T("x+y - Addition for noncomplex values"); 
  }
  
  //-----------------------------------------------------------
  IToken* OprtAddElementWise::Clone() const
  { 
    return new OprtAddElementWise(*this);
  }

//-----------------------------------------------------------
//
// class OprtSub
//
//-----------------------------------------------------------

  OprtSubElementWise::OprtSubElementWise()
    :IOprtBin(_T("-"), (int)prADD_SUB, oaLEFT) 
  {}

  //-----------------------------------------------------------

/** \brief Implements the Subtraction operator.
\throw ParserError in case one of the arguments if
       nonnumeric.
*/
  void OprtSubElementWise::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
  { 
    assert(num==2);

    const IValue *arg1 = a_pArg[0].Get();
    const IValue *arg2 = a_pArg[1].Get();

    if (arg1->GetType()=='m' && arg2->GetType()=='m')
    {
      //Vector - Vector
      const matrix_type &a1 = a_pArg[0]->GetArray(),
                       &a2 = a_pArg[1]->GetArray();
  
      //Gets the smallest size
      int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();
  
      matrix_type rv(size);//this variable receive the result of operation
      for (int i=0; i<size; ++i) {// do the operation between arg1 and agr2 for each element of the smallest array
        if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
          throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
  
        if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
          throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
  
        rv.At(i) = a1.At(i).GetFloat() - a2.At(i).GetFloat();
      }
      
      *ret = rv;
    }
    else if (arg1->GetType()=='m' && arg2->IsNonComplexScalar()) {
      // Vector - Scalar
      const matrix_type &a1 = arg1->GetArray();
  
      matrix_type rv(a1.GetRows());//this variable receive the result of operation, your size is equal to arg1 size
      for (int i = 0; i < a1.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg1 (vector)
    
        if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
          throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
    
        rv.At(i) = a1.At(i).GetFloat() - arg2->GetFloat();
      }
  
      *ret = rv;
    }
    else if(arg1->IsNonComplexScalar() && arg2->GetType()=='m') {
      //Scalar - Vector
      const matrix_type &a2 = arg2->GetArray();
  
      matrix_type rv(a2.GetRows());//this variable receive the result of operation, your size is equal to arg2 size
      for (int i = 0; i < a2.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg2 (vector)
    
        if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
          throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
  
        rv.At(i) = arg1->GetFloat() - a2.At(i).GetFloat();
      }
  
      *ret = rv;
    }
    else
    {
      //Scalar - Scalar
      if (!arg1->IsNonComplexScalar())// if the element of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));
  
      if (!arg2->IsNonComplexScalar())// if the element of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg2->GetType(), 'f', 2));
  
      *ret = arg1->GetFloat() - arg2->GetFloat();
    }
  }

  //-----------------------------------------------------------
  const char_type* OprtSubElementWise::GetDesc() const
  { 
    return _T("subtraction"); 
  }
  
  //-----------------------------------------------------------
  IToken* OprtSubElementWise::Clone() const
  { 
    return new OprtSubElementWise(*this);
  }

//-----------------------------------------------------------
//
// class OprtMul
//
//-----------------------------------------------------------
    
  OprtMulElementWise::OprtMulElementWise()
    :IOprtBin(_T("*"), (int)prMUL_DIV, oaLEFT) 
  {}

  //-----------------------------------------------------------

/** \brief Implements the Multiplication operator.
  \throw ParserError in case one of the arguments if
         nonnumeric.
*/
  void OprtMulElementWise::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
  { 
    assert(num==2);
    
    IValue *arg1 = a_pArg[0].Get();
    IValue *arg2 = a_pArg[1].Get();
    if (arg1->GetType()=='m' && arg2->GetType()=='m')
    {
      // Vector * Vector
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
    
        rv.At(i) = a1.At(i).GetFloat() * a2.At(i).GetFloat();
      }
      
      *ret = rv;
    }
    else if (arg1->GetType()=='m' && arg2->IsNonComplexScalar())
    {
      // Vector * Scalar
      const matrix_type &a1 = arg1->GetArray();
  
      matrix_type rv(a1.GetRows());//this variable receive the result of operation, your size is equal to arg1 size
      for (int i = 0; i < a1.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg1 (vector)
    
        if (!a1.At(i).IsNonComplexScalar())
          throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
    
        rv.At(i) = a1.At(i).GetFloat() * arg2->GetFloat();
      }
  
      *ret = rv;
    }
    else if (arg2->GetType()=='m' && arg1->IsNonComplexScalar())
    {
      // Scalar * Vector
      const matrix_type &a2 = arg2->GetArray();
  
      matrix_type rv(a2.GetRows()); //this variable receive the result of operation, your size is equal to arg2 size
      for (int i = 0; i < a2.GetRows(); ++i) {// do the operation between arg1 and agr2 for each element of the arg2 (vector)
    
        if (!a2.At(i).IsNonComplexScalar())
          throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
    
        rv.At(i) = a2.At(i).GetFloat() * arg1->GetFloat();
      }
  
      *ret = rv;
    }
    else
    {
      //Scalar * Scalar
      if (!arg1->IsNonComplexScalar())// if the element of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1)); 

      if (!arg2->IsNonComplexScalar())// if the element of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg2->GetType(), 'f', 2)); 

      *ret = arg1->GetFloat() * arg2->GetFloat(); 
    }
  }

  //-----------------------------------------------------------
  const char_type* OprtMulElementWise::GetDesc() const
  { 
    return _T("multiplication"); 
  }
  
  //-----------------------------------------------------------
  IToken* OprtMulElementWise::Clone() const
  { 
    return new OprtMulElementWise(*this);
  }

//-----------------------------------------------------------
//
// class OprtDiv
//
//-----------------------------------------------------------


  OprtDivElementWise::OprtDivElementWise()
    :IOprtBin(_T("/"), (int)prMUL_DIV, oaLEFT) 
  {}

  //-----------------------------------------------------------
  /** \brief Implements the Division operator. 
      \throw ParserError in case one of the arguments if 
             nonnumeric.
      \*ret NAN if the denominator is zero.
  */
  void OprtDivElementWise::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)
  { 
    assert(num==2);
    IValue *arg1 = a_pArg[0].Get();
    IValue *arg2 = a_pArg[1].Get();

    if (arg1->GetType()=='m' && arg2->GetType()=='m')
    {
      // Vector / Vector
      const matrix_type &a1 = arg1->GetArray(),
                        &a2 = arg2->GetArray();
  
      //Gets the smallest size
      int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();
  
      matrix_type rv(size);
      for (int i=0; i<size; ++i) {
        if (!a1.At(i).IsNonComplexScalar())
          throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
  
        if (!a2.At(i).IsNonComplexScalar())
          throw ParserError(ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
  
        if (a2.At(i).GetFloat() == (float) 0)
          rv.At(i) = NAN;
        
        else
          rv.At(i) = a1.At(i).GetFloat() / a2.At(i).GetFloat();
      }
      
      *ret = rv;
    }
    else if (arg1->GetType()=='m' && arg2->IsNonComplexScalar())
    {
      // Vector / Scalar
      const matrix_type &a1 = arg1->GetArray();
      matrix_type rv(a1.GetRows());//this variable receive the result of operation, your size is equal to arg1 size
      
      if (arg2->GetFloat() != (float) 0) {
        for (int i = 0; i < a1.GetRows(); ++i) {
          // do the operation between arg1 and agr2 for each element of the arg1 (vector) if arg2 (scalar) != 0
          rv.At(i) = a1.At(i).GetFloat() / arg2->GetFloat();
        }
      }
      else { //when arg2 == 0, this operation for each element of arg1 is not-a-number
        for (int i = 0; i < a1.GetRows(); ++i) {
          rv.At(i) = NAN;
        }
      }
      *ret = rv;
    }
    else if (arg2->GetType()=='m' && arg1->IsNonComplexScalar())
    {
      // Scalar / Vector
      const matrix_type &a2 = arg2->GetArray();
      matrix_type rv(a2.GetRows());//this variable receive the result of operation, your size is equal to arg2 size
      
      
      for (int i = 0; i < a2.GetRows(); ++i) {
        // do the operation between arg1 and agr2 for each element of the arg2 (vector) if != 0
        if (a2.At(i).GetFloat() != (float) 0) {
          rv.At(i) = arg1->GetFloat() / a2.At(i).GetFloat();
        }
        else {
          //when an element of arg2 == 0, this operation for them is not-a-number
          rv.At(i) = NAN;
        }
      }
      *ret = rv;
    }
    else
    {// If arg[0] and arg[1] is a non-complex scalar and arg[1] is != 0 returns arg[0]/arg[1], otherwise returns not-a-number
      if (!a_pArg[0]->IsNonComplexScalar())// if the element of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[0]->GetType(), 'f', 1));

      if (!a_pArg[1]->IsNonComplexScalar())// if the element of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a_pArg[1]->GetType(), 'f', 2));

      if (a_pArg[1]->GetFloat() != 0)
        *ret = a_pArg[0]->GetFloat() / a_pArg[1]->GetFloat();
      else
        *ret = NAN;
    }
  }

  //-----------------------------------------------------------
  const char_type* OprtDivElementWise::GetDesc() const
  { 
    return _T("division"); 
  }
  
  //-----------------------------------------------------------
  IToken* OprtDivElementWise::Clone() const
  { 
    return new OprtDivElementWise(*this);
  }

//-----------------------------------------------------------
//
// class OprtPow
//
//-----------------------------------------------------------

  OprtPowElementWise::OprtPowElementWise()
    :IOprtBin(_T("^"), (int)prPOW, oaRIGHT) 
  {}
                                                                        
  //-----------------------------------------------------------
/** \brief Implements the Power operator.
  \throw ParserError in case one of the arguments if 
*/
  void OprtPowElementWise::Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int num)
  {
    assert(num == 2);
    const IValue* arg1 = a_pArg[0].Get();
    const IValue* arg2 = a_pArg[1].Get();
  
    if (arg1->GetType() == 'm' && arg2->GetType() == 'm') {
      // Vector + Vector
      const matrix_type &a1 = arg1->GetArray(),
                        &a2 = arg2->GetArray();
  
      //Gets the smallest size
      int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();
      
      matrix_type rv(size); //this variable receive the result of operation
      for (int i=0; i<size; i++) { // do the operation between arg1 and agr2 for each element of the smallest array
        if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
          throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
  
        if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
          throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
  
//        int ib = a2.At(i).GetInteger();
//        if (a2.At(i).GetFloat() - ib == 0) {
//          *ret = std::pow(a1.At(i).GetFloat(), ib);
//        }
//        else
          std::cout << "a1.At(i) = " << a1.At(i).GetFloat() << std::endl;
          std::cout << "a2.At(i) = " << a2.At(i).GetFloat() << std::endl;
          *ret = std::pow((int) a1.At(i).GetFloat(), (int) a2.At(i).GetFloat());
      }
    }
    else if (arg1->GetType() == 'm' && arg2->IsNonComplexScalar()){
      // Vector ^ Scalar
      const matrix_type &a1 = arg1->GetArray();
      
      matrix_type rv(a1.GetRows());//this variable receive the result of operation, your size is equal to arg1 size
      for (int i=0; i<a1.GetRows(); i++) {// do the operation between arg1 and agr2 for each element of the arg1 (vector)
        if (!a1.At(i).IsNonComplexScalar())// if the element from array of arg1 isn't a non-complex scalar
          throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));
          
        //int ib = arg2->GetInteger();
        //if (a1.At(i).GetFloat() - ib == 0) {
        //  *ret = std::pow(a1.At(i).GetFloat(), ib);
        //}
        //else
          *ret = std::pow(a1.At(i).GetFloat(), arg2->GetFloat());
      }
    }
    else if (arg2->GetType() == 'm' && arg1->IsNonComplexScalar()){
      // Scalar ^ Vector
      const matrix_type &a2 = arg2->GetArray();
  
      matrix_type rv(a2.GetRows());//this variable receive the result of operation, your size is equal to arg2 size
      for (int i=0; i<a2.GetRows(); i++) {// do the operation between arg1 and agr2 for each element of the arg2 (vector)
        if (!a2.At(i).IsNonComplexScalar())// if the element from array of arg2 isn't a non-complex scalar
          throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));
    
        //int ib = arg2->GetInteger();
        //if (a2.At(i).GetFloat() - ib == 0) {
        //  *ret = std::pow(a2.At(i).GetFloat(), ib);
        //}
        //else
          *ret = std::pow(arg1->GetFloat(), a2.At(i).GetFloat());
      }
    }
    else{
      if (!arg1->IsNonComplexScalar())// if the element of arg1 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));
  
      if (!arg2->IsNonComplexScalar())// if the element of arg2 isn't a non-complex scalar
        throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg2->GetType(), 'f', 2));
  
      //int ib = arg2->GetInteger();
      //if (arg1->GetFloat() - ib == 0) {
        //*ret = std::pow(arg1->GetFloat(), ib);
      //}
      //else
        *ret = std::pow(arg1->GetFloat(), arg2->GetFloat());
    }
  }
  //-----------------------------------------------------------
  const char_type* OprtPowElementWise::GetDesc() const
  { 
    return _T("x^y - Raises x to the power of y.");
  }

  //-----------------------------------------------------------
  IToken* OprtPowElementWise::Clone() const
  { 
    return new OprtPowElementWise(*this);
  }
}
