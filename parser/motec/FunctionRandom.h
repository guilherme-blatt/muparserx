//
// Created by Optimum G on 1/27/2023.
//

#ifndef MUPARSERX_FUNCTIONRANDOM_H
#define MUPARSERX_FUNCTIONRANDOM_H

#include "../mpICallback.h"
#include "../mpParser.h"

MUP_NAMESPACE_START

class RandValue : public ICallback
{
public:
  RandValue () :ICallback(cmFUNC, _T("rand_val"), -1) {};
  
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  
  virtual const char_type* GetDesc() const override
  {
    return _T("parserid() - muParserX version information");
  }
  
  virtual IToken* Clone() const override
  {
    return new RandValue(*this);
  }
}; // class FunParserID

#endif //MUPARSERX_FUNCTIONRANDOM_H

}//namespace end