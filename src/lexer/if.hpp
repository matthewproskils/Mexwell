#include "lexer.h"
#include "../util/debugTokens.hpp"
#include "./function.hpp"

#pragma once

inline Token *Lexer::ConditionValue()
{
  Token *t = new Token("Comparison", TokenType::ConditionValue, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);
  t->add_child("Left", Value());
  if (getType() != ParseTokenType::CloseParenthesis)
  {
    t->add_child("Comparison", new Token(getVal(), TokenType::Compare, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber));
    incPtr();
    t->add_child("Right", Value());
    return t;
  }
  else
  {
    t->add_child("Right", new Token("true", TokenType::Boolean, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber));
    t->add_child("Comparison", new Token("==", TokenType::Compare, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber));
    return t;
  }
}

inline Token *Lexer::GetCondition()
{
  Token *condition = new Token("ConditionWrapper", TokenType::ConditionValue, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

  // If t ype is not 'if', you don't need to do a comparison
  /*
  Ex:
  if (a == b)
  {
    // do stuff
  }
  else  <-- Do not need to check for the '(a == b)'
  {
    // do other stuff
  }
  */

  if (getType() != ParseTokenType::Else)
  {
    Expects(ParseTokenType::OpenParenthesis, "Open Parenthesis");

    int i = 0;
    while (getType() != ParseTokenType::CloseParenthesis)
    {
      i++;
      condition->add_child(
          "Condition" + std::to_string(i),
          ConditionValue());
    }

    Expects(ParseTokenType::CloseParenthesis, "Closing Parenthesis");
    Expects(ParseTokenType::OpenCurlyBracket, "Open Curly Bracket");

    // 'If' statement body
    if (getType() != ParseTokenType::CloseCurlyBracket)
    {
      // If there is nothing in the statement body, don't add the condition
      condition->add_child("Body", FunctionBody());
    }

    return condition;
  }
  else
  {
    Expects(ParseTokenType::Else, "Else");
    // 'Else' statement body
    Expects(ParseTokenType::OpenCurlyBracket, "Open Curly Bracket");

    if (getType() != ParseTokenType::CloseCurlyBracket)
    {
      // If there is nothing in the statement body, don't add the condition
      condition->add_child("Body", FunctionBody());
    }

    return condition;
  }
}

inline Token *Lexer::If()
{
  Token *t = new Token("if", TokenType::IfWrap, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);

  Expects(ParseTokenType::If, "If");
  t->add_child("If", GetCondition());

  int i = 0;
  // Elif Statement - TODO
  Token *elif = new Token("ElseIfWrapper", TokenType::IfWrap, ParsedTokens[ParsedIndex]->lineNumber, ParsedTokens[ParsedIndex]->charNumber);
  while (getType() == ParseTokenType::ElseIf)
  {
    incPtr();
    elif->add_child("ElseIf" + std::to_string(i), GetCondition());
    i++;
  }
  t->add_child("ElseIf", elif);
  // 'Else' statement body
  if (getType() == ParseTokenType::Else)
  {
    t->add_child("Else", GetCondition());
  }

  return t;
}