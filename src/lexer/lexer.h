#include <vector>
#include <string>
#include <map>
#include <iostream>
#include "token.hpp"
#include "../parser/token.hpp"

using std::string, std::vector, std::pair, std::make_pair;

#pragma once

class Lexer
{
private:
  vector<pair<string, int>> ParsedTokens;
  int ParsedIndex;
  vector<Token *> Lexed;

public:
  Lexer(vector<pair<string, int>> tokens)
  {
    ParsedTokens = tokens;
    ParsedIndex = -1;
    Lexed = {};
  }

  vector<Token *> LexFile();

  void incPtr()
  {
    ParsedIndex++;
    if (ParsedIndex >= ParsedTokens.size())
    {
      std::cout << "Unexpected end of file" << std::endl;
      exit(1);
    }
  }

  void Function();

  int getType()
  {
    if (ParsedIndex >= ParsedTokens.size())
    {
      std::cout << "Unexpected End of File";
    }
    return ParsedTokens[ParsedIndex].second;
  }

  string getVal()
  {
    if (ParsedIndex >= ParsedTokens.size())
    {
      std::cout << "Unexpected End of File";
    }
    return ParsedTokens[ParsedIndex].first;
  }

  string Expects(int ExpectType, string ExpectStr);

  Token *getLast()
  {
    return Lexed[Lexed.size() - 1];
  }

  Token *FuncArgs();

  Token *Expression();

  void Args(Token *args)
  {
    string argType = Expects(ParseTokenType::Expression, "Expression or Close Parenthesis");
    incPtr();
    string argValue = Expects(ParseTokenType::Expression, "Expression");
    incPtr();

    string argName = "Arg" + string(1, args->Children.size() + 1);

    Token *arg = new Token(argName, TokenType::FunctionArgument);
    arg->add_child("Value", new Token(argValue, TokenType::Expression));
    arg->add_child("Type", new Token(argType, TokenType::Expression));

    args->add_child(argName, arg);
  }
};