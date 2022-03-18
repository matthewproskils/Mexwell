#include "src/parser/parser.hpp"
#include "src/lexer/lexer.hpp"
#include "src/compiler/compiler.hpp"
#include "src/util/std.hpp"

Scope* Main(vector<Token*> tokens, string filename)
{
  Compiler* compiler = new Compiler();
  Scope *global = mex_std(filename);
  compiler->compile(global, tokens);

  compiler->compile(global, global->get_symbol("main")->Func->code);

  return global;
}

void MexFile(const char *Filename)
{
  Parser *parser = new Parser("main.mx");
  vector<ParseToken *> Parsed = parser->ParseFile();
  parser->debug(Parsed);

  Lexer *lexer = new Lexer(Parsed);
  vector<Token *> tokens = lexer->LexFile();

  for (size_t i = 0; i < tokens.size(); i++)
  {
    debugTokens(tokens[i]);
  }

  Scope* global = Main(tokens, lexer->FileName);

  // global->print_symbols();
}

void Mex(string data)
{
  Parser *parser = new Parser(data);
  vector<ParseToken *> Parsed = parser->ParseFile();

  Lexer *lexer = new Lexer(Parsed);
  vector<Token *> tokens = lexer->LexFile();

  Main(tokens, lexer->FileName);
}

void MexDebug(string data)
{
  Parser *parser = new Parser(data);
  vector<ParseToken *> Parsed = parser->ParseFile();
  parser->debug(Parsed);

  Lexer *lexer = new Lexer(Parsed);
  vector<Token *> tokens = lexer->LexFile();

  for (size_t i = 0; i < tokens.size(); i++)
  {
    debugTokens(tokens[i]);
  }

  Scope* global = Main(tokens, lexer->FileName);
  global->print_symbols();
}