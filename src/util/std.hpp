#include "../compiler/compiler.hpp"

#pragma once

Symbol* print(std::vector<Symbol *> s)
{
  for (size_t i = 0; i < s.size(); i++)
  {
    std::cout << s[i]->value << std::endl;
  }
  
  return new Symbol("void", SymbolType::Void, false); 
}

Symbol* int_to_string(std::vector<Symbol *> s)
{
  s[0]->type = SymbolType::String;
  return s[0];
}

Scope *mex_std()
{
  // const char* filename = "main.mx";
  // MexFile(filename);

  Scope *global = new Scope(nullptr);
  // get function pointer

  SymbolFunction *p = new SymbolFunction("print", {SymbolType::String}, SymbolType::Void, print);
  p->setInfArgs();
  global->add_symbol("print", new Symbol(p));

  SymbolFunction *its = new SymbolFunction("int_to_string", {SymbolType::Number}, SymbolType::Number, int_to_string);
  global->add_symbol("int_to_string", new Symbol(its));

  return global;
}