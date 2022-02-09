#include "lexer.h"

#pragma once

inline void Lexer::incPtr()
{
  ParsedIndex++;
  if (ParsedIndex >= ParsedTokens.size())
  {
    std::cout << "Unexpected end of file, we expected something here" << std::endl;
    exit(1);
  }
}

inline ParseTokenType Lexer::getType()
{
  if (ParsedIndex >= ParsedTokens.size())
  {
    std::cout << "Unexpected End of File at line " << ParsedTokens[ParsedIndex-1]->lineNumber << ParsedTokens[ParsedIndex-1]->charNumber << std::endl;
  }
  return ParsedTokens[ParsedIndex]->type;
}
inline string Lexer::Expects(ParseTokenType ExpectType, string ExpectStr)
{
  if (getType() == ExpectType)
  {
    return getVal();
  }
  else
  {
    std::cout << "Expected " << ExpectStr << " at line " << ParsedTokens[ParsedIndex]->lineNumber << " char " << ParsedTokens[ParsedIndex]->lineNumber << ", Got " << getVal() << std::endl;
    exit(1);
  }
}