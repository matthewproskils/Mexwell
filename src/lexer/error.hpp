#include "lexer.h"

#pragma once

inline void Lexer::Error(string Token, string Note)
{
  std::cout << "\n\033[1;33mAt File: " + FileName + " \033[1;31m[Error] \n\033[0;m" + Note + "\nLine " + std::to_string(ParsedTokens[ParsedIndex]->lineNumber) + " char " + std::to_string(ParsedTokens[ParsedIndex]->charNumber) + " \n\033[1;31m[Token:] \033[0m" + Token << std::endl;

  /*
    Ex:
    At File: VM [Error]
    Expected Semicolon or Open Bracket or Open Parenthesis
    Line 3 char 9
    [Token:] ==
  */

  throw;
  // exit(0);
};
