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

inline Token *Lexer::Expression()
{
  string Expr1 = getVal();
  incPtr();
  if (getType() == ParseTokenType::Semicolon)
  {
    // Standalone Variable
    return new Token(Expr1, TokenType::Expression, ParsedTokens[ParsedIndex - 2]->lineNumber, ParsedTokens[ParsedIndex - 2]->charNumber);
  }
  else if (getType() == ParseTokenType::OpenBracket)
  {
    // Get Object
  }
  else if (getType() == ParseTokenType::OpenParenthesis)
  {
    // Func Call
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
    incPtr();
    Expects(ParseTokenType::Semicolon, "semicolon");

    return t;
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

  incPtr();

  incPtr();

  int expr = 0;

  Token *v = new Token("", TokenType::Expression, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);
  if (getType() != ParseTokenType::CloseCurlyBracket)
  {
    v->add_child("expr" + std::to_string(expr), Expression());
    incPtr();
    expr++;
    while (getType() != ParseTokenType::CloseCurlyBracket)
    {
      v->add_child("expr" + std::to_string(expr), Expression());
      incPtr();
      expr++;
    }
  }
  t->add_child("expr", v);

  return t;
}

inline vector<Token *> Lexer::LexFile()
{
  while (ParsedIndex < ParsedTokens.size())
  {
    if (getVal() == "fun")
    {
      Lexed.push_back(Function());
    }
    else if (getVal() == "const" || getVal() == "var")
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
  incPtr();
  Expects(ParseTokenType::Semicolon, "Semicolon");

  return t;
}

inline Token *Lexer::Value()
{
  if (getType() == ParseTokenType::Number)
  {

    Token *t = new Token(getVal(), TokenType::Number, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

    return t;
  }
  else if (getType() == ParseTokenType::String)
  {
    Token *t = new Token(getVal(), TokenType::String, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

    return t;
  }
  else if (getVal() == "true" || getVal() == "false")
  {
    Token *t = new Token(getVal(), TokenType::Boolean, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

    return t;
  }
  else if (getType() == ParseTokenType::Expression)
  {
    Token *t = new Token(getVal(), TokenType::Expression, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

    return t;
  }
  else
  {
    std::cout << "Error: Invalid Value: " << getVal() << std::endl;
    exit(1);
  }
}