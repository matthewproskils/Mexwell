#include "lexer.h"
#include "../util/debugTokens.hpp"

#pragma once

inline Token *Lexer::FunctionBody()
{
  Token *v = new Token("", TokenType::Expression, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

  int expr = 0;
  // Expr = Count of expressions
  while (getType() != ParseTokenType::CloseCurlyBracket)
  {
    Token *t = Lex();
    if (t != nullptr)
    {
      v->add_child("expr" + std::to_string(expr), t);
      expr++;
    }
  }

  Expects(ParseTokenType::CloseCurlyBracket, "Close Curly Bracket");

  return v;
}
inline Token *Lexer::Function()
{
  Token *t = new Token(
      getVal(),
      TokenType::FuncDeclaration,
      ParsedTokens[ParsedIndex]->lineNumber,
      ParsedTokens[ParsedIndex]->charNumber);
  incPtr();

  Expects(ParseTokenType::Expression, "Expression");

  t->add_child(
      "FuncName",
      new Token(
          ParsedTokens[ParsedIndex - 1]->value,
          TokenType::FuncDeclaration,
          ParsedTokens[ParsedIndex - 1]->lineNumber,
          ParsedTokens[ParsedIndex - 1]->charNumber));

  Expects(ParseTokenType::OpenParenthesis, "Open Parenthesis");

  t->add_child(
      "FuncArgs",
      FuncArgs());

  Expects(ParseTokenType::CloseParenthesis, "Close Parenthesis");

  t->add_child(
      "ReturnType",
      Value());

  Expects(ParseTokenType::OpenCurlyBracket, "Open Curly Bracket");

  t->add_child("expr", FunctionBody());

  return t;
}