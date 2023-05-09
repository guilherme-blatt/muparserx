//
// Created by Optimum G on 1/27/2023.
//

#ifndef MUPARSERX_MOTECSTATMEANFUNCTION_H
#define MUPARSERX_MUPARSERX_MOTECSTATMEANFUNCTION_H

#include "../mpICallback.h"
#include "../mpParser.h"

MUP_NAMESPACE_START

class StatMean : public ICallback
{
public:
  StatMean () :ICallback(cmFUNC, _T("stat_mean"), -1 ){};
  
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  
  virtual const char_type* GetDesc() const override
  {
    return _T("parserid() - muParserX version information");
  }
  
  virtual IToken* Clone() const override
  {
    return new StatMean(*this);
  }
}; // class StatMean

#endif //MUPARSERX_MUPARSERX_MOTECSTATMEANFUNCTION_H

}//namespace end