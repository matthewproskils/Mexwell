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
          getVal(),
          TokenType::Expression,
          ParsedTokens[ParsedIndex]->lineNumber,
          ParsedTokens[ParsedIndex]->charNumber));

  incPtr();
  Expects(ParseTokenType::EqualsSign, "EqualsSign");
  incPtr();
  t->add_child("Value", Value());

  return t;
}