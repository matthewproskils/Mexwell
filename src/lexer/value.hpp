#include "lexer.h"

#pragma once

inline Token *Lexer::Value()
{
  if (getType() == ParseTokenType::Number)
  {

    Token *t = new Token(getVal(), TokenType::Number, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

    return t;
  }
  else if (getType() == ParseTokenType::String)
  {
    return new Token(getVal(), TokenType::String, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);
  }
  else if (getVal() == "true" || getVal() == "false")
  {
    return new Token(getVal(), TokenType::Boolean, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);
  }
  else if (getVal() == "void") 
  {
    return new Token("void", TokenType::Void, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);
  }
  else if (getType() == ParseTokenType::Expression)
  {
    if (ParsedTokens[ParsedIndex + 1]->type == ParseTokenType::OpenParenthesis)
    {
      incPtr();
      return CallExpr();
    }
    else
    {
      Token *t = new Token(getVal(), TokenType::Expression, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

      return t;
    }
  }
  else
  {
    std::cout << "Error: Invalid Value: " << getVal() << std::endl;
    exit(1);
  }
}

inline string Lexer::getVal()
{
  if (ParsedIndex >= ParsedTokens.size())
  {
    std::cout << "Unexpected End of File";
  }
  return ParsedTokens[ParsedIndex]->value;
}