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

#pragma once

inline vector<Token *> Lexer::LexFile()
{
  while (ParsedIndex < ParsedTokens.size())
  {
    if (getType() == ParseTokenType::FunDeclaration)
    {
      Lexed.push_back(Function());
    }
    else if (getType() == ParseTokenType::VarDecl)
    {
      Lexed.push_back(Variable());
    }
    else if (getType() == ParseTokenType::Semicolon)
    {
    }
    else if (getType() == ParseTokenType::Expression)
    {
      Lexed.push_back(Expression());
    }
    else
    {
      std::cout << "Error: Unexpected Token " << getVal() << ", type: " << to_underlying(getType()) << std::endl;
      exit(1);
    }
    ParsedIndex++;
  }

  return Lexed;
}

inline Token *Lexer::CallExpr()
{
  ParsedIndex--;
  string Expr1 = getVal();
  incPtr();

  incPtr();
  Token *t = new Token(Expr1, TokenType::ExpressionCall, ParsedTokens[ParsedIndex - 2]->lineNumber, ParsedTokens[ParsedIndex - 2]->charNumber);

  if (getType() != ParseTokenType::CloseParenthesis)
  {
    t->add_child("arg" + std::to_string(t->Children.size()), Value());
    incPtr();

    while (getType() != ParseTokenType::CloseParenthesis)
    {
      Expects(ParseTokenType::Comma, "Comma");
      t->add_child("arg" + std::to_string(t->Children.size()), Value());
      incPtr();
    }
  }

  Expects(ParseTokenType::CloseParenthesis, "Close Parenthesis");

  return t;
}


inline Lexer::Lexer(vector<ParseToken*> tokens)
{
  ParsedTokens = tokens;
  ParsedIndex = 0;
  Lexed = {};
}

