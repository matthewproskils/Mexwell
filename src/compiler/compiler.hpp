#include "compiler.h"
#include "scope.hpp"

inline Compiler::Compiler(vector<Token *> tokens)
{
  tokens = tokens;
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
      Variable(tokens[ParsedIndex]);
      exit(1);
    }
    else
    {
      std::cout << "Unexpected Type, " << to_underlying(getType());
      exit(1);
    }
  }
}

inline std::pair<string, Symbol *> Compiler::Variable(Token* t)
{
  bool isConstant = t->value() == "const";
  string varName = getChild(t, "Name")->second->value;
  Symbol *var = Value(getChild(t, "Value")->second);
  std::cout << varName;

  return std::make_pair("", nullptr);
}

inline void Compiler::incPtr()
{
  ParsedIndex;
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

inline std::map<string, Token *>::iterator Compiler::getChild(Token* te, string Child)
{
  auto t = te->Children.find(Child);
  if (t != te->Children.end())
  {
    return t;
  };
  std::cout << "Compiler error, could not get child: " << Child << std::endl;
  exit(1);
}

inline Symbol* Compiler::Value(Token* t) {
  if (t->type == TokenType::Number) {
    
  }
}