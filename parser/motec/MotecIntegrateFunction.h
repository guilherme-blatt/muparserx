//
// Created by Optimum G on 1/27/2023.
//

#ifndef MUPARSERX_MOTECINTEGRATEFUNCTION_H
#define MUPARSERX_MUPARSERX_MOTECINTEGRATEFUNCTION_H

#include "../mpICallback.h"
#include "../mpParser.h"

MUP_NAMESPACE_START

class Integrate : public ICallback
{
  int frequency_;
public:
  Integrate (int frequency) :ICallback(cmFUNC, _T("integrate") ) {frequency_ = frequency;};
  
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  
  virtual const char_type* GetDesc() const override
  {
    return _T("parserid() - muParserX version information");
  }
  
  virtual IToken* Clone() const override
  {
    return new Integrate(*this);
  }
}; // class Integrate

#endif //MUPARSERX_MUPARSERX_MOTECINTEGRATEFUNCTION_H

}//namespace end