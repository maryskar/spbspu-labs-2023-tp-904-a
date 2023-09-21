#include "convertToPostfixNotation.h"
#include <string>
#include "isLessPriority.h"
#include <queue>
#include <stack>

namespace mashkin
{
  void convertToPostNot(const std::string& line, std::queue< std::string >& que)
  {
    std::stack< std::string > stc;
    std::string op;
    for (auto symb: line)
    {
      if (symb == ' ')
      {
        if (!op.find_first_of("()-+*/%!^"))
        {
          if (op == "(")
          {
            stc.push(op);
          }
          else if (op == ")")
          {
            while (stc.top() != "(")
            {
              que.push(stc.top());
              stc.pop();
            }
            stc.pop();
          }
          else if (stc.empty())
          {
            stc.push(op);
          }
          else
          {
            if (isLessPriority(stc.top(), op))
            {
              while (!stc.empty())
              {
                que.push(stc.top());
                stc.pop();
              }
              stc.push(op);
            }
            else
            {
              stc.push(op);
            }
          }
        }
        else if (!op.empty())
        {
          que.push(op);
        }
        op = "";
      }
      else
      {
        op += symb;
      }
    }
    while (!stc.empty())
    {
      if (stc.top() == "(")
      {
        throw std::logic_error("There are parentheses");
      }
      que.push(stc.top());
      stc.pop();
    }
  }
}
