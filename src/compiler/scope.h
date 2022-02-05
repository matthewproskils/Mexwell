#include <string>
#include <map>

#pragma once

using std::map;
using std::string;

enum class SymbolType
{
  Number,
  String
};

class Symbol
{
public:
  SymbolType type;
  string value;
  bool isConstant;

  Symbol(string value, SymbolType type, bool isConstant) : value(value), type(type), isConstant(isConstant){};

private:
};

class Scope
{
public:
  Scope(Scope *parent);
  ~Scope();

  void add_symbol(std::pair<string, Symbol *> s);
  void add_symbol(string name, Symbol * s);
  Symbol *get_symbol(string name);
  void print_symbols();
  void print_symbols(string prefix);

private:
  Scope *parent;
  std::map<string, Symbol *> symbols;
};
