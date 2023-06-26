#include "commands.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include "polygon.h"
#include "solvingCommands.h"

/*void runRightshapes(std::istream& inp, std::string& command);
void runPerms(std::istream& inp, std::string& command);
void runCount(std::istream& inp, std::string& command);
void runMin(std::istream& inp, std::string& command);
void runMax(std::istream& inp, std::string& command);*/
void runArea(std::istream& inp, std::string& command, const std::vector< mashkin::Polygon >& res);

std::vector< mashkin::FullArea > getFullArea(const std::vector< mashkin::Polygon >& res)
{
  std::vector< mashkin::PositiveArea > halfPA;
  std::vector< mashkin::NegativeArea > halfNA;
  std::vector< mashkin::FullArea > area;
  std::transform(res.begin(), res.end(), std::back_inserter(halfPA), mashkin::calcPositiveArea);
  std::transform(res.begin(), res.end(), std::back_inserter(halfNA), mashkin::calcNegativeArea);
  std::transform(halfPA.begin(), halfPA.end(), halfNA.begin(), std::back_inserter(area), mashkin::solveArea);
  return area;
}

void runEven(const std::vector< mashkin::Polygon >& res)
{
  std::vector< mashkin::FullArea > fullArea = getFullArea(res);
}

/*void runOdd();
void runMean();
void runAreaNumOfVertexes(std::string& command);*/

void runArea(std::istream& inp, std::string& command, const std::vector< mashkin::Polygon >& res)
{
  inp >> command;
  if (command == "EVEN")
  {
    runEven(res);
  }
  /*else if (command == "ODD")
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
  }*/
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
    /*else if (command == "MAX")
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
    }*/
    else
    {
      std::cout << " <INVALID COMMAND>";
    }
  }
}
