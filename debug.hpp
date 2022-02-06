#include "src/parser/parser.hpp"
#include "src/lexer/lexer.hpp"
#include "src/compiler/compiler.hpp"

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

void MexFile(const char* Filename)
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