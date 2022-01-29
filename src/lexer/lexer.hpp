#include "lexer.h"
#include "../parser/token.hpp"
#include <type_traits>

#pragma once

template <typename E>
constexpr auto to_underlying(E e) noexcept
{
  return static_cast<std::underlying_type_t<E>>(e);
}

inline Token *Lexer::FuncArgs()
{
  Token *args = new Token("FuncArgs", TokenType::FuncArgumentWrapper);

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

inline Token *Lexer::Expression()
{

  if (getType() == ParseTokenType::VarDecl)
  {
  }
  else if (getType() == ParseTokenType::Expression)
  {
    string Expr1 = getVal();
    incPtr();
    if (getType() == ParseTokenType::Semicolon)
    {
      // Standalone Variable
      incPtr();
      return new Token(Expr1, TokenType::Expression);
    }
    else if (getType() == ParseTokenType::OpenBracket)
    {
      // Array
    }
    else if (getType() == ParseTokenType::OpenParenthesis)
    {
      // Call Function
    }
  }
}

inline string Lexer::Expects(ParseTokenType ExpectType, string ExpectStr)
{
  if (getType() == ExpectType)
  {
    return getVal();
  }
  else
  {
    std::cout << "Expected " << ExpectStr << ", Got " << getVal() << std::endl;
    exit(1);
  }
}

inline void Lexer::Function()
{
  Lexed.push_back(new Token(getVal(), TokenType::FuncDeclaration));
  incPtr();

  getLast()->add_child(
      "FuncName",
      new Token(
          Expects(ParseTokenType::Expression, "Expression"),
          TokenType::FuncDeclaration));
  incPtr();

  Expects(ParseTokenType::OpenParenthesis, "Open Parenthesis");
  incPtr();

  getLast()->add_child(
      "FuncArgs",
      FuncArgs());

  incPtr();

  Expects(ParseTokenType::OpenCurlyBracket, "Bracket");
  incPtr();

  int expr = 0;
  while (getType() != ParseTokenType::CloseCurlyBracket)
  {
    expr++;
    getLast()->add_child("" + expr, Expression());
  }
}

inline vector<Token *> Lexer::LexFile()
{
  while (ParsedIndex > ParsedTokens.size())
  {
    incPtr();

    if (getType() == ParseTokenType::FunDeclaration)
    {
      Function();
    }
  }

  return Lexed;
}

inline void Lexer::Args(Token *args)
{
  std::cout << to_underlying(getType()) << std::endl;
  string argType = Expects(ParseTokenType::Expression, "Expression or Close Parenthesis");
  incPtr();
  string argValue = Expects(ParseTokenType::Expression, "Expression");
  incPtr();

  string argName = "Arg" + string(1, args->Children.size() + 1);

  Token *arg = new Token(argName, TokenType::FunctionArgument);
  arg->add_child("Value", new Token(argValue, TokenType::Expression));
  arg->add_child("Type", new Token(argType, TokenType::Expression));

  args->add_child(argName, arg);
}
