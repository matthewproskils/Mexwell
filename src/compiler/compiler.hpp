#include "compiler.h"
#include "scope.hpp"
#include <map>

inline Compiler::Compiler(vector<Token *> tokens)
{
  this->tokens = tokens;
}

inline void Compiler::compile()
{
  Scope *global = new Scope(nullptr);
  Scope *current = global;

  ParsedIndex = 0;

  while (ParsedIndex < tokens.size())
  {
    if (getType() == TokenType::VariableDef)
    {
      global->add_symbol(Variable(tokens[ParsedIndex]));
    }
    else if (getType() == TokenType::FuncDeclaration)
    {
      global->add_symbol(Function(tokens[ParsedIndex]));
    }
    else
    {
      std::cout << "Unexpected Type, " << to_underlying(getType()) << std::endl;
      exit(1);
    }
    ParsedIndex++;
  }
  global->print_symbols();
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
  }
}

inline std::pair<string, Symbol *> Compiler::Function(Token *t)
{
  std::map<string, string> args = {};

  for (std::pair<string, Token*> a : t->get_child("FuncArgs")->Children) {
    std::cout << a.first << std::endl;
    args.insert(make_pair(a.second->get_child("Type")->value, a.second->get_child("Value")->value));
  }

  std::vector<Token *> code = {};

  for (std::pair<string, Token*> a : t->get_child("expr")->Children) {
    code.push_back(a.second);
  }

  SymbolFunction* f = new SymbolFunction(t->get_child("FuncName")->value, args, code);

  Symbol *s = new Symbol(f);
  
  return std::pair<string, Symbol*>(t->get_child("FuncName")->value, s);
}