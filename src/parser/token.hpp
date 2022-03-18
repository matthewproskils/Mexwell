#pragma once

enum class ParseTokenType
{
  VarDecl,  // 0
  String, // 1
  Expression, // 2
  OpenCurlyBracket, // 3
  CloseCurlyBracket, //  4
  OpenBracket, // 5
  CloseBracket, // 6
  OpenParenthesis, // 7
  CloseParenthesis, // 8
  Semicolon, // 9
  FunDeclaration, // 10
  EqualsSign, // 11
  Number, // 12
  Comma, // 13
  If, // 14
  Else, // 15
  Comparison, // 16
  ElseIf, // 17
};

class ParseToken
{
public:
  ParseTokenType type;
  string value;
  int lineNumber;
  int charNumber;

  ParseToken(ParseTokenType type, string value, int lineNumber, int charNumber) : type(type), value(value), lineNumber(lineNumber), charNumber(charNumber) {}
};