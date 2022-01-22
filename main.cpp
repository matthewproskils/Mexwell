#include "src/parser/parser.hpp"
#include "src/lexer/lexer.hpp"

int main(int argc, char const *argv[])
{
  Parser *parser = new Parser("main.mx");
  vector<pair<string, int>> Parsed = parser->ParseFile();

  Lexer *lexer = new Lexer(Parsed);
  vector<Token*> tokens = lexer->LexFile();
  return 0;
}
