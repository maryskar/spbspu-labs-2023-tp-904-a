#include "commands.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include "polygon.h"
#include "solvingCommands.h"

void runRightshapes(std::istream& inp, std::string& command);
void runPerms(std::istream& inp, std::string& command);
void runCount(std::istream& inp, std::string& command);
void runMin(std::istream& inp, std::string& command);
void runMax(std::istream& inp, std::string& command);
void runArea(std::istream& inp, std::string& command);

// auto begin = res.begin();
// auto end = res.end();
// auto
// std::transform(res.begin(), res.end(), out.begin(),
// структура(1) данных которая имеет в себе сумму x(n)y(n + 1)
/*
  struct Polygon
  {
    std::vector< Point > points;
  };
  struct XMultiY
  {
    XMultiY(const Point& first, const Point& second)
    {
      res = first.x * second.y;
    }
    int res;
  };
  XMultiY solveXY(const Point& rhs)
  {
    return XMultiY(rhs);
  }
  struct PositiveArea
  {
    PositiveArea(const Polygon& lhs, const Polygon& rhs)
    {
      std::transform(lhs.points.begin(), --lhs.points.end(), ++rhs.point.begin(), *this.halfArea.begin(), solveXY);
    }
    std::vector< XMultiY > halfArea;
  };
  vector< PositiveArea > halfPArea;
  PositiveArea calcPositiveArea(const Polygon& first, const Polygon& second)
  {
    return PositiveArea(first, second);
  }
  std::transform(res.begin(), res.end(), halfPArea().begin(), calcPositiveArea);

*/
// структура(2) данных которая имеет в себе сумму x(n+1)y(n)
// структура данных которая имеет в себе разницу (1) - (2)
void runEven(const std::vector< mashkin::Polygon >& res)
{
  std::vector< mashkin::PositiveArea > halfPArea;
  std::vector< mashkin::NegativeArea > halfNArea;
  std::vector< mashkin::FullArea > fullArea;
  std::transform(res.begin(), res.end(), halfPArea.begin(), mashkin::calcPositiveArea);
  std::transform(res.begin(), res.end(), halfNArea.begin(), mashkin::calcNegativeArea);
  std::transform(halfPArea.begin(), halfPArea.end(), halfNArea.begin(), fullArea.begin(), mashkin::solveArea);
}

void runOdd();
void runMean();
void runAreaNumOfVertexes(std::string& command);

void runArea(std::istream& inp, std::string& command, const std::vector< mashkin::Polygon >& res)
{
  inp >> command;
  if (command == "EVEN")
  {
    runEven(res);
  }
  else if (command == "ODD")
  {
    runOdd();
  }
  else if (command == "MEAN")
  {
    runMean();
  }
  else if (command.find_first_not_of("0123456789") == std::string::npos)
  {
    runAreaNumOfVertexes(command);
  }
  else
  {
    std::cout << " <INVALID COMMAND>";
  }
}

namespace mashkin
{
  void runCommand(std::istream& inp, std::string& command, const std::vector< Polygon >& res)
  {
    inp >> command;
    if (command == "AREA")
    {
      runArea(inp, command, res);
    }
    else if (command == "MAX")
    {
      runMax(inp, command);
    }
    else if (command == "MIN")
    {
      runMin(inp, command);
    }
    else if (command == "COUNT")
    {
      runCount(inp, command);
    }
    else if (command == "PERMS")
    {
      runPerms(inp, command);
    }
    else if (command == "RIGHTSHAPES")
    {
      runRightshapes(inp, command);
    }
  }
}
