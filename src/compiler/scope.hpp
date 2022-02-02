#include "scope.h"

#pragma once

inline Scope::Scope(Scope *parent) : parent(parent){};

inline void add_symbol(Symbol *symbol) {
  // this->symbols.insert(std::pair<string, Symbol*>(symbol->name, symbol));
};