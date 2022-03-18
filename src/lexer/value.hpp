#include "lexer.h"

#pragma once

inline Token *Lexer::Value()
{
  if (getType() == ParseTokenType::Number)
  {
    Token *t = new Token(getVal(), TokenType::Number, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

    incPtr();

    return t;
  }
  else if (getType() == ParseTokenType::String)
  {
    Token *t = new Token(getVal(), TokenType::String, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

    incPtr();

    return t;
  }
  else if (getVal() == "true" || getVal() == "false")
  {
    Token *t = new Token(getVal(), TokenType::Boolean, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

    incPtr();

    return t;
  }
  else if (getVal() == "void")
  {
    incPtr();
    return new Token("void", TokenType::Void, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);
  }
  else if (getType() == ParseTokenType::Expression)
  {
    if (getVal(1) == "(")
    {
      incPtr();
      return CallExpr();
    }
    else
    {
      Token *t = new Token(getVal(), TokenType::Expression, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

      incPtr();

      return t;
    }
  }
  else
  {
    Error("", "Invalid Value " + getVal());
  }
}

inline string Lexer::getVal(int i)
{
  if (ParsedIndex+i >= ParsedTokens.size())
  {
    ParsedIndex--;
    Error("", "Unexpected End of File");
  }
  return ParsedTokens[ParsedIndex+i]->value;
}