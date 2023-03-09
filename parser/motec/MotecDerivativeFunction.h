//
// Created by Optimum G on 1/27/2023.
//

#ifndef MUPARSERX_MOTECSMOOTHFUNCTION_H
#define MUPARSERX_MUPARSERX_MOTECSMOOTHFUNCTION_H

#include "../mpICallback.h"
#include "../mpParser.h"

MUP_NAMESPACE_START

class Derivative : public ICallback
{
  int frequency_;
public:
  Derivative (int frequency) :ICallback(cmFUNC, _T("derivative"), 2) {frequency_ = frequency;};
  
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  
  virtual const char_type* GetDesc() const override
  {
    return _T("parserid() - muParserX version information");
  }
  
  virtual IToken* Clone() const override
  {
    return new Derivative(*this);
  }
}; // class Derivative

class DerivativeFunction{
public:
  static matrix_type Derivative(ptr_val_type &ret, const ptr_val_type *a_pArg, int frequency);
};
#endif //MUPARSERX_MUPARSERX_MOTECSMOOTHFUNCTION_H

}//namespace end