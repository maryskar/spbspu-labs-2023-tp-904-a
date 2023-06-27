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

namespace mashkin
{
  using namespace std::placeholders;
  using pol = Polygon;
  using vecPol = std::vector< pol >;
  using farea = FullArea;
  using vecFArea = std::vector< farea >;
  using outIter = std::ostream_iterator< farea >;

  /*void runRightshapes(std::istream& inp, std::string& command);
  void runPerms(std::istream& inp, std::string& command);
  void runCount(std::istream& inp, std::string& command);
  void runMin(std::istream& inp, std::string& command);
  */
  void runMax(std::istream& inp, std::string& command, const vecPol& res);
  void runArea(std::istream& inp, std::string& command, const vecPol& res);

  void runEven(const vecPol& res)
  {
    vecPol data = res;
    vecPol::iterator it = std::partition(data.begin(), data.end(), isEven);
    vecFArea areas = getFullArea(data.begin(), it);
    vecFArea sumArea;
    sumArea.push_back(std::accumulate(areas.begin(), areas.end(), farea()));
    std::copy(sumArea.begin(), sumArea.end(), outIter(std::cout, "\n"));
  }

  void runOdd(const vecPol& res)
  {
    vecPol data = res;
    vecPol::iterator it = std::partition(data.begin(), data.end(), isOdd);
    vecFArea areas = getFullArea(data.begin(), it);
    vecFArea sumArea;
    sumArea.push_back(std::accumulate(areas.begin(), areas.end(), farea()));
    std::copy(sumArea.begin(), sumArea.end(), outIter(std::cout, "\n"));
  }

  void runMean(const vecPol& res)
  {
    vecPol data = res;
    size_t quntity = res.size();
    vecFArea areas = getFullArea(data.begin(), data.end());
    vecFArea sumArea;
    sumArea.push_back(std::accumulate(areas.begin(), areas.end(), farea()));
    sumArea.begin()->res /= quntity;
    std::copy(sumArea.begin(), sumArea.end(), outIter(std::cout, "\n"));
  }

  void runAreaNumOfVertexes(const vecPol& res, const std::string& num)
  {
    vecPol data = res;
    size_t count = std::stoull(num);
    vecPol::iterator it = std::partition(data.begin(), data.end(), std::bind(isEqual, _1, count));
    vecFArea areas = getFullArea(data.begin(), it);
    vecFArea sumArea;
    sumArea.push_back(std::accumulate(areas.begin(), areas.end(), farea()));
    std::copy(sumArea.begin(), sumArea.end(), outIter(std::cout, "\n"));
  }

  void runArea(std::istream& inp, std::string& command, const vecPol& res)
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
      std::cout << "<INVALID COMMAND>";
    }
  }

  void runMaxArea(const vecPol& res)
  {
    vecPol data = res;
    std::sort(data.begin(), data.end());
    vecFArea areas = getFullArea(--data.end(), data.end());
    std::copy(areas.begin(), areas.end(), outIter(std::cout, "\n"));
  }

  void runMacVertexes(const vecPol& res)
  {
    vecPol data = res;
    std::sort(data.begin(), data.end());
    vecPol::iterator it = --data.end();
    std::cout << it->points.size() << "\n";
  }

  void runMax(std::istream& inp, std::string& command, const std::vector< mashkin::Polygon >& data)
  {
    inp >> command;
    if (command == "AREA")
    {
      runMaxArea(data);
    }
    else if (command == "VERTEXES")
    {
      runMacVertexes(data);
    }
    else
    {
      std::cout << "<INVALID COMMAND>";
    }
  }

  void runCommand(std::istream& inp, std::string& command, const std::vector< Polygon >& res)
  {
    inp >> command;
    if (command == "AREA")
    {
      runArea(inp, command, res);
    }
    else if (command == "MAX")
    {
      runMax(inp, command, res);
    }
    /*else if (command == "MIN")
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
