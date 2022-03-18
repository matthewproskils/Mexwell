#include "lexer.h"

#pragma once

inline Token *Lexer::Variable()
{
  Token *t = new Token(getVal(), TokenType::VariableDef, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);
  incPtr();
  Expects(ParseTokenType::Expression, "Variable Name");
  t->add_child(
      "Name",
      new Token(
          getVal(-1),
          TokenType::Expression,
          ParsedTokens[ParsedIndex]->lineNumber,
          ParsedTokens[ParsedIndex]->charNumber));
  Expects(ParseTokenType::EqualsSign, "EqualsSign");
  t->add_child("Value", Value());
  Expects(ParseTokenType::Semicolon, "Semicolon");

  return t;
}