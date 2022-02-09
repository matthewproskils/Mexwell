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
    else if (this->parent != nullptr)
    {
      return this->parent->get_symbol(name);
    }
    else
    {
      std::cout << "Type " << name << " not found" << std::endl;
      exit(1);
    }
  }

  bool hasSymbol(string s)
  {
    if (this->symbols.count(s) > 0)
    {
      return true;
    }
    else if (this->parent != nullptr)
    {
      return this->parent->hasSymbol(s);
    }
    else
    {
      return false;
    }
  }

  SymbolType get_type(string s)
  {
    if (s == "number")
    {
      return SymbolType::Number;
    }
    else if (s == "string")
    {
      return SymbolType::String;
    }
    else if (s == "bool")
    {
      return SymbolType::Boolean;
    }
    else if (s == "Function")
    {
      return SymbolType::Function;
    }
    else if (s == "number")
    {
      return SymbolType::Number;
    }
    else if (s == "void")
    {
      return SymbolType::Void;
    }
    else
    {
      std::cout << "Type " << s << " not found" << std::endl;
      exit(1);
    }
  }

  SymbolType get_type(TokenType t)
  {
    if (t == TokenType::Number)
    {
      return SymbolType::Number;
    }
    else if (t == TokenType::String)
    {
      return SymbolType::String;
    }
    else if (t == TokenType::Boolean)
    {
      return SymbolType::Boolean;
    }
    else if (t == TokenType::Number)
    {
      return SymbolType::Number;
    }
    else if (t == TokenType::Void)
    {
      return SymbolType::Void;
    }
    else
    {
      std::cout << "Error: " << to_underlying(t) << " is not a valid type" << std::endl;
      exit(1);
    };
  }

  string type_string(SymbolType t)
  {
    // type to string
    if (t == SymbolType::Boolean)
    {
      return "bool";
    }
    else if (t == SymbolType::Number)
    {
      return "number";
    }
    else if (t == SymbolType::String)
    {
      return "string";
    }
    else if (t == SymbolType::Function)
    {
      return "Function";
    }
    else
    {
      std::cout << "Error: " << to_underlying(t) << " is not a valid type" << std::endl;
      exit(1);
    };
  }
};