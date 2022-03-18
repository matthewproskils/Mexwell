#include "lexer.h"

#pragma once

inline void Lexer::incPtr()
{
  ParsedIndex++;
  if (ParsedIndex > ParsedTokens.size()+1)
  {
    ParsedIndex--;
    Error("", "Unexpected end of file, we expected something here");
  }
}

inline ParseTokenType Lexer::getType()
{
  if (ParsedIndex > ParsedTokens.size()+1)
  {
    ParsedIndex--;
    Error("", "Unexpected end of file, we expected something here");
  }
  return ParsedTokens[ParsedIndex]->type;
}

inline void Lexer::Expects(ParseTokenType ExpectType, string ExpectStr)
{
  if (getType() == ExpectType)
  {
    incPtr();
  }
  else
  {
    Error(getVal(), " Expected " + ExpectStr + " but got " + getVal());
  }
}