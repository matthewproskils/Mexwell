#ifndef PARSER_HPP
#define PARSER_HPP

#include "readfile.hpp"
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <map>
#include "token.hpp"

using std::make_pair;
using std::map;
using std::regex;
using std::string;
using std::pair;
using std::vector;

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
  return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

class Parser
{
private:
  string FileData;
  int FileIndex;
  int FileLength;
  vector<char> OneLongToken = {'{', '}', '(', ')', '[', ']', ';', '=', ','};

public:
  Parser(const char *filename)
  {
    string fName;
    fName.push_back(*filename);

    FileData = ReadFile(filename);
    FileLength = FileData.length();
  }

  Parser(string FileData)
  {
    this->FileData = FileData;
    FileLength = FileData.length();
  }

  vector<ParseToken *> ParseFile()
  {
    vector<ParseToken *> tokens = {};

    for (this->FileIndex = 0; FileIndex < FileLength;)
    {
      if (isspace(get()))
      {
      }
      else if (std::find(OneLongToken.begin(), OneLongToken.end(), get()) != std::end(OneLongToken))
      {
        ParseTokenType x = (ParseTokenType)oneType();
        tokens.push_back(new ParseToken(x, string(1, get()), lineNumber(), charNumber()));
      }
      else if (slice(3) == "fun")
      {
        FileIndex += 2;
        tokens.push_back(new ParseToken(ParseTokenType::FunDeclaration, "fun", lineNumber(), charNumber()));
      }
      else if (slice(3) == "var")
      {
        tokens.push_back(new ParseToken(ParseTokenType::VarDecl, slice(3), lineNumber(), charNumber()));
        FileIndex += 2;
      }
      else if (isdigit(get()))
      {
        tokens.push_back(new ParseToken(ParseTokenType::Number, parse_number(), lineNumber(), charNumber()));
        FileIndex--;
      }
      else if (get() == '"' || get() == '\'')
      {
        tokens.push_back(new ParseToken(ParseTokenType::String, parse_string(), lineNumber(), charNumber()));
      }
      else if (isalpha(get()) || get() == '_')
      {
        tokens.push_back(new ParseToken(ParseTokenType::Expression, parse_expression(), lineNumber(), charNumber()));
        FileIndex--;
      } else {
        std::cout << "Unexpected " << get() << " at line " << lineNumber() << " char " << charNumber() << std::endl;
        exit(1);
      }
      FileIndex++;
    }

    return tokens;
  }

  char get()
  {
    return FileData[FileIndex];
  }

  string slice(int len)
  {
    return FileData.substr(FileIndex, FileIndex + len);
  }

  string until_end()
  {
    return FileData.substr(FileIndex, FileLength - 1);
  }

  string parse_string()
  {
    string Expression = string(1, get());
    FileIndex++;
    while (get() != Expression[0])
    {
      Expression.push_back(get());
      if (get() == '\\')
      {
        FileIndex++;
        Expression.push_back(get());
      }
      FileIndex++;
    }
    Expression.push_back(get());
    return Expression;
  }

  string parse_expression()
  {
    string Expression = "";
    while (isalpha(get()) || get() == '_' || isdigit(get()))
    {
      Expression.push_back(get());
      FileIndex++;
    };
    return Expression;
  }

  string parse_number()
  {
    string Number = "";
    while (isdigit(get()))
    {
      Number.push_back(get());
      FileIndex++;
    }
    return Number;
  }

  ParseTokenType oneType()
  {
    ParseTokenType x = ParseTokenType::String;
    switch (get())
    {
    case '{':
      x = ParseTokenType::OpenCurlyBracket;
      break;
    case '}':
      x = ParseTokenType::CloseCurlyBracket;
      break;
    case '(':
      x = ParseTokenType::OpenParenthesis;
      break;
    case ')':
      x = ParseTokenType::CloseParenthesis;
      break;
    case '[':
      x = ParseTokenType::OpenBracket;
      break;
    case ']':
      x = ParseTokenType::CloseBracket;
      break;
    case ';':
      x = ParseTokenType::Semicolon;
      break;
    case '=':
      x = ParseTokenType::EqualsSign;
      break;
    case ',':
      x = ParseTokenType::Comma;
      break;
    default:
      std::cout << "Invalid token";
      exit(1);
    }
    return x;
  }

  int lineNumber()
  {
    int newlines = 0;
    for (int i = 0; i < FileIndex; i++)
    {
      if (FileData[i] == '\n')
      {
        newlines++;
      }
    }
    return newlines + 1;
  }

  int charNumber()
  {
    // Go backwards from fileIndex until you find a newline
    int i = FileIndex;
    for (; i > 0; i--)
    {
      if (FileData[i] == '\n')
      {
        break;
      }
    }
    return FileIndex - i;
  }

  void debug(vector<ParseToken *> tokens)
  {
    for (auto token : tokens)
    {
      std::cout << "Line: " << token->lineNumber << ", Character: " << token->charNumber << ", Type: " << as_integer(token->type) << ", Value: " << token->value << std::endl;
    }
  }
};

#endif // PARSER_HPP
