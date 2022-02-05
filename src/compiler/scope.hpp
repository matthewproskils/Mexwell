#include "scope.h"
#include "../lexer/lexer.hpp"

#pragma once

inline Scope::Scope(Scope *parent) : parent(parent){};

inline void Scope::add_symbol(string name, Symbol *s) {
  this->symbols.insert(std::pair<string, Symbol*>(name, s));
};

inline Symbol* Scope::get_symbol(string name) {
  if (this->symbols.find(name) != this->symbols.end()) {
    return this->symbols[name];
  } else if (this->parent != nullptr) {
    return this->parent->get_symbol(name);
  } else {
    std::cout << "Compiler Error, Variable " << name << " Does Not Exist." << std::endl;
    exit(1);
  }
};

inline void Scope::print_symbols() {
  std::cout << "Scope: " << std::endl;
  for (auto i : this->symbols) {
    std::cout << i.first << ": " << i.second->value << ", type: " << to_underlying(i.second->type) << std::endl;
  }
}

inline void Scope::add_symbol(std::pair<string, Symbol*> s) {
  this->symbols.insert(s);
}

inline void is_restricted(string name) {
  vector<string> restricted = {
      "true",
      "false",
      "fun",
      "var",
      "let",
      "if",
      "else",
      "while",
      "for",
      "in",
      "return"};

  if (std::find(restricted.begin(), restricted.end(), name) != restricted.end()) {
    std::cout << "Compiler Error, Variable " << name << " Is Restricted." << std::endl;
    exit(1);
  }
}