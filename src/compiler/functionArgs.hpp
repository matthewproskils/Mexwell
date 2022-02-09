#include "compiler.h"

#pragma once

inline Scope *Compiler::funcArgs(Scope *scope, Token *t)
{

  // Get the function
  Symbol *v = scope->get_symbol(t->value);

  if (v->Func == nullptr)
  {
    std::cout << "Compiler Error, Function not found: " << t->value << std::endl;
    exit(1);
  }

  SymbolFunction *f = v->Func;

  // Set Function Scope
  Scope *funcScope = new Scope(scope);

  // Check if it is function
  if (f == nullptr)
  {
    std::cout << "Compiler Error, " << t->value << " is not a function" << std::endl;
    exit(1);
  }

  // Check if the number of arguments is correct
  if (f->args.size() != t->Children.size())
  {
    std::cout << "Compiler Error, " << t->value << " takes " << f->args.size() << " arguments, " << t->get_child("FuncArgs")->Children.size() << " given" << std::endl;
    exit(1);
  }

  // Check Type of arguments
  int j = 0;
  for (pair<string, string> i : f->args)
  {
    funcScope->add_symbol(i.first, Value(t->get_child("arg" + std::to_string(j)), false));
  }

  return funcScope;
}



inline vector<Symbol *> Compiler::nativeArgs(Scope *global, Token *t)
{
  // Get the function
  SymbolFunction *f = global->get_symbol(t->value)->Func;

  // Check if argument size is correct
  if (f->nativeArgs.size() != t->Children.size())
  {
    std::cout << "Compiler Error, " << t->value << " takes " << f->args.size() << " arguments, " << t->get_child("FuncArgs")->Children.size() << " given" << std::endl;
    exit(1);
  }

  // Get the arguments
  vector<Symbol *> args = {};

  int v = 0;
  // Check Type of arguments
  for (auto i : t->Children)
  {
    Symbol *s = Value(i.second, false);
    if (s->type == f->nativeArgs[v])
    {
      args.push_back(s);
      v++;
    }
    else
    {
      std::cout << "Compiler Error, type " << to_underlying(f->nativeArgs[v]) << " expected" << std::endl;
      exit(1);
    }
  }
  return args;
}
