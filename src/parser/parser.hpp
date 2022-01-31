#include "readfile.hpp"
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include <map>
#include "token.hpp"

using std::vector, std::string, std::regex, std::map, std::make_pair, std::pair;

#pragma once

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
  vector<char> OneLongToken = {'{', '}', '(', ')', '[', ']', ';', '='};

public:
  Parser(const char *filename)
  {
    string fName;
    fName.push_back(*filename);

    FileData = ReadFile("main.mx");
    FileLength = FileData.length();
  }

  vector<pair<string, ParseTokenType>> ParseFile()
  {
    vector<pair<string, ParseTokenType>> tokens = {};

    for (this->FileIndex = 0; FileIndex < FileLength;)
    {
      if (isspace(get()))
      {
      }
      else if (std::count(OneLongToken.begin(), OneLongToken.end(), get()))
      {
        ParseTokenType x = (ParseTokenType)oneType();
        tokens.push_back(make_pair(string(1, get()), x));
      }
      else if (slice(3) == "fun")
      {
        FileIndex += 2;
        tokens.push_back(make_pair("fun", ParseTokenType::FunDeclaration));
      }
      else if (slice(3) == "var" || slice(3) == "let")
      {
        tokens.push_back(make_pair(slice(3), ParseTokenType::VarDecl));
        FileIndex += 2;
      }
      else if (isdigit(get()))
      {
        tokens.push_back(make_pair(parse_number(), ParseTokenType::Number));
        FileIndex--;
      }
      else if (get() == '"' || get() == '\'')
      {
        tokens.push_back(make_pair(parse_string(), ParseTokenType::String));
      }
      else if (isalpha(get()) || get() == '_')
      {
        tokens.push_back(make_pair(parse_expression(), ParseTokenType::Expression));
        FileIndex--;
      }

      FileIndex++;
    }

    for (int i = 0; i < tokens.size(); i++)
    {
      std::cout << tokens[i].first << " " << as_integer(tokens[i].second) << std::endl;
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
    string Expression = "" + get();
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
    while (isalpha(get()) || get() == '_' || get() == '2')
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
    default:
      std::cout << "Invalid token";
      exit(1);
    }
    return x;
  }
};