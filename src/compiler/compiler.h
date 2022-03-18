#include "../util/error.hpp"
#include "../lexer/lexer.hpp"
#include "./scope.hpp"

#pragma once

class Compiler
{
private:
  int ParsedIndex;
  string FileName;

public:
  vector<Token *> tokens;

  Scope *global;

  Compiler();

  ~Compiler();

  void compile(Scope *scope, vector<Token *> tokens);

  std::pair<string, Symbol *> Variable(Token *t);

  std::pair<string, Symbol *> Function(Token *t);

  TokenType getType();

  Symbol *Value(Token *t, bool isConstant);

  Scope *funcArgs(Scope *global, Token *t);

  vector<Symbol *> nativeArgs(Scope *global, Token *t);

  Symbol *ExprCall(Token *t, Scope *global);

  void If(Token *t, Scope *global);

  bool ConditionEval(Token *t, Scope *global);
};
