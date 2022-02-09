#include "../lexer/token.hpp"
#include "toUnderlying.hpp"

#pragma once

std::string repeatTab(int i)
{
  string s = "";
  for (int j = 0; j < i; j++)
  {
    s += "\t";
  }
  return s;
}

void debugTokens(Token *t, int tab = 0)
{
  std::cout << repeatTab(tab) << "Value: " << t->value << "\n"
            << repeatTab(tab) << "Type: " << to_underlying(t->type) << std::endl;
  map<std::string, Token *>::iterator it;
  for (it = t->Children.begin(); it != t->Children.end(); it++)
  {
    std::cout << repeatTab(tab + 1) << it->first << ":" << std::endl;
    debugTokens(it->second, tab + 2);
  }
}