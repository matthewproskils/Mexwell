#include "../lexer/lexer.hpp"

#pragma once

class Compiler
{
public:
  int ParsedIndex;
  
  vector<Token *> tokens;

  Compiler(vector<Token *> tokens);

  ~Compiler();

  void compile();
};