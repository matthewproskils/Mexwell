#include "compiler.h"

#pragma once

inline std::pair<string, Symbol *> Compiler::Variable(Token *t)
{
  bool isConstant = (t->value == "const");
  string varName = t->get_child("Name")->value;
  Symbol *var = Value(t->get_child("Name"), isConstant);

  return std::make_pair(varName, var);
}
