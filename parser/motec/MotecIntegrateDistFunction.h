//
// Created by Optimum G on 1/27/2023.
//

#ifndef MUPARSERX_MOTECINTEGRATEDISTFUNCTION_H
#define MUPARSERX_MUPARSERX_MOTECINTEGRATEDISTFUNCTION_H

#include "../mpICallback.h"
#include "../mpParser.h"

MUP_NAMESPACE_START

class IntegrateDist : public ICallback
{
  int frequency_;
public:
  IntegrateDist (int frequency) :ICallback(cmFUNC, _T("integrate_dist"), -1 ){frequency_ = frequency;};
  
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  
  virtual const char_type* GetDesc() const override
  {
    return _T("parserid() - muParserX version information");
  }
  
  virtual IToken* Clone() const override
  {
    return new IntegrateDist(*this);
  }
}; // class IntegrateDist

#endif //MUPARSERX_MUPARSERX_MOTECINTEGRATEDISTFUNCTION_H

}//namespace end