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
  string FileName;

  Lexer(vector<ParseToken*> tokens, string File_Name = "VM");

  vector<Token *> LexFile();

  void incPtr();

  Token* Function();

  ParseTokenType getType();

  string getVal(int i = 0);

  void Expects(ParseTokenType ExpectType, string ExpectStr);

  Token *getLast();

  Token *FuncArgs();

  Token *Expression();

  Token *Variable();

  Token *Value();

  Token *CallExpr();

  void Args(Token *args);

  void Error(string Token, string Note);

  Token *Lex();

  Token *If();

  Token *ConditionValue();

  Token *FunctionBody();

  Token *GetCondition();
};