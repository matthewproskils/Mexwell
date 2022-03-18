#include "compiler.h"

#pragma once

inline TokenType Compiler::getType()
{
  return tokens[ParsedIndex]->type;
}