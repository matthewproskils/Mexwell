#include "compiler.h"

#pragma once

inline TokenType Compiler::getType()
{
  return tokens[ParsedIndex]->type;
}

inline string Compiler::getValue()
{
  return tokens[ParsedIndex]->value;
}

inline void Compiler::incPtr()
{
  if (ParsedIndex > tokens.size())
  {
    std::cout << "Compiler Error, Unexpected End Of File" << std::endl;
    exit(1);
  }
}