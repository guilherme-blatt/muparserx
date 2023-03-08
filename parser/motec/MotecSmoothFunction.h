//
// Created by Optimum G on 1/27/2023.
//

#ifndef MUPARSERX_MOTECSMOOTHFUNCTION_H
#define MUPARSERX_MUPARSERX_MOTECSMOOTHFUNCTION_H

#include "../mpICallback.h"
#include "../mpParser.h"

MUP_NAMESPACE_START

class Smooth : public ICallback
{
  int frequency_;
public:
  Smooth (int frequency) :ICallback(cmFUNC, _T("smooth"), 2) {frequency_ = frequency;};
  
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  
  virtual const char_type* GetDesc() const override
  {
    return _T("parserid() - muParserX version information");
  }
  
  virtual IToken* Clone() const override
  {
    return new Smooth(*this);
  }
}; // class Smooth

class SmoothFunction{
public:
  static matrix_type Smooth(ptr_val_type &ret, const ptr_val_type *a_pArg, int frequency);
  
};
#endif //MUPARSERX_MUPARSERX_MOTECSMOOTHFUNCTION_H

}//namespace end