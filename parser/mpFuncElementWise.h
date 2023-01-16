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
#ifndef MUP_FUNC_ELEMENT_WISE_H
#define MUP_FUNC_ELEMENT_WISE_H

#include "mpICallback.h"

/** \defgroup functions Function callback objects.

  This group lists the objects representing parser functions.
*/


MUP_NAMESPACE_START

#define MUP_UNARY_FUNC_ELEMENT_WISE_DEF(CLASS)                                          \
    class CLASS : public ICallback                                         \
    {                                                                      \
    public:                                                                \
      CLASS();                                                             \
      virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;  \
      virtual const char_type* GetDesc() const override;                   \
      virtual IToken* Clone() const override;                              \
    }; 

    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunSinElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunCosElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunTanElementWise)
    // arcus functions
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunASinElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunACosElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunATanElementWise)
    // hyperbolic functions
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunSinHElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunCosHElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunTanHElementWise)
    // hyperbolic arcus functions
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunASinHElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunACosHElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunATanHElementWise)
    // logarithm functions
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunLogElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunLog10ElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunLog2ElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunLnElementWise)
    // square root
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunSqrtElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunCbrtElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunExpElementWise)
    MUP_UNARY_FUNC_ELEMENT_WISE_DEF(FunAbsElementWise)
#undef MUP_UNARY_FUNC_ELEMENT_WISE_DEF

#define MUP_BINARY_FUNC_ELEMENT_WISE_DEF(CLASS)                                          \
    class CLASS : public ICallback                                         \
    {                                                                      \
    public:                                                                \
      CLASS();                                                             \
      virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;  \
      virtual const char_type* GetDesc() const override;                   \
      virtual IToken* Clone() const override;                              \
    };

    MUP_BINARY_FUNC_ELEMENT_WISE_DEF(FunPowElementWise)
    MUP_BINARY_FUNC_ELEMENT_WISE_DEF(FunHypotElementWise)
    MUP_BINARY_FUNC_ELEMENT_WISE_DEF(FunAtan2ElementWise)
    MUP_BINARY_FUNC_ELEMENT_WISE_DEF(FunFmodElementWise)
    MUP_BINARY_FUNC_ELEMENT_WISE_DEF(FunRemainderElementWise)
#undef MUP_BINARY_FUNC_ELEMENT_WISE_DEF

}  // namespace mu

#endif
