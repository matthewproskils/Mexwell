#include "compiler.h"

#pragma once

inline bool Compiler::ConditionEval(Token *t, Scope *global)
{
  for (int i = 1; i < t->Children.size(); i++)
  {
    Token *Condition = t->get_child("Condition" + std::to_string(i));
    if (Condition->get_child("Comparison")->value == "==")
    {
      return Value(Condition->get_child("Left"), false)->value == Value(Condition->get_child("Right"), false)->value;
    }

    if (Condition->get_child("Comparison")->value == "!=")
    {
      return Value(Condition->get_child("Left"), false)->value != Value(Condition->get_child("Right"), false)->value;
    }

    if (Condition->get_child("Comparison")->value == ">")
    {
      return Value(Condition->get_child("Left"), false)->value > Value(Condition->get_child("Right"), false)->value;
    }

    if (Condition->get_child("Comparison")->value == "<")
    {
      return Value(Condition->get_child("Left"), false)->value < Value(Condition->get_child("Right"), false)->value;
    }

    if (Condition->get_child("Comparison")->value == ">=")
    {
      return Value(Condition->get_child("Left"), false)->value >= Value(Condition->get_child("Right"), false)->value;
    }

    if (Condition->get_child("Comparison")->value == "<=")
    {
      return Value(Condition->get_child("Comparison"), false)->value <= Value(Condition->get_child("Comparison"), false)->value;
    }
  }
  exit(0);
}

inline void Compiler::If(Token *t, Scope *s)
{
  Compiler *IfCompiler = new Compiler();
  if (ConditionEval(t->get_child("If"), s))
  {
    vector<Token *> body = {};
    for (int i = 0; i < t->get_child("If")->get_child("Body")->Children.size(); i++)
    {
      body.push_back(t->get_child("If")->get_child("Body")->get_child("expr" + std::to_string(i)));
    }
    IfCompiler->compile(s, body);
    return;
  }

  for (int i = 0; i < t->get_child("ElseIf")->Children.size(); i++)
  {
    if (ConditionEval(t->get_child("ElseIf")->get_child("ElseIf" + std::to_string(i)), s))
    {
      vector<Token *> body = {};
      for (int j = 0; j < t->get_child("ElseIf")->get_child("ElseIf" + std::to_string(i))->get_child("Body")->Children.size(); j++)
      {
        body.push_back(t->get_child("ElseIf")->get_child("ElseIf" + std::to_string(i))->get_child("Body")->get_child("expr" + std::to_string(j)));
      }
      IfCompiler->compile(s, body);
      return;
    }
  }

  if (t->get_child("Else") != nullptr)
  {
    vector<Token *> body = {};
    for (int i = 0; i < t->get_child("Else")->get_child("Body")->Children.size(); i++)
    {
      body.push_back(t->get_child("Else")->get_child("Body")->get_child("expr" + std::to_string(i)));
    }
    IfCompiler->compile(s, body);
    return;
  }

  return;
}
