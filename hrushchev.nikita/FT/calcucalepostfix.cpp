#include "calcucalepostfix.hpp"
#include <string>
#include <stdexcept>
#include <cmath>
#include <stack>
#include <queue>
#include "arithmetic.hpp"

long double hrushchev::calculatePostfix(std::queue< std::string >& postfixQueue)
{
  namespace hrn = hrushchev;

  std::stack< long double > stack;
  while (!postfixQueue.empty())
  {
    std::string token = postfixQueue.front();
    postfixQueue.pop();
    if (std::isdigit(token[0]))
    {
      stack.push(std::stold(token));
    }
    else if (token == "sin" || token == "cos")
    {
      if (stack.empty())
      {
        throw std::logic_error("Not enough operands for unary operator");
      }
      long double operand = stack.top();
      stack.pop();
      long double result;
      if (token == "sin")
      {
        result = hrn::sin(operand);
      }
      else if (token == "cos")
      {
        result = hrn::cos(operand);
      }
      stack.push(result);
    }
    else
    {
      long double operand2 = stack.top();
      stack.pop();
      long double operand1 = stack.top();
      stack.pop();
      long double result;
      if (token == "+")
      {
        result = hrn::sum(operand1, operand2);
      }
      else if (token == "-")
      {
        result = hrn::subtract(operand1, operand2);
      }
      else if (token == "*")
      {
        result = hrn::multiply(operand1, operand2);
      }
      else if (token == "/")
      {
        result = hrn::division(operand1, operand2);
      }
      else if (token == "%")
      {
        result = hrn::remaind(operand1, operand2);
      }
      stack.push(result);
    }
  }
  return stack.top();
}


