#include <string>
#include <map>
#include <iostream>

using std::string, std::map;
#pragma once

enum TokenType
{
  FuncDeclaration
};

class Token {
public:
  int type;
  string value;
  map<string, Token> Children = {};

  Token(string Value, int Type) {
    type = Type;
    value = Value;
  }

  void add_child(string name, Token token) {
    Children.insert(std::pair<string, Token>(name, token));
  }

  std::pair<string, Token> get_child(string name) {
    auto it = Children.find(name);
    if (it == Children.end()) {
      std::cout << "Error: Cannot find child " << name << std::endl;
    } else {
      return *it;
    }
  }
};