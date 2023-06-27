#include "commands.h"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>
#include "polygon.h"
#include "solvingCommands.h"

using namespace std::placeholders;

/*struct Person
{
  Person(int rhs):
    res(rhs)
  {
  }

  bool operator==(const Person& rhs)
  {
    return res == rhs.res;
  }

  int res;
};

std::vector< Person > data3;
using namespace std::placeholders;
std::sort(std::begin(data3), std::end(data3), std::bind(std::equal_to< Person >(), _1, Person(1)));*/

/*void runRightshapes(std::istream& inp, std::string& command);
void runPerms(std::istream& inp, std::string& command);
void runCount(std::istream& inp, std::string& command);
void runMin(std::istream& inp, std::string& command);
void runMax(std::istream& inp, std::string& command);*/
void runArea(std::istream& inp, std::string& command, const std::vector< mashkin::Polygon >& res);

void runEven(const std::vector< mashkin::Polygon >& res)
{
  using pol = mashkin::Polygon;
  std::vector< pol > data = res;
  std::vector< pol >::iterator it = std::partition(data.begin(), data.end(), mashkin::isEven);
  std::vector< mashkin::FullArea > areas = mashkin::getFullArea(data.begin(), it);
  mashkin::FullArea sumArea = std::accumulate(areas.begin(), areas.end(), mashkin::FullArea());
  std::cout << sumArea;
}

void runOdd(const std::vector< mashkin::Polygon >& res)
{
  using pol = mashkin::Polygon;
  std::vector< pol > data = res;
  std::vector< pol >::iterator it = std::partition(data.begin(), data.end(), mashkin::isOdd);
  std::vector< mashkin::FullArea > areas = mashkin::getFullArea(data.begin(), it);
  mashkin::FullArea sumArea = std::accumulate(areas.begin(), areas.end(), mashkin::FullArea());
  std::cout << sumArea;
}

void runMean(const std::vector< mashkin::Polygon >& res)
{
  std::vector< mashkin::Polygon > data = res;
  size_t quntity = res.size();
  std::vector< mashkin::FullArea > areas = mashkin::getFullArea(data.begin(), data.end());
  mashkin::FullArea sumArea = std::accumulate(areas.begin(), areas.end(), mashkin::FullArea());
  sumArea.res /= quntity;
  std::cout << sumArea;
}

void runAreaNumOfVertexes(const std::vector< mashkin::Polygon >& res, const std::string& num)
{
  using pol = mashkin::Polygon;
  std::vector< mashkin::Polygon > data = res;
  size_t count = std::stoull(num);
  std::vector< pol >::iterator it = std::partition(data.begin(), data.end(), std::bind(mashkin::isEqual, _1, count));
  std::vector< mashkin::FullArea > areas = mashkin::getFullArea(data.begin(), it);
  mashkin::FullArea sumArea = std::accumulate(areas.begin(), areas.end(), mashkin::FullArea());
  std::cout << sumArea;
}

void runArea(std::istream& inp, std::string& command, const std::vector< mashkin::Polygon >& res)
{
  inp >> command;
  if (command == "EVEN")
  {
    runEven(res);
  }
  else if (command == "ODD")
  {
    runOdd(res);
  }
  else if (command == "MEAN")
  {
    runMean(res);
  }
  else if (command.find_first_not_of("0123456789") == std::string::npos)
  {
    runAreaNumOfVertexes(res, command);
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
    else if (inp.eof())
    {
      return;
    }
    else
    {
      std::cout << " <INVALID COMMAND>";
    }
  }
}
