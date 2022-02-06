#include "src/parser/parser.hpp"
#include "src/lexer/lexer.hpp"
#include "src/compiler/compiler.hpp"

void MexFile(const char* Filename)
{
  Parser *parser = new Parser("main.mx");
  vector<ParseToken *> Parsed = parser->ParseFile();
  // parser->debug(Parsed);

  Lexer *lexer = new Lexer(Parsed);
  vector<Token *> tokens = lexer->LexFile();

  for (size_t i = 0; i < tokens.size(); i++)
  {
    debugTokens(tokens[i]);
  }

  Compiler *compiler = new Compiler(tokens);
  compiler->compile();
}

void Mex(string data)
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

  Compiler* compiler = new Compiler(tokens);
  compiler->compile();
}

void MexDebug(string data)
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

  Compiler* compiler = new Compiler(tokens);
  compiler->compile();
}