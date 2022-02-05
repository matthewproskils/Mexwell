#include <string>
#include <map>

#pragma once

using std::map;
using std::string;

class Symbol
{
public:
  string name;
  int type;
  string value;
  int line;
  int character;
  bool isConstant;

  enum Type
  {
    UNKNOWN,
    FUNCTION,
    VARIABLE,
    CONSTANT,
    ENUM,
    ENUM_VALUE,
    TYPE
  };

  Symbol(string name, Type type, int isConstant, int line, int chr) : name(name), type(type), line(line), isConstant(isConstant), character(chr) {};

private:
};

class Scope
{
public:
  Scope(Scope *parent);
  ~Scope();

  void add_symbol(Symbol *symbol);
  Symbol *get_symbol(string name);
  void print_symbols();
  void print_symbols(string prefix);

private:
  Scope *parent;
  std::map<string, Symbol *> symbols;
};
