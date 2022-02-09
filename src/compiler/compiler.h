#include "../lexer/lexer.hpp"
#include "./scope.hpp"

#pragma once

class Compiler
{
public:
  int ParsedIndex;
  
  vector<Token *> tokens;

  Scope* global;

  Compiler();

  ~Compiler();

  void incPtr();

  void compile(Scope* scope, vector<Token*> tokens);

  std::pair<string, Symbol*> Variable(Token* t);

  std::pair<string, Symbol*> Function(Token* t);
  
  TokenType getType();

  string getValue();

  Symbol* Value(Token *t, bool isConstant);

  Scope* funcArgs(Scope* global, Token* t);

  vector<Symbol* > nativeArgs(Scope* global, Token* t);

  Symbol *ExprCall(Token* t, Scope* global);
};

