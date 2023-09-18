#include "convertinfixtopostfix.hpp"
#include <string>
#include <stdexcept>
#include <queue>
#include <stack>
#include <map>

namespace hrushchev
{
  int getOperatorPriority(const std::string& op)
  {
    if (op == "*" || op == "/" || op == "%" || op == "sin" || op == "cos")
    {
      return 2;
    }
    else if (op == "+" || op == "-")
    {
      return 1;
    }
    else if (op == "(" || op == ")")
    {
      return 0;
    }
    else
    {
      throw std::logic_error("Invalid operator");
    }
  }

  bool isHigherPriority(const std::string& op1, const std::string& op2)
  {
    return getOperatorPriority(op1) >= getOperatorPriority(op2);
  }

  bool isOperator(const std::string& op)
  {
    return op == "*" || op == "/" || op == "+" || op == "-" || op == "(" || op == ")" || op == "%";
  }

  bool isUnaryOperator(const std::string& op)
  {
    return op == "sin" || op == "cos";
  }

  bool isVariable(const std::string& op, std::map< std::string, std::string >& variables)
  {
    try
    {
      variables.at(op);
      return true;
    }
    catch(...)
    {
      return false;
    }
  }
}

std::queue< std::string > hrushchev::convertInfixToPostfix(std::queue< std::string >& infixQueue,
    std::map< std::string, std::string >& variables)
{
  namespace hrn = hrushchev;
  std::queue< std::string > postfixQueue;
  std::stack< std::string > stack;

  while (!infixQueue.empty())
  {
    std::string token = infixQueue.front();
    infixQueue.pop();
    if (std::isdigit(token[0]))
    {
      postfixQueue.push(token);
    }
    else if (hrn::isOperator(token))
    {
      if (token == ")")
      {
        while (!stack.empty() && (stack.top() != "("))
        {
          postfixQueue.push(stack.top());
          stack.pop();
        }
        if (stack.empty())
        {
          throw std::logic_error("Mismatched parentheses");
        }
        stack.pop();
      }
      else if (token == "(")
      {
        stack.push(token);
      }
      else
      {
        while (!stack.empty() && (hrn::isHigherPriority(stack.top(),token)))
        {
          postfixQueue.push(stack.top());
          stack.pop();
        }
        stack.push(token);
      }
    }
    else if (isUnaryOperator(token))
    {
      stack.push(token);
    }
    else if (isVariable(token, variables))
    {
      stack.push(variables.at(token));
    }
    else
    {
      throw std::logic_error("Invalid token");
    }
  }

  while (!stack.empty())
  {
    std::string op = stack.top();
    stack.pop();
    if (op == "(")
    {
      throw std::logic_error("Mismatched parentheses");
    }
    postfixQueue.push(op);
  }

  return postfixQueue;
}
