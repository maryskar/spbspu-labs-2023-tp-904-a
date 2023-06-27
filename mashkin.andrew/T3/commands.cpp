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
  */
  void runMin(std::istream& inp, std::string& command, const vecPol& res);
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
      if (res.empty())
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      else
      {
        runMean(res);
      }
    }
    else if (command.find_first_not_of("0123456789") == std::string::npos)
    {
      if (command == "0" || command == "1" || command == "2")
      {
        std::cout << "<INVALID COMMAND>\n";
      }
      else
      {
        runAreaNumOfVertexes(res, command);
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  void runMaxArea(const vecPol& res)
  {
    vecPol data = res;
    vecFArea areas = getFullArea(data.begin(), data.end());
    std::sort(areas.begin(), areas.end());
    std::copy(--areas.end(), areas.end(), outIter(std::cout, "\n"));
  }

  void runMaxVertexes(const vecPol& res)
  {
    vecPol data = res;
    std::sort(data.begin(), data.end());
    vecPol::iterator it = --data.end();
    std::cout << it->points.size() << "\n";
  }

  void runMax(std::istream& inp, std::string& command, const std::vector< mashkin::Polygon >& data)
  {
    inp >> command;
    if (data.empty())
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    else if (command == "AREA")
    {
      runMaxArea(data);
    }
    else if (command == "VERTEXES")
    {
      runMaxVertexes(data);
    }
    else
    {
      std::cout << "<INVALID COMMAND>";
    }
  }

  void runMinArea(const vecPol& res)
  {
    vecPol data = res;
    vecFArea areas = getFullArea(data.begin(), data.end());
    std::sort(areas.begin(), areas.end());
    std::copy(areas.begin(), ++areas.begin(), outIter(std::cout, "\n"));
  }

  void runMinVertexes(const vecPol& res)
  {
    vecPol data = res;
    std::sort(data.begin(), data.end());
    vecPol::iterator it = data.begin();
    std::cout << it->points.size() << "\n";
  }

  void runMin(std::istream& inp, std::string& command, const vecPol& res)
  {
    inp >> command;
    if (res.empty())
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    else if (command == "AREA")
    {
      runMinArea(res);
    }
    else if (command == "VERTEXES")
    {
      runMinVertexes(res);
    }
    else
    {
      std::cout << "<INVALID COMMAND>";
    }
  }

  void runCountEven(const vecPol& res)
  {
    vecPol data = res;
    size_t quantity = std::count_if(data.begin(), data.end(), isEven);
    std::cout << quantity << "\n";
  }

  void runCountOdd(const vecPol& res)
  {
    vecPol data = res;
    size_t quantity = std::count_if(data.begin(), data.end(), isOdd);
    std::cout << quantity << "\n";
  }

  void runCountNumOfVertexes(const vecPol& res, const std::string& command)
  {
    vecPol data = res;
    size_t count = std::stoull(command);
    size_t quantity = std::count_if(data.begin(), data.end(), std::bind(isEqual, _1, count));
    std::cout << quantity << "\n";
  }

  void runCount(std::istream& inp, std::string& command, const vecPol& res)
  {
    inp >> command;
    if (res.empty())
    {
      std::cout << "<INVALID COMMAND>\n";
    }
    else if (command == "EVEN")
    {
      runCountEven(res);
    }
    else if (command == "ODD")
    {
      runCountOdd(res);
    }
    else if (command.find_first_not_of("0123456789") == std::string::npos)
    {
      runCountNumOfVertexes(res, command);
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
    else if (command == "MIN")
    {
      runMin(inp, command, res);
    }
    else if (command == "COUNT")
    {
      runCount(inp, command, res);
    }
    /*else if (command == "PERMS")
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
