#include "compiler.h"
#include "scope.hpp"

#pragma once

// Define a function
inline std::pair<string, Symbol *> Compiler::Function(Token *t)
{
  std::map<string, string> args = {};

  for (std::pair<string, Token *> a : t->get_child("FuncArgs")->Children)
  {
    args.insert(make_pair(a.second->get_child("Type")->value, a.second->get_child("Value")->value));
  }

  std::vector<Token *> code = {};

  for (std::pair<string, Token *> a : t->get_child("expr")->Children)
  {
    code.push_back(a.second);
  }

  SymbolFunction *f = new SymbolFunction(t->get_child("FuncName")->value, args, global->get_type(t->get_child("ReturnType")->value), code);

  Symbol *s = new Symbol(f);

  return std::pair<string, Symbol *>(t->get_child("FuncName")->value, s);
}


inline Symbol *Compiler::ExprCall(Token *t, Scope *global)
{
  if (global->get_symbol(t->value)->Func->isNative)
  {
    vector<Symbol *> args = nativeArgs(global, t);
    return global->get_symbol(t->value)->Func->nativeFunc(args);
  }
  else
  {
    Scope *funcScope = funcArgs(global, t);
    Compiler *funCompiler = new Compiler();
    funCompiler->compile(funcScope, global->get_symbol(getValue())->Func->code);

    if (funcScope->hasSymbol("return"))
    {
      return funcScope->get_symbol("return");
    }
    else
    {
      std::cout << "Compiler error, function did not return a value [return using 'var return = {insert value here}]'" << std::endl;
      exit(1);
    }
  }
}