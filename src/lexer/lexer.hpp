#include "lexer.h"
#include "../parser/token.hpp"

#pragma once

inline Token *Lexer::FuncArgs()
{
  Token *args = new Token("FuncArgs", TokenType::FuncArgumentWrapper);

  while (ParsedIndex < ParsedTokens.size())
  {
    incPtr();

    if (getType() == ParseTokenType::CloseParenthesis)
    {
      incPtr();
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
      return new Token("Expression", new Token(Expr1, TokenType::SingleExpression));
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

  FuncArgs();

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
  while (ParsedIndex < ParsedTokens.size())
  {
    incPtr();

    if (getType() == ParseTokenType::FunDeclaration)
    {
      Function();
    }
  }

  return Lexed;
}
