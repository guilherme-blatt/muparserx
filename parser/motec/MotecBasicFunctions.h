//
// Created by Optimum G on 1/27/2023.
//

#ifndef MUPARSERX_MOTECBASICFUNCTIONS_H
#define MUPARSERX_MUPARSERX_MOTECBASICFUNCTIONS_H

#include "../mpICallback.h"
#include "../mpParser.h"
#include <random>

MUP_NAMESPACE_START

class RandValue : public ICallback
{
  bool has_seed_been_defined_ = false;
  
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
}; // class RandValue

//Integer part of scalar or a vector (Rounds the value towards zero)
class MotecInt : public ICallback
{
public:
  MotecInt () :ICallback(cmFUNC, _T("integer"), 1) {};
  
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  
  virtual const char_type* GetDesc() const override
  {
    return _T("parserid() - muParserX version information");
  }
  
  virtual IToken* Clone() const override
  {
    return new MotecInt(*this);
  }
}; // class MotecInt

//Returns true if the value is finite
class MotecIsFinite : public ICallback
{
public:
  MotecIsFinite () :ICallback(cmFUNC, _T("is_finite"), 1) {};
  
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  
  virtual const char_type* GetDesc() const override
  {
    return _T("parserid() - muParserX version information");
  }
  
  virtual IToken* Clone() const override
  {
    return new MotecIsFinite(*this);
  }
}; // class MotecIsFinite

//Square of scalar or a vector
class MotecSquare : public ICallback
{
public:
  MotecSquare () :ICallback(cmFUNC, _T("sqr"), 1) {};
  
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  
  virtual const char_type* GetDesc() const override
  {
    return _T("parserid() - muParserX version information");
  }
  
  virtual IToken* Clone() const override
  {
    return new MotecSquare(*this);
  }
}; // class MotecSquare

class MotecToDouble : public ICallback
{
public:
  MotecToDouble () :ICallback(cmFUNC, _T("to_double"), 1) {};
  
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  
  virtual const char_type* GetDesc() const override
  {
    return _T("parserid() - muParserX version information");
  }
  
  virtual IToken* Clone() const override
  {
    return new MotecToDouble(*this);
  }
}; // class MotecToDouble

class MotecFrac : public ICallback
{
public:
  MotecFrac () :ICallback(cmFUNC, _T("frac"), 1) {};
  
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  
  virtual const char_type* GetDesc() const override
  {
    return _T("parserid() - muParserX version information");
  }
  
  virtual IToken* Clone() const override
  {
    return new MotecFrac(*this);
  }
}; // class MotecToDouble

class MotecInvalid : public ICallback
{
public:
  MotecInvalid () :ICallback(cmFUNC, _T("invalid"), 0) {};
  
  virtual void Eval(ptr_val_type &ret, const ptr_val_type *a_pArg, int a_iArgc) override;
  
  virtual const char_type* GetDesc() const override
  {
    return _T("parserid() - muParserX version information");
  }
  
  virtual IToken* Clone() const override
  {
    return new MotecInvalid(*this);
  }
}; // class MotecToDouble

#endif //MUPARSERX_MUPARSERX_MOTECBASICFUNCTIONS_H

}//namespace end