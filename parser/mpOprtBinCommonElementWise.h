/*
                __________                                 ____  ___
     _____  __ _\______   \_____ _______  ______ __________\   \/  /
    /     \|  |  \     ___/\__  \\_  __ \/  ___// __ \_  __ \     /
    |  Y Y  \  |  /    |     / __ \|  | \/\___ \\  ___/|  | \/     \
    |__|_|  /____/|____|    (____  /__|  /____  >\___  >__| /___/\  \
          \/                     \/           \/     \/           \_/
    Copyright (C) 2022 Ingo Berg, et al.
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
#ifndef MP_OPRT_BIN_ELEMENT_WISE_H
#define MP_OPRT_BIN_ELEMENT_WISE_H

/** \file
    \brief Definitions of classes used as callbacks for standard binary operators.
    */

/** \defgroup binop Binary operator callbacks

  This group lists the objects representing the binary operators of muParserX.
  */

#include <cmath>
#include "mpIOprt.h"
#include "mpValue.h"
#include "mpError.h"


MUP_NAMESPACE_START


class OprtStrAddElementWise : public IOprtBin
{
public:
  OprtStrAddElementWise();
  virtual void Eval(ptr_val_type& ret, const ptr_val_type *arg, int argc) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
};


/** \brief Callback object for testing if two values are equal.
    \ingroup binop
    */
class OprtEQElementWise : public IOprtBin
{
public:
  OprtEQElementWise();
  virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
};


/** \brief Callback object for testing if two values are not equal.
    \ingroup binop
    */
class OprtNEQElementWise : public IOprtBin
{
public:
  OprtNEQElementWise();
  virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
};


/** \brief Callback object class for the "Less than" operator.
    \ingroup binop
    */
class OprtLTElementWise : public IOprtBin
{
public:
  OprtLTElementWise();
  virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
};


/** \brief Callback object class for the "Greater than" operator.
    \ingroup binop
    */
class OprtGTElementWise : public IOprtBin
{
public:
  OprtGTElementWise();
  virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
};


/** \brief Callback object class for the "Less or equal" operator.
    \ingroup binop
    */
class OprtLEElementWise : public IOprtBin
{
public:
  OprtLEElementWise();
  virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
};


/** \brief Callback object class for the "Greater or or equal" operator.
    \ingroup binop
    */
class OprtGEElementWise : public IOprtBin
{
public:
  OprtGEElementWise();
  virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
};


/** \brief Callback class for a logic and operator.
    \ingroup binop
    */
class OprtAndElementWise : public IOprtBin
{
public:
  OprtAndElementWise();
  virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
};


/** \brief Callback class for a logic or operator.
    \ingroup binop
    */
class OprtOrElementWise : public IOprtBin
{
public:
  OprtOrElementWise();
  virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
};


/** \brief Callback class for a logical or operator.
    \ingroup binop
*/
class OprtLogicOrElementWise : public IOprtBin
{
public:
  OprtLogicOrElementWise(const char_type* szIdent = _T("||"));
  virtual void Eval(ptr_val_type& ret, const ptr_val_type* a_pArg, int) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
};


/** \brief Callback class for a logical and operator.
    \ingroup binop
*/
class OprtLogicAndElementWise : public IOprtBin
{
public:
  OprtLogicAndElementWise(const char_type* szIdent = _T("&&"));
  virtual void Eval(ptr_val_type& ret, const ptr_val_type* a_pArg, int) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
};


/** \brief Callback class for the shift left operator.
    \ingroup binop
    */
class OprtShlElementWise : public IOprtBin
{
public:
  OprtShlElementWise();
  virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
};


/** \brief Callback class for the shift right operator.
    \ingroup binop
    */
class OprtShrElementWise : public IOprtBin
{
public:
  OprtShrElementWise();
  virtual void Eval(ptr_val_type& ret, const ptr_val_type *a_pArg, int) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
};


/** \brief Callback for an operator allowing to cast values to floating
           point values.
           \ingroup infix
           */
class OprtCastToFloatElementWise : public IOprtInfix
{
public:
  OprtCastToFloatElementWise();
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
}; // class OprtCastToFloatElementWise


/** \brief Callback for an operator allowing to cast values to integer values.
    \ingroup infix
*/
class OprtCastToIntElementWise : public IOprtInfix
{
public:
  OprtCastToIntElementWise();
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  virtual const char_type* GetDesc() const override;
  virtual IToken* Clone() const override;
}; // class OprtCastToIntElementWise

}  // namespace mu

#endif
