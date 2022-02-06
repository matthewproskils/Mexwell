#include <string>
#include <map>

#pragma once

using std::map;
using std::string;

std::string repeatTab(int i)
{
  string s = "";
  for (int j = 0; j < i; j++)
  {
    s += "\t";
  }
  return s;
}

void debugTokens(Token *t, int tab = 0)
{
  std::cout << repeatTab(tab) << "Value: " << t->value << "\n"
            << repeatTab(tab) << "Type: " << to_underlying(t->type) << std::endl;
  map<std::string, Token *>::iterator it;
  for (it = t->Children.begin(); it != t->Children.end(); it++)
  {
    std::cout << repeatTab(tab + 1) << it->first << ":" << std::endl;
    debugTokens(it->second, tab + 2);
  }
}

enum class SymbolType
{
  Number,
  String,
  Boolean,
  Function
};

class SymbolFunction
{
public:
  string name;
  map<string, string> args;
  vector<Token*> code;

  SymbolFunction(string name, map<string, string> args, vector<Token*> code) : name(name), args(args), code(code) {};
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
    this->value = "Function ( " + f->name + " )";
    this->type = SymbolType::Function;
  }
};

class Scope
{
public:
  map<string, Symbol *> symbols;
  vector<Scope *> scopes;
  Scope *parent;
  Scope()
  {
    this->parent = nullptr;
  }
  Scope(Scope *parent)
  {
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