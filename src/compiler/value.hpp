#include "compiler.h"

#pragma once

inline Symbol *Compiler::Value(Token *t, bool isConstant)
{
  if (t->type == TokenType::Number)
  {
    return new Symbol(t->value, SymbolType::Number, isConstant);
  }
  else if (t->type == TokenType::String)
  {
    return new Symbol(t->value, SymbolType::String, isConstant);
  }
  else if (t->value == "true" || t->value == "false")
  {
    return new Symbol(t->value, SymbolType::Boolean, isConstant);
  }
  else if (t->type == TokenType::ExpressionCall)
  {
    return ExprCall(t, global);
  }
  else if (t->type == TokenType::Expression)
  {
    return global->get_symbol(t->value);
  }
  else
  {
    std::cout << "Invalid Type " << to_underlying(t->type) << "?" << std::endl;
    exit(1);
  }
}
