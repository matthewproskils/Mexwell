#include "compiler.h"
#include "scope.hpp"

inline Compiler::Compiler(vector<Token *> tokens) {
  this->tokens = tokens;
}

inline void Compiler::compile() {
  Scope *global = new Scope(nullptr);
  Scope *current = global;
  
  this->ParsedIndex = 0;
  while (this->ParsedIndex < this->tokens.size()) {
    
  }
}