#include <string>
#include <map>

#pragma once

using std::map;
using std::string;

enum class SymbolType
{
  Number,
  String,
  Boolean
};

class Function 
{
  public:
  string name;
  vector<string> args;
  vector<string> code;
  vector<SymbolType> argsType;
};

class Symbol 
{
public:
  string value;
  SymbolType type;
  bool isConstant;
  int lineNumber;
  int charNumber;
  Symbol(string value, SymbolType type, bool isConstant)
  {
    this->value = value;
    this->type = type;
    this->isConstant = isConstant;
  }
};

class Scope 
{
public:
  map<string, Symbol*> symbols;
  vector<Scope*> scopes;
  Scope* parent;
  Scope()
  {
    this->parent = nullptr;
  }
  Scope(Scope* parent)
  {
    this->parent = parent;
  }
  void print_symbols()
  {
    std::cout << "Scope: " << std::endl;
    for (auto s : this->symbols)
    {
      std::cout << "  " << s.first << std::endl;
    }
    for (auto s : this->scopes)
    {
      s->print_symbols();
    }
  }
  void add_symbol(string name, Symbol* symbol)
  {
    this->symbols.insert(make_pair(name, symbol));
  }
  Symbol* get_symbol(string name)
  {
    if (this->symbols.count(name) > 0)
    {
      return this->symbols[name];
    }
    else if (this->parent != nullptr)
    {
      return this->parent->get_symbol(name);
    }
    else
    {
      return nullptr;
    }
  }
};