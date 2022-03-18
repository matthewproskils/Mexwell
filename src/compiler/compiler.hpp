#include "compiler.h"

#include "function.hpp"
#include "functionArgs.hpp"
#include "scope.hpp"
#include "util.hpp"
#include "value.hpp"
#include "variable.hpp"
#include "if.hpp"
#pragma once

inline Compiler::Compiler() {}

inline void Compiler::compile(Scope *global, vector<Token *> t)
{
  this->ParsedIndex = 0;
  this->tokens = t;
  this->global = global;

  while (ParsedIndex < t.size())
  {
    if (getType() == TokenType::VariableDef)
    {
      global->add_symbol(Variable(t[ParsedIndex]));
    }
    else if (getType() == TokenType::FuncDeclaration)
    {
      global->add_symbol(Function(t[ParsedIndex]));
    }
    else if (getType() == TokenType::ExpressionCall)
    {
      ExprCall(t[ParsedIndex], global);
    }
    else if (getType() == TokenType::IfWrap)
    {
      If(t[ParsedIndex], global);
    }
    else
    {
      Error(t[ParsedIndex], "Unexpected Token, expected 'variable declaration', 'function declaration', or 'expression call'", FileName);
    }
    ParsedIndex++;
  }
}