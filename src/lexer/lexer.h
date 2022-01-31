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
  vector<pair<string, ParseTokenType>> ParsedTokens;
  int ParsedIndex;
  vector<Token *> Lexed;

public:
  Lexer(vector<pair<string, ParseTokenType>> tokens)
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

  Token* Function();

  ParseTokenType getType()
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

  string Expects(ParseTokenType ExpectType, string ExpectStr);

  Token *getLast()
  {
    return Lexed[Lexed.size() - 1];
  }

  Token *FuncArgs();

  Token *Expression();

  Token *Variable();

  Token *Value();
  
  void Args(Token *args);
};