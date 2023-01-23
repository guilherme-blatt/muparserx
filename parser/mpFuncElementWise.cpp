/** \file
    \brief Implementation of basic functions used by muParserX.

<pre>
               __________                                 ____  ___
    _____  __ _\______   \_____ _______  ______ __________\   \/  /
   /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     / 
  |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \ 
  |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
        \/                     \/           \/     \/           \_/
                                       Copyright (C) 2016, Ingo Berg
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
  </pre>
*/
#include "mpFuncElementWise.h"

//--- Standard includes ----------------------------------------------------
#include <cmath>
#include <cassert>
#include <iostream>

//--- muParserX framework --------------------------------------------------
#include "mpValue.h"
#include "mpError.h"

#undef log
#undef log2

MUP_NAMESPACE_START

#define MUP_UNARY_FUNC_ELEMENT_WISE(CLASS, IDENT, FUNC, DESC)                                                           \
    CLASS::CLASS()                                                                                                      \
    :ICallback(cmFUNC, _T(IDENT), 1)                                                                                    \
    {}                                                                                                                  \
                                                                                                                        \
    void CLASS::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)                                            \
    {                                                                                                                   \
      assert(num==1);                                                                                                   \
      const IValue *arg1 = a_pArg[0].Get();                                                                             \
      if (arg1->GetType()=='m')                                                                                         \
      {                                                                                                                 \
        /* Vector */                                                                                                    \
        const matrix_type &a1 = arg1->GetArray();                                                                       \
        matrix_type rv(a1.GetRows());                                                                                   \
        /* do the operation for each element in arg1 */                                                                 \
        for (int i=0; i<a1.GetRows(); ++i)                                                                              \
        {                                                                                                               \
          if (!a1.At(i).IsNonComplexScalar())/* if the element from array of arg1 isn't a non-complex scalar*/          \
            throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));          \
                                                                                                                        \
          rv.At(i) = FUNC(a1.At(i).GetFloat());                                                                         \
        }                                                                                                               \
        *ret = rv;                                                                                                      \
      }                                                                                                                 \
      else                                                                                                              \
      {/* Scalar */                                                                                                     \
        if (!arg1->IsNonComplexScalar())/* if the element of arg1 isn't a non-complex scalar*/                          \
          throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));               \
                                                                                                                        \
        *ret = FUNC(arg1->GetFloat());                                                                                  \
      }                                                                                                                 \
    }                                                                                                                   \
                                                                                                                        \
    const char_type* CLASS::GetDesc() const                                                                             \
    {                                                                                                                   \
      return _T(DESC);                                                                                                  \
    }                                                                                                                   \
                                                                                                                        \
    IToken* CLASS::Clone() const                                                                                        \
    {                                                                                                                   \
      return new CLASS(*this);                                                                                          \
    }

    // trigonometric functions
    MUP_UNARY_FUNC_ELEMENT_WISE(FunTanElementWise,   "sin",   std::sin,   "sine function")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunCosElementWise,   "cos",   std::cos,   "cosine function")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunSinElementWise,   "tan",   std::tan,   "tangens function")
    // arcus functions
    MUP_UNARY_FUNC_ELEMENT_WISE(FunASinElementWise,  "asin",  std::asin,  "arcus sine")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunACosElementWise,  "acos",  std::acos,  "arcus cosine")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunATanElementWise,  "atan",  std::atan,  "arcus tangens")
    // hyperbolic functions
    MUP_UNARY_FUNC_ELEMENT_WISE(FunSinHElementWise,  "sinh",  std::sinh,  "hyperbolic sine")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunCosHElementWise,  "cosh",  std::cosh,  "hyperbolic cosine")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunTanHElementWise,  "tanh",  std::tanh,  "hyperbolic tangens")
    // hyperbolic arcus functions
    MUP_UNARY_FUNC_ELEMENT_WISE(FunASinHElementWise, "asinh", std::asinh, "hyperbolic arcus sine")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunACosHElementWise, "acosh", std::acosh, "hyperbolic arcus cosine")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunATanHElementWise, "atanh", std::atanh, "hyperbolic arcus tangens")
    // logarithm functions
    MUP_UNARY_FUNC_ELEMENT_WISE(FunLogElementWise,   "log",   std::log,   "Natural logarithm")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunLog10ElementWise, "log10", std::log10, "Logarithm base 10")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunLog2ElementWise,  "log2",  std::log2,  "Logarithm base 2")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunLnElementWise,    "ln",    std::log,   "Natural logarithm")
    // square root
    MUP_UNARY_FUNC_ELEMENT_WISE(FunSqrtElementWise,  "sqrt",  std::sqrt,  "sqrt(x) - square root of x")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunCbrtElementWise,  "cbrt",  std::cbrt,  "cbrt(x) - cubic root of x")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunExpElementWise,   "exp",   std::exp,   "exp(x) - e to the power of x")
    MUP_UNARY_FUNC_ELEMENT_WISE(FunAbsElementWise,   "abs",   std::fabs,  "abs(x) - absolute value of x")
#undef MUP_UNARY_FUNC_ELEMENT_WISE

#define MUP_BINARY_FUNC_ELEMENT_WISE(CLASS, IDENT, FUNC, DESC)                                                          \
    CLASS::CLASS()                                                                                                      \
    :ICallback(cmFUNC, _T(IDENT), 2)                                                                                    \
    {}                                                                                                                  \
                                                                                                                        \
    void CLASS::Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int num)                                            \
    {                                                                                                                   \
      assert(num==2);                                                                                                   \
      const IValue *arg1 = a_pArg[0].Get();                                                                             \
      const IValue *arg2 = a_pArg[1].Get();                                                                             \
      if (arg1->GetType()=='m' && arg2->GetType()=='m')                                                                 \
      {                                                                                                                 \
        /* Vector + Vector*/                                                                                            \
        const matrix_type &a1 = arg1->GetArray(),                                                                       \
            &a2 = arg2->GetArray();                                                                                     \
                                                                                                                        \
        /*Gets the smallest size*/                                                                                      \
        int size = a1.GetRows() < a2.GetRows() ? a1.GetRows() : a2.GetRows();                                           \
                                                                                                                        \
        matrix_type rv(size);/*this variable receive the result of operation*/                                          \
        for (int i=0; i<size; ++i)/* do the operation between arg1 and agr2 for each element of the smallest array*/    \
        {                                                                                                               \
          if (!a1.At(i).IsNonComplexScalar())/* if the element from array of arg1 isn't a non-complex scalar*/          \
            throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));          \
                                                                                                                        \
          if (!a2.At(i).IsNonComplexScalar())/* if the element from array of arg2 isn't a non-complex scalar*/          \
            throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));          \
                                                                                                                        \
          rv.At(i) = FUNC(a1.At(i).GetFloat(), a2.At(i).GetFloat());                                                    \
        }                                                                                                               \
        *ret = rv;                                                                                                      \
      }                                                                                                                 \
                                                                                                                        \
      else if (arg1->GetType()=='m' && arg2->IsNonComplexScalar()) {                                                    \
        /* Vector + Scalar*/                                                                                            \
        const matrix_type &a1 = arg1->GetArray();                                                                       \
                                                                                                                        \
        matrix_type rv(a1.GetRows());/*this variable receive the result of operation, your size is equal to arg1 size*/ \
        /* do the operation between arg1 and agr2 for each element of the arg1 (vector)*/                               \
        for (int i = 0; i < a1.GetRows(); ++i) {                                                                        \
          if (!a1.At(i).IsNonComplexScalar())/* if the element from array of arg1 isn't a non-complex scalar*/          \
            throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a1.At(i).GetType(), 'f', 1));          \
                                                                                                                        \
          rv.At(i) = FUNC(a1.At(i).GetFloat(), arg2->GetFloat());                                                       \
        }                                                                                                               \
        *ret = rv;                                                                                                      \
      }                                                                                                                 \
                                                                                                                        \
      else if(arg1->IsNonComplexScalar() && arg2->GetType()=='m') {                                                     \
        /*Scalar + Vector*/                                                                                             \
        const matrix_type &a2 = arg2->GetArray();                                                                       \
        matrix_type rv(a2.GetRows());/*this variable receive the result of operation, your size is equal to arg2 size*/ \
        /* do the operation between arg1 and agr2 for each element of the arg1 (vector)*/                               \
        for (int i = 0; i < a2.GetRows(); ++i) {                                                                        \
          if (!a2.At(i).IsNonComplexScalar())/* if the element from array of arg2 isn't a non-complex scalar*/          \
            throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), a2.At(i).GetType(), 'f', 1));          \
                                                                                                                        \
          rv.At(i) = FUNC(arg1->GetFloat(), a2.At(i).GetFloat());                                                       \
        }                                                                                                               \
        *ret = rv;                                                                                                      \
      }                                                                                                                 \
      else                                                                                                              \
      {/*Scalar + Scalar*/                                                                                              \
        if (!arg1->IsNonComplexScalar())/* if the element of arg1 isn't a non-complex scalar*/                          \
          throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg1->GetType(), 'f', 1));               \
                                                                                                                        \
        if (!arg2->IsNonComplexScalar())/* if the element of arg2 isn't a non-complex scalar*/                          \
          throw ParserError( ErrorContext(ecTYPE_CONFLICT_FUN, -1, GetIdent(), arg2->GetType(), 'f', 2));               \
                                                                                                                        \
        *ret = FUNC(arg1->GetFloat(), arg2->GetFloat());                                                                \
      }                                                                                                                 \
    }                                                                                                                   \
                                                                     \
    const char_type* CLASS::GetDesc() const                          \
    {                                                                \
      return _T(DESC);                                               \
    }                                                                \
                                                                     \
    IToken* CLASS::Clone() const                                     \
    {                                                                \
      return new CLASS(*this);                                       \
    }

    MUP_BINARY_FUNC_ELEMENT_WISE(FunPowElementWise,  "pow",  std::pow,  "pow(x, y) - raise x to the power of y")
    MUP_BINARY_FUNC_ELEMENT_WISE(FunHypotElementWise,  "hypot",  std::hypot,  "hypot(x, y) - compute the length of the vector x,y")
    MUP_BINARY_FUNC_ELEMENT_WISE(FunAtan2ElementWise, "atan2", std::atan2, "arcus tangens with quadrant fix")
    MUP_BINARY_FUNC_ELEMENT_WISE(FunFmodElementWise,  "fmod",  std::fmod,  "fmod(x, y) - floating point remainder of x / y")
    MUP_BINARY_FUNC_ELEMENT_WISE(FunRemainderElementWise,  "remainder",  std::remainder,  "remainder(x, y) - IEEE remainder of x / y")
#undef MUP_BINARY_FUNC_ELEMENT_WISE

MUP_NAMESPACE_END
