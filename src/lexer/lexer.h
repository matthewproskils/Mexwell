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
  vector<ParseToken*> ParsedTokens;
  int ParsedIndex;
  vector<Token *> Lexed;

public:
  Lexer(vector<ParseToken*> tokens)
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
      std::cout << "Unexpected End of File at line " << ParsedTokens[ParsedIndex-1]->lineNumber << ParsedTokens[ParsedIndex-1]->charNumber << std::endl;
    }
    return ParsedTokens[ParsedIndex]->type;
  }

  string getVal()
  {
    if (ParsedIndex >= ParsedTokens.size())
    {
      std::cout << "Unexpected End of File";
    }
    return ParsedTokens[ParsedIndex]->value;
  }

  string Expects(ParseTokenType ExpectType, string ExpectStr);

  Token *getLast()
  {
    if (Lexed.size() == 0)
    {
      std::cout << "Huh" << std::endl;
      exit(1);
    }
    return Lexed[Lexed.size() - 1];
  }

  Token *FuncArgs();

  Token *Expression();

  Token *Variable();

  Token *Value();
  
  void Args(Token *args);
};