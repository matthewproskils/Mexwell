#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "token.hpp"
#include "../parser/token.hpp"

#pragma once

class Lexer
{
private:
  vector<ParseToken*> ParsedTokens;
  int ParsedIndex;
  vector<Token *> Lexed;

public:
  Lexer(vector<ParseToken*> tokens);

  vector<Token *> LexFile();

  void incPtr();

  Token* Function();

  ParseTokenType getType();

  string getVal();

  string Expects(ParseTokenType ExpectType, string ExpectStr);

  Token *getLast();

  Token *FuncArgs();

  Token *Expression();

  Token *Variable();

  Token *Value();

  Token *CallExpr();

  void Args(Token *args);
};