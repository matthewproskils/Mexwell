#include "src/parser/parser.hpp"
#include "src/lexer/lexer.hpp"
#include "src/compiler/compiler.hpp"

void MexFile(const char* Filename, Scope* global)
{
  Parser *parser = new Parser("main.mx");
  vector<ParseToken *> Parsed = parser->ParseFile();
  // parser->debug(Parsed);

  Lexer *lexer = new Lexer(Parsed);
  vector<Token *> tokens = lexer->LexFile();

  // for (size_t i = 0; i < tokens.size(); i++)
  // {
  //   debugTokens(tokens[i]);
  // }

  Compiler *compiler = new Compiler();
  compiler->compile(global, tokens);
  if (global->hasSymbol("main"))
  {
    if (global->get_symbol("main")->Func->args.size() != 0) {
      std::cout << "Error: main function must have no arguments" << std::endl;
      exit(1);
    }
    compiler->compile(global, global->get_symbol("main")->Func->code);
  } else {
    std::cout << "Error: main function not found" << std::endl;
    exit(1);
  }
  global->print_symbols();
}

void Mex(string data, Scope* global)
{
  Parser *parser = new Parser(data);
  vector<ParseToken*> Parsed = parser->ParseFile();
  // parser->debug(Parsed);

  Lexer *lexer = new Lexer(Parsed);
  vector<Token *> tokens = lexer->LexFile();
  
  // for (size_t i = 0; i < tokens.size(); i++)
  // {
  //   debugTokens(tokens[i]);
  // }

  Compiler *compiler = new Compiler();
  compiler->compile(global, tokens);
  if (global->hasSymbol("main"))
  {
    if (global->get_symbol("main")->Func->args.size() != 0) {
      std::cout << "Error: main function must have no arguments" << std::endl;
      exit(1);
    }
    compiler->compile(global, global->get_symbol("main")->Func->code);
  } else {
    std::cout << "Error: main function not found" << std::endl;
    exit(1);
  }
  // global->print_symbols();
}

void MexDebug(string data, Scope* global)
{
  Parser *parser = new Parser(data);
  vector<ParseToken*> Parsed = parser->ParseFile();
  parser->debug(Parsed);

  Lexer *lexer = new Lexer(Parsed);
  vector<Token *> tokens = lexer->LexFile();
  
  for (size_t i = 0; i < tokens.size(); i++)
  {
    debugTokens(tokens[i]);
  }

  Compiler *compiler = new Compiler();
  compiler->compile(global, tokens);
  if (global->hasSymbol("main"))
  {
    if (global->get_symbol("main")->Func->args.size() != 0) {
      std::cout << "Error: main function must have no arguments" << std::endl;
      exit(1);
    }
    compiler->compile(global, global->get_symbol("main")->Func->code);
  } else {
    std::cout << "Error: main function not found" << std::endl;
    exit(1);
  }
  global->print_symbols();
}