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

  vector<Token *> LexFile()
  {
    while (ParsedIndex < ParsedTokens.size())
    {
      incPtr();

      if (getType() == ParseTokenType::FunDeclaration)
      {
        Function();
      }
    }

    return Lexed;
  }

  void incPtr()
  {
    ParsedIndex++;
    if (ParsedIndex >= ParsedTokens.size())
    {
      std::cout << "Unexpected end of file" << std::endl;
      exit(1);
    }
  }

  void Function()
  {
    Lexed.push_back(new Token(getVal(), TokenType::FuncDeclaration));
    incPtr();

    getLast()->add_child(
        "FuncName",
        Token(
            Expects(ParseTokenType::Expression, "Expression"),
            TokenType::FuncDeclaration));
    incPtr();

    Expects(ParseTokenType::OpenParenthesis, "Open Parenthesis");
    incPtr();

    FuncArgs();

    Expects(ParseTokenType::OpenCurlyBracket, "Bracket");
    incPtr();

    Expression();
  }

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

  string Expects(int ExpectType, string ExpectStr)
  {
    if (getType() == ExpectType)
    {
      return getVal();
    }
    else
    {
      std::cout << "Expected " << ExpectStr << ", Got " << getVal() << std::endl;
      exit(1);
    }
  }

  Token *getLast()
  {
    return Lexed[Lexed.size() - 1];
  }

  Token *FuncArgs()
  {

    while (ParsedIndex < ParsedTokens.size())
    {
      incPtr();

      if (getType() == ParseTokenType::CloseParenthesis)
      {
        break;
      }
    }
  }

  Token *Expression()
  {
    if (getType() == ParseTokenType::VarDecl)
    {
    }
    else if (getType() == ParseTokenType::Expression)
    {
    }
  }
};