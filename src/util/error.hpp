#include <iostream>
#include <string>

void Error(Token* T, string Note, string FileName)
{
  std::cout << "\n\033[1;33mAt File: " + FileName + " \033[1;31m[Error] \n\033[0;m" + Note + "\nLine " + std::to_string(T->lineNumber) + " char " + std::to_string(T->charNumber) + " \n\033[1;31m[Token:] \033[0m" + T->value << std::endl;

  /*
    Ex:
    At File: VM [Error]
    Expected Semicolon or Open Bracket or Open Parenthesis
    Line 3 char 9
    [Token:] ==
  */

  throw;
  // exit(0);
};

void Error(string T, string Note, string FileName)
{
  std::cout << "\n\033[1;33mAt File: " + FileName + " \033[1;31m[Error] \n\033[0;m" + Note + "\n\033[1;31m[Token:] \033[0m" + T << std::endl;

  /*
    Ex:
    At File: VM [Error]
    Expected Semicolon or Open Bracket or Open Parenthesis
    Line 3 char 9
    [Token:] ==
  */

  throw;
  // exit(1);
};