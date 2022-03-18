#include "lexer.h"
#include "../parser/token.hpp"
#include "../util/toUnderlying.hpp"

#include "expression.hpp"
#include "function.hpp"
#include "functionArgs.hpp"
#include "util.hpp"
#include "variable.hpp"
#include "value.hpp"
#include "variable.hpp"
#include "if.hpp"
#include "error.hpp"

#pragma once

inline vector<Token *> Lexer::LexFile()
{

  vector<Token *> Lexed = {};
  while (ParsedIndex < ParsedTokens.size())
  {
    if (getType() == ParseTokenType::FunDeclaration)
    {
      Lexed.push_back(Function());
    } else {
      Error(getVal(), "Unexpected Token, expected 'function declaration'");
    }
    ParsedIndex++;
  }

  return Lexed;
}

inline Token *Lexer::Lex()
{
  if (getType() == ParseTokenType::FunDeclaration)
  {
    return Function();
  }
  else if (getType() == ParseTokenType::VarDecl)
  {
    return Variable();
  }
  else if (getType() == ParseTokenType::Semicolon)
  {
    incPtr();
  }
  else if (getType() == ParseTokenType::Expression)
  {
    return Expression();
  }
  else if (getType() == ParseTokenType::If)
  {
    return If();
  }
  else
  {
    Error(getVal(), "Unexpected Token, expected 'if', 'expression', 'semicolon', 'variable declaration', or 'function declaration'");
  }
}
inline Token *Lexer::CallExpr()
{
  string Expr1 = getVal(-1);

  incPtr();
  Token *t = new Token(Expr1, TokenType::ExpressionCall, ParsedTokens[ParsedIndex - 2]->lineNumber, ParsedTokens[ParsedIndex - 2]->charNumber);

  if (getType() != ParseTokenType::CloseParenthesis)
  {
    t->add_child("arg" + std::to_string(t->Children.size()), Value());

    while (getType() != ParseTokenType::CloseParenthesis)
    {
      Expects(ParseTokenType::Comma, "Comma");
      t->add_child("arg" + std::to_string(t->Children.size()), Value());
    }
  }

  Expects(ParseTokenType::CloseParenthesis, "Close Parenthesis");
  return t;
}

inline Lexer::Lexer(vector<ParseToken *> tokens, string File_Name)
{
  FileName = File_Name;

  ParsedTokens = tokens;
  ParsedIndex = 0;
}
