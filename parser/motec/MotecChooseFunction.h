//
// Created by Optimum G on 1/27/2023.
//

#ifndef MUPARSERX_MOTECCHOOSEFUNCTION_H
#define MUPARSERX_MUPARSERX_MOTECCHOOSEFUNCTION_H

#include "../mpICallback.h"
#include "../mpParser.h"

MUP_NAMESPACE_START

class Choose : public ICallback
{
public:
  Choose () :ICallback(cmFUNC, _T("choose"), 3) {};
  
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  
  virtual const char_type* GetDesc() const override
  {
    return _T("parserid() - muParserX version information");
  }
  
  virtual IToken* Clone() const override
  {
    return new Choose(*this);
  }
}; // class Choose

#endif //MUPARSERX_MUPARSERX_MOTECCHOOSEFUNCTION_H

}//namespace end