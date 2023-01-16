/*
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
*/
#include "mpPackageElementWise.h"

#include "mpParserBase.h"
#include "mpFuncElementWise.h"
#include "mpOprtElementWise.h"
#include "mpOprtBinCommon.h"


MUP_NAMESPACE_START

//------------------------------------------------------------------------------
std::unique_ptr<PackageElementWise> PackageElementWise::s_pInstance;

//------------------------------------------------------------------------------
IPackage* PackageElementWise::Instance()
{
  if (s_pInstance.get()==nullptr)
  {
    s_pInstance.reset(new PackageElementWise);
  }

  return s_pInstance.get();
}

//------------------------------------------------------------------------------
void PackageElementWise::AddToParser(ParserXBase *pParser)
{
  pParser->DefineFun(new FunSinElementWise());
  pParser->DefineFun(new FunCosElementWise());
  pParser->DefineFun(new FunTanElementWise());
  pParser->DefineFun(new FunSinHElementWise());
  pParser->DefineFun(new FunCosHElementWise());
  pParser->DefineFun(new FunTanHElementWise());
  pParser->DefineFun(new FunASinElementWise());
  pParser->DefineFun(new FunACosElementWise());
  pParser->DefineFun(new FunATanElementWise());
  pParser->DefineFun(new FunASinHElementWise());
  pParser->DefineFun(new FunACosHElementWise());
  pParser->DefineFun(new FunATanHElementWise());
  pParser->DefineFun(new FunLogElementWise());
  pParser->DefineFun(new FunLog10ElementWise());
  pParser->DefineFun(new FunLog2ElementWise());
  pParser->DefineFun(new FunLnElementWise());
  pParser->DefineFun(new FunExpElementWise());
  pParser->DefineFun(new FunSqrtElementWise());
  pParser->DefineFun(new FunCbrtElementWise());
  pParser->DefineFun(new FunAbsElementWise());

  // binary functions
  pParser->DefineFun(new FunPowElementWise());
  pParser->DefineFun(new FunHypotElementWise());
  pParser->DefineFun(new FunAtan2ElementWise());
  pParser->DefineFun(new FunFmodElementWise());
  pParser->DefineFun(new FunRemainderElementWise());

  // Operator callbacks
  pParser->DefineInfixOprt(new OprtSignElementWise());
  pParser->DefineInfixOprt(new OprtSignPosElementWise());
  pParser->DefineOprt(new OprtAddElementWise());
  pParser->DefineOprt(new OprtSubElementWise());
  pParser->DefineOprt(new OprtMulElementWise());
  pParser->DefineOprt(new OprtDivElementWise());
  pParser->DefineOprt(new OprtPowElementWise());
}

//------------------------------------------------------------------------------
string_type PackageElementWise::GetDesc() const
{
  return _T("");
}

//------------------------------------------------------------------------------
string_type PackageElementWise::GetPrefix() const
{
  return _T("");
}

MUP_NAMESPACE_END
