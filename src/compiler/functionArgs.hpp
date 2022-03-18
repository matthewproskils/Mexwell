#include "compiler.h"

#pragma once

inline Scope *Compiler::funcArgs(Scope *scope, Token *t)
{

  // Get the function
  Symbol *v = scope->get_symbol(t);

  if (v->Func == nullptr)
  {
    Error(t, "Function " + t->value + " does not exist", FileName);
  }

  SymbolFunction *f = v->Func;

  // Set Function Scope
  Scope *funcScope = new Scope(scope, FileName);

  // Check if it is function
  if (f == nullptr)
  {
    Error(t, "Variable " + t->value + " is not a function", FileName);
  }

  // Check if the number of arguments is correct
  if (f->args.size() != t->Children.size())
  {
    Error(t, "Function " + t->value + " expects " + std::to_string(f->args.size()) + " arguments, got " + std::to_string(t->Children.size()), FileName);
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
  SymbolFunction *f = global->get_symbol(t)->Func;

  // Check if argument size is correct
  if (f->nativeArgs.size() != t->Children.size() && !f->infArgs)
  {
    Error(t, "Function " + t->value + " expects " + std::to_string(f->nativeArgs.size()) + " arguments, got " + std::to_string(t->Children.size()), FileName);
  }

  // Get the arguments
  vector<Symbol *> args = {};

  int v = 0;
  // Check Type of arguments
  if (f->infArgs)
  {
    for (auto i : t->Children)
    {
      Symbol *s = Value(i.second, false);
      if (s->type == f->nativeArgs[0])
      {
        args.push_back(s);
        v++;
      }
      else
      {
        Error(t, "Argument " + std::to_string(v) + " is not of type " + std::to_string(to_underlying(f->nativeArgs[v])), FileName);
      }
    }
  }
  else
  {
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
        Error(t, "Argument " + std::to_string(v) + " is not of type " + std::to_string(to_underlying(f->nativeArgs[v])), FileName);
      }
    }
  }
  return args;
}
