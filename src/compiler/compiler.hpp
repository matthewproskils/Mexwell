#include "compiler.h"
#include "scope.hpp"
#include <map>

#pragma once

inline Compiler::Compiler()
{
}

inline void Compiler::compile(Scope *global, vector<Token *> t)
{
  this->ParsedIndex = 0;
  this->tokens = t;

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
      if (global->get_symbol(getValue())->Func->isNative)
      {
        vector<Symbol *> args = nativeArgs(global, t[ParsedIndex]);
        global->get_symbol(getValue())->Func->nativeFunc(args);
      }
      else
      {
        Scope *funcScope = funcArgs(global, t[ParsedIndex]);
        Compiler *funCompiler = new Compiler();
        funCompiler->compile(funcScope, global->get_symbol(getValue())->Func->code);
      }
    }
    else
    {
      std::cout << "Unexpected Type, " << to_underlying(getType()) << std::endl;
      exit(1);
    }
    ParsedIndex++;
  }
}

inline std::pair<string, Symbol *> Compiler::Variable(Token *t)
{
  bool isConstant = (t->value == "const");
  string varName = getChild(t, "Name")->second->value;
  Symbol *var = Value(getChild(t, "Value")->second, isConstant);

  return std::make_pair(varName, var);
}

inline void Compiler::incPtr()
{
  if (ParsedIndex > tokens.size())
  {
    std::cout << "Compiler Error, Unexpected End Of File" << std::endl;
    exit(1);
  }
}

inline TokenType Compiler::getType()
{
  return tokens[ParsedIndex]->type;
}

inline string Compiler::getValue()
{
  return tokens[ParsedIndex]->value;
}

inline std::map<string, Token *>::iterator Compiler::getChild(Token *te, string Child)
{
  auto t = te->Children.find(Child);
  if (t != te->Children.end())
  {
    return t;
  };
  std::cout << "Compiler error, could not get child: " << Child << std::endl;
  exit(1);
}

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
  else
  {
    std::cout << "Invalid Type?" << std::endl;
    exit(1);
  }
}

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

  SymbolFunction *f = new SymbolFunction(t->get_child("FuncName")->value, args, code);

  Symbol *s = new Symbol(f);

  return std::pair<string, Symbol *>(t->get_child("FuncName")->value, s);
}

inline Scope *Compiler::funcArgs(Scope *scope, Token *t)
{

  // Get the function
  SymbolFunction *f = scope->get_symbol(t->value)->Func;

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
    if (t->get_child("arg" + std::to_string(j))->type == TokenType::Expression)
    {
      string symbolName = t->get_child("arg" + std::to_string(j))->value;
      if (!scope->hasSymbol(symbolName))
      {
        std::cout << "Compiler Error, " << symbolName << " is not defined" << std::endl;
        exit(1);
      }
      if (scope->get_symbol(symbolName)->type == scope->get_type(i.second))
      {
        funcScope->add_symbol(i.first, scope->get_symbol(symbolName));
      }
      else
      {
        std::cout << "Compiler Error, type " << i.second << " expected" << std::endl;
        exit(1);
      }
    }
    else if (scope->get_type(i.second) == scope->get_type(t->get_child("arg" + std::to_string(j))->type))
    {
      // Add the argument to the scope
      funcScope->add_symbol(i.first, new Symbol(t->get_child("arg" + std::to_string(j))->value, scope->get_type(i.second), false));
      j++;
    }
    else
    {
      std::cout << "Compiler Error, type " << i.second << " expected" << std::endl;
      exit(1);
    }
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
  for (auto i : t->Children) {
    if (i.second->type == TokenType::Expression) {
      if (!global->hasSymbol(i.second->value)) {
        std::cout << "Compiler Error, " << i.second->value << " is not defined" << std::endl;
        exit(1);
      } else if (global->get_symbol(i.second->value)->type == f->nativeArgs[v]) {
        args.push_back(global->get_symbol(i.second->value));
      } else {
        std::cout << "Compiler Error, type " << global->type_string(f->nativeArgs[v]) << " expected at line " << i.second->lineNumber << " char " << i.second->charNumber << std::endl;
        exit(1);
      }
    }
    else if (global->get_type(i.second->type) == f->nativeArgs[v])
    {
      args.push_back(new Symbol(i.second->value, f->nativeArgs[v], false));
      v++;
    }
  }

  return args;
}