#include <string>
#include <map>

#include "../util/debugTokens.hpp"
#include "../util/toUnderlying.hpp"

#pragma once

using std::map;
using std::string;

enum class SymbolType
{
  Number,
  String,
  Boolean,
  Function,
  Void
};

class Symbol;

class SymbolFunction
{
public:
  string name;
  map<string, string> args;
  vector<Token *> code;
  Token *returnExpr;
  SymbolType returnType;

  vector<SymbolType> nativeArgs;
  bool isNative = false;
  bool infArgs = true;
  Symbol *(*nativeFunc)(vector<Symbol *>);

  SymbolFunction(string name, map<string, string> args, SymbolType ReturnType, vector<Token *> code) : name(name), args(args), code(code), returnType(ReturnType){};

  // Native function Set number of rags
  SymbolFunction(string name, vector<SymbolType> args, SymbolType ReturnType, Symbol *(*fun)(std::vector<Symbol *>)) : name(name), nativeFunc(fun), nativeArgs(args), returnType(ReturnType)
  {
    isNative = true;
  };

  // set infinite args
  void setInfArgs()
  {
    infArgs = true;
  };
};

class Symbol
{
public:
  string value;
  SymbolType type;
  bool isConstant;
  bool isFunction = false;
  SymbolFunction *Func;

  Symbol(string value, SymbolType type, bool isConstant)
  {
    this->value = value;
    this->type = type;
    this->isConstant = isConstant;
  }
  // Function
  Symbol(SymbolFunction *f)
  {
    isFunction = true;
    Func = f;
    if (!f->isNative)
    {
      this->value = "Function ( " + f->name + " )";
      this->type = SymbolType::Function;
    }
    else
    {
      this->value = "Native Function ( " + f->name + " )";
      this->type = SymbolType::Function;
    }
  }
};

class Scope
{
public:
  map<string, Symbol *> symbols;
  vector<Scope *> scopes;
  Scope *parent;
  string FileName;

  Scope()
  {
    this->parent = nullptr;
  }
  Scope(Scope *parent, string Filename)
  {
    this->FileName = Filename;
    this->parent = parent;
  }
  void print_symbols()
  {
    std::cout << "Scope: " << std::endl;
    for (auto s : this->symbols)
    {
      std::cout << s.first << ": " << s.second->value << "\nData:\n\tIsConstant: " << s.second->isConstant << "\n\tIsFunction: " << s.second->isFunction << "\n\tType: " << to_underlying(s.second->type) << std::endl;
      if (s.second->isFunction)
      {
        if (!s.second->Func->isNative)
        {
          std::cout << "\tArgs: " << std::endl;
          for (auto a : s.second->Func->args)
          {
            std::cout << "\t\t" << a.first << ": " << a.second << " " << std::endl;
          }
          std::cout << "\tCode: " << std::endl;
          for (auto a : s.second->Func->code)
          {
            debugTokens(a, 1);
          }
          std::cout << "\tReturnType: " << to_underlying(s.second->Func->returnType) << std::endl;
        }
        else
        {
          std::cout << "\tArgs: " << s.second->Func->nativeArgs.size() << std::endl;
        }
      }
    }
    for (auto s : this->scopes)
    {
      s->print_symbols();
    }
  }
  void add_symbol(std::pair<string, Symbol *> symbol)
  {
    this->symbols.insert(symbol);
  }
  void add_symbol(string name, Symbol *symbol)
  {
    this->symbols.insert(make_pair(name, symbol));
  }
  Symbol *get_symbol(string name)
  {
    if (this->symbols.count(name) > 0)
    {
      return this->symbols[name];
    }
    if (this->parent != nullptr)
    {
      return this->parent->get_symbol(name);
    }

    Error(name, "Symbol not found: " + name, FileName);
  }

  Symbol *get_symbol(Token *t)
  {
    if (this->symbols.count(t->value) > 0)
    {
      return this->symbols[t->value];
    }

    if (this->parent != nullptr)
    {
      return this->parent->get_symbol(t->value);
    }
    Error(t, "Variable " + t->value + " not found", FileName);
  }

  bool hasSymbol(string s)
  {
    if (this->symbols.count(s) > 0)
    {
      return true;
    }
    if (this->parent != nullptr)
    {
      return this->parent->hasSymbol(s);
    }
    return false;
  }

  SymbolType get_type(Token *s)
  {
    if (s->value == "number")
    {
      return SymbolType::Number;
    }
    
    if (s->value == "string")
    {
      return SymbolType::String;
    }
    
    if (s->value == "bool")
    {
      return SymbolType::Boolean;
    }

    if (s->value == "Function")
    {
      return SymbolType::Function;
    }
    
    if (s->value == "number")
    {
      return SymbolType::Number;
    }
    
    if (s->value == "void")
    {
      return SymbolType::Void;
    }
  }
};