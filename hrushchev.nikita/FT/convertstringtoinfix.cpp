#include "convertstringtoinfix.hpp"
#include <string>
#include <queue>

bool isOperator(char c)
{
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
}

std::queue< std::string > hrushchev::convertStringToInfix(std::string str)
{
  namespace hrn = hrushchev;
  std::queue< std::string > infix_queue;
  std::string cur_token;

  infix_queue.push("(");
  for (char c : str)
  {
    if (isOperator(c))
    {
      if (!cur_token.empty())
      {
        infix_queue.push(cur_token);
        cur_token.clear();
      }
      infix_queue.push(std::string(1, c));
    }
    else
    {
      cur_token += c;
    }
  }

  if (!cur_token.empty())
  {
    infix_queue.push(cur_token);
  }
  infix_queue.push(")");
  return infix_queue;
}

