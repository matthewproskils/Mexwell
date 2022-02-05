#include "../lexer/lexer.hpp"
#include "./scope.hpp"

#pragma once

class Compiler
{
public:
  int ParsedIndex;
  
  vector<Token *> tokens;

  Compiler(vector<Token *> tokens);

  ~Compiler();

  void incPtr();

  void compile();

  std::pair<string, Symbol*> Variable(Token* t);
  
  TokenType getType();

  string getValue();

  Symbol* Value(Token *t);

  std::map<string, Token*>::iterator getChild(Token* te, string Child);
};