#include "lexer.h"

#pragma once


inline Token *Lexer::Expression()
{
  if (getType() == ParseTokenType::VarDecl)
  {
    return Variable();
  }
  else
  {
    string Expr1 = getVal();
    incPtr();
    if (getType() == ParseTokenType::Semicolon)
    {
    }
    else if (getType() == ParseTokenType::OpenBracket)
    {
      // Get Object
    }
    else if (getType() == ParseTokenType::OpenParenthesis)
    {
      return CallExpr();
    }
    else
    {
      Error(getVal(), "Expected Semicolon or Open Bracket or Open Parenthesis");
    }
  }
}