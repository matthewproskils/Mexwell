#include "lexer.h"

#pragma once

inline void Lexer::Args(Token *args)
{
  string argType = Expects(ParseTokenType::Expression, "Expression or Close Parenthesis");
  incPtr();
  string argValue = Expects(ParseTokenType::Expression, "Expression");
  incPtr();
  string argName = "Arg" + std::to_string(args->Children.size());

  Token *arg = new Token(argName,
                         TokenType::FunctionArgument,
                         ParsedTokens[ParsedIndex - 3]->lineNumber,
                         ParsedTokens[ParsedIndex - 3]->charNumber);
  arg->add_child(
      "Type",
      new Token(argValue,
                TokenType::Expression,
                ParsedTokens[ParsedIndex - 3]->lineNumber,
                ParsedTokens[ParsedIndex - 3]->charNumber));
  arg->add_child(
      "Value",
      new Token(argType, TokenType::Expression, ParsedTokens[ParsedIndex - 3]->lineNumber, ParsedTokens[ParsedIndex - 3]->charNumber));

  args->add_child(argName, arg);
}

inline Token *Lexer::FuncArgs()
{
  Token *args = new Token("FuncArgs", TokenType::FuncArgumentWrapper, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

  while (ParsedIndex < ParsedTokens.size())
  {
    if (getType() == ParseTokenType::CloseParenthesis)
    {
      break;
    }
    else
    {
      Args(args);
    }
  }

  return args;
}