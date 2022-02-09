#include "lexer.h"

#pragma once

inline Token *Lexer::Function()
{
  Token *t = new Token(
      getVal(),
      TokenType::FuncDeclaration,
      ParsedTokens[ParsedIndex]->lineNumber,
      ParsedTokens[ParsedIndex]->charNumber);
  incPtr();

  t->add_child(
      "FuncName",
      new Token(
          Expects(ParseTokenType::Expression, "Expression"),
          TokenType::FuncDeclaration,
          ParsedTokens[ParsedIndex]->lineNumber,
          ParsedTokens[ParsedIndex]->charNumber));
  incPtr();

  Expects(ParseTokenType::OpenParenthesis, "Open Parenthesis");
  incPtr();

  t->add_child(
      "FuncArgs",
      FuncArgs());

  Expects(ParseTokenType::CloseParenthesis, "Close Parenthesis");
  incPtr();

  t->add_child(
      "ReturnType",
      Value());

  incPtr();

  int expr = 0;

  Token *v = new Token("", TokenType::Expression, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

  incPtr();
  if (getType() != ParseTokenType::CloseCurlyBracket)
  {
    v->add_child("expr" + std::to_string(expr), Expression());
    incPtr();
    Expects(ParseTokenType::Semicolon, "semicolon");
    incPtr();
    expr++;
    while (getType() != ParseTokenType::CloseCurlyBracket)
    {
      v->add_child("expr" + std::to_string(expr), Expression());
      incPtr();
      Expects(ParseTokenType::Semicolon, "semicolon");
      incPtr();
      expr++;
    }
  }

  t->add_child("expr", v);

  return t;
}