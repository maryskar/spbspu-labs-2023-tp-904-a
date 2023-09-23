#include "commands.h"
#include <map>
#include <memory>
#include <queue>
#include <stack>
#include "convertToPostfixNotation.h"
#include "isLessPriority.h"
#include "semanticTree.h"
#include "solving.h"

namespace mashkin
{
  using semTree = SemanticTree< std::string >;

  bool isOperator(const std::string& symb)
  {
    return symb == "*" || symb == "+" || symb == "-" || symb == "/" || symb == "!" || symb == "^" || symb == "%";
  }

  short int defineOperation(const std::string& symb)
  {
    if (symb == "!")
    {
      return 1;
    }
    else
    {
      return 2;
    }
  }

  std::ostream& printQueue(std::ostream& out, std::queue< std::string >& que)
  {
    while (!que.empty())
    {
      out << que.front();
      que.pop();
      if (!que.empty())
      {
        out << " ";
      }
    }
    return out;
  }

  void inputExpressionToTree(std::queue< std::string >& que, std::stack< std::shared_ptr< semTree > >& stack)
  {
    while (!que.empty())
    {
      auto newNode = std::make_shared< semTree >(semTree{que.front(), {}});
      if (isOperator(que.front()))
      {
        auto operation = defineOperation(que.front());
        for (short int i = --operation; i >= 0; i--)
        {
          newNode->children[i] = stack.top();
          stack.pop();
        }
      }
      stack.push(newNode);
      que.pop();
    }
  }

  void addExpr(std::istream& input, std::map< std::string, std::shared_ptr< SemanticTree< std::string > > >& map)
  {
    std::queue< std::string > que;
    std::string key;
    std::string line;
    std::stack< std::shared_ptr< semTree > > expression;
    input >> key;
    std::getline(input, line);
    line += " ";
    convertToPostNot(line, que);
    inputExpressionToTree(que, expression);
    map[key] = expression.top();
    expression.pop();
  }

  void solveNode(std::shared_ptr< semTree >& node)
  {
    static std::map< std::string, int long long (*)(int long long, int long long) > mapOfSolving;
    mapOfSolving["!"] = factorial;
    mapOfSolving["+"] = sum;
    mapOfSolving["-"] = minus;
    mapOfSolving["*"] = multiplicate;
    mapOfSolving["/"] = divide;
    mapOfSolving["%"] = getRemainderAfterDivision;
    mapOfSolving["^"] = exponentiate;
    if (defineOperation(node->data) == 1)
    {
      int long long var = std::stoll(node->children[0]->data);
      node->data = std::to_string(mapOfSolving[node->data](var, var));
    }
    else
    {
      int long long first = std::stoll(node->children[0]->data);
      int long long second = std::stoll(node->children[1]->data);
      node->data = std::to_string(mapOfSolving[node->data](first, second));
    }
  }

  std::shared_ptr< semTree > getSimplify_impl(std::shared_ptr< semTree >& node, std::shared_ptr< semTree >& before)
  {
    if (node->children.empty())
    {
      return before;
    }
    for (short int i = 0; i < defineOperation(node->data); i++)
    {
      node = getSimplify_impl(node->children[i], node);
    }
    for (short int i = 0; i < defineOperation(node->data); i++)
    {
      if (node->children[i]->data.find_first_of("0123456789"))
      {
        return before;
      }
    }
    solveNode(node);
    node->children.clear();
    return before;
  }

  std::shared_ptr< semTree > copyExpr_impl(const std::shared_ptr< semTree >& toCopy,
      const std::shared_ptr< semTree >& tree)
  {
    if (tree->children.empty())
    {
      return toCopy;
    }
    for (short int i = 0; i < defineOperation(tree->data); i++)
    {
      toCopy->children[i] = std::make_shared< semTree >(semTree{tree->children.at(i)->data, {}});
      copyExpr_impl(toCopy->children.at(i), tree->children.at(i));
    }
    return toCopy;
  }

  std::shared_ptr< semTree > copyExpr(const std::shared_ptr< semTree >& tree)
  {
    auto res = std::make_shared< semTree >(semTree{tree->data, {}});
    return copyExpr_impl(res, tree);
  }

  void simplifyExpr(std::istream& inp, std::map< std::string, std::shared_ptr< semTree > >& map)
  {
    std::string key;
    std::string expr;
    inp >> key;
    inp >> expr;
    map[key] = copyExpr(map[expr]);
    auto node = map[key];
    auto begin = node;
    getSimplify_impl(begin, begin);
  }

  struct Parameters
  {
    void operator()(const std::string& value)
    {
      if (value.find_first_of("0123456789!%^*-+/"))
      {
        param_.push(value);
      }
    }

    std::queue< std::string > param_;
  };

  template< class F >
  F traverse_lnr_impl(std::shared_ptr< semTree >& root, F& f)
  {
    if (!root)
    {
      return f;
    }
    for (short int i = 0; i < root->children.size(); i++)
    {
      traverse_lnr_impl(root->children[i], f);
    }
    f(root->data);
    return f;
  }

  void getParameters(std::istream& inp, std::map< std::string, std::shared_ptr< semTree > >& map)
  {
    std::string key;
    inp >> key;
    Parameters param;
    traverse_lnr_impl(map[key], param);
    if (param.param_.empty())
    {
      std::cout << "Expression has no parameters\n";
    }
    else
    {
      printQueue(std::cout, param.param_) << "\n";
    }
  }

  struct NewParam
  {
    void operator()(std::string& value)
    {
      if (value == param_)
      {
        value = newParam_;
      }
    }

    std::string param_;
    std::string newParam_;
  };

  void setNewExpr(std::istream& inp, std::map< std::string, std::shared_ptr< semTree > >& map)
  {
    std::string expr;
    std::string key;
    inp >> key;
    inp >> expr;
    NewParam newParam;
    inp >> newParam.param_;
    inp >> newParam.newParam_;
    Parameters param;
    traverse_lnr_impl(map[expr], param);
    if (param.param_.empty())
    {
      std::cout << "Expression has no parameters\n";
    }
    else
    {
      map[key] = copyExpr(map[expr]);
      traverse_lnr_impl(map[key], newParam);
    }
  }

  void replaceExprTtQueue(std::queue< std::string >& que, std::shared_ptr< semTree >& root)
  {
    if (root->children.empty())
    {
      que.push(root->data);
      return;
    }
    for (short int i = 0; i < root->children.size(); i++)
    {
      if (isOperator(root->data) && isOperator(root->children[i]->data))
      {
        if (isLessPriority(root->data, root->children[i]->data))
        {
          que.push("(");
          replaceExprTtQueue(que, root->children[i]);
          que.push(")");
          if (i == 0)
          {
            que.push(root->data);
          }
          continue;
        }
      }
      replaceExprTtQueue(que, root->children[i]);
      if (i == 0)
      {
        que.push(root->data);
      }
    }
  }

  void showExpr(std::istream& inp, std::map< std::string, std::shared_ptr< semTree > >& map)
  {
    std::string key;
    inp >> key;
    if (map.find(key) == map.end())
    {
      std::cout << "There is no expr\n";
      return;
    }
    std::queue< std::string > toPrint;
    replaceExprTtQueue(toPrint, map[key]);
    printQueue(std::cout, toPrint) << "\n";
  }
}
