#include <string>
#include <map>
#include <iostream>

using std::string;
using std::map;

#pragma once

enum class TokenType
{
  // SymbolFunction
  FuncDeclaration,
  FuncArgumentWrapper,
  FunctionArgument,

  //Expression
  Expression,
  SingleExpression,
  ExpressionCall,

  //Variable
  VariableDef,
  VarType, //Var, Let, or Const

  //Types
  Number,
  String,
  Boolean,
  Void,

  //If Statement
  IfWrap,
  If,
  Else,
  ConditionValue,
  Compare
};

class Token {
public:
  TokenType type;
  string value;
  int lineNumber;
  int charNumber;
  map<string, Token*> Children = {};

  Token(string Value, TokenType Type, int LineNumber, int CharNumber) : value(Value), lineNumber(LineNumber), charNumber(CharNumber), type(Type) {}

  void add_child(string name, Token* token) {
    Children.insert(std::pair<string, Token*>(name, token));
  }

  Token* get_child(string name) {
    auto it = Children.find(name);
    if (it == Children.end()) {
      std::cout << "Error: Cannot find child " << name << std::endl;
      exit(1);
    } else {
      return it->second;
    }
  }
};