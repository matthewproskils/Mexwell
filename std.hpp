#include "./src/compiler/compiler.hpp"

#pragma once

Symbol* print(vector<Symbol *> s)
{
  for (size_t i = 0; i < s.size(); i++)
  {
    std::cout << s[i]->value << std::endl;
  }
  
  return nullptr; 
}

Scope *mex_std()
{
  // const char* filename = "main.mx";
  // MexFile(filename);

  Scope *global = new Scope(nullptr);
  // get function pointer

  SymbolFunction *p = new SymbolFunction("print", {SymbolType::String}, print);
  p->setInfArgs();
  global->add_symbol("print", new Symbol(p));


  return global;
}