#pragma once

enum ParseTokenType
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
  FunDeclaration
};