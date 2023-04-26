//
// Created by Optimum G on 1/27/2023.
//

#include "MotecDefinition.h"

MUP_NAMESPACE_START

void motecDefinition::add_motec_functions(mup::ParserX* parser, int frequency)
{
  parser->DefineFun(new RandValue());
  parser->DefineFun(new MotecFrac());
  parser->DefineFun(new MotecInt());
  parser->DefineFun(new MotecIsFinite());
  parser->DefineFun(new MotecSquare());
  parser->DefineFun(new MotecToDouble());
  parser->DefineFun(new MotecInvalid());
  parser->DefineFun(new MotecSgn());
  parser->DefineFun(new Choose());
  parser->DefineFun(new Smooth(frequency));
  parser->DefineFun(new Derivative(frequency));
  parser->DefineFun(new Integrate(frequency));
  parser->DefineFun(new IntegrateDist(frequency));
  
  
}



}//Namespace
