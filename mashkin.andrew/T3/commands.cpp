#include "commands.h"
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <iterator>
#include <limits>
#include <numeric>
#include <stdexcept>
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

  constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();

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

  void runArea(std::istream& inp, const vecPol& res)
  {
    std::string command;
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
        throw std::logic_error("Logic error");
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
        throw std::logic_error("Logic error");
      }
      else
      {
        runAreaNumOfVertexes(res, command);
      }
    }
    else
    {
      throw std::logic_error("Logic error");
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

  void runMax(std::istream& inp, const std::vector< mashkin::Polygon >& data)
  {
    std::string command;
    inp >> command;
    if (data.empty())
    {
      throw std::logic_error("Logic error");
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
      throw std::logic_error("Logic error");
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

  void runMin(std::istream& inp, const vecPol& res)
  {
    std::string command;
    inp >> command;
    if (res.empty())
    {
      throw std::logic_error("Logic error");
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
      throw std::logic_error("Logic error");
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

  void runCount(std::istream& inp, const vecPol& res)
  {
    std::string command;
    inp >> command;
    if (command == "EVEN")
    {
      if (res.empty())
      {
        std::cout << 0 << "\n";
      }
      else
      {
        runCountEven(res);
      }
    }
    else if (command == "ODD")
    {
      if (res.empty())
      {
        std::cout << 0 << "\n";
      }
      else
      {
        runCountOdd(res);
      }
    }
    else if (command.find_first_not_of("0123456789") == std::string::npos)
    {
      if (command == "0" || command == "1" || command == "2")
      {
        throw std::logic_error("Logic error");
      }
      else
      {
        runCountNumOfVertexes(res, command);
      }
    }
    else
    {
      throw std::logic_error("Logic error");
    }
  }

  void runPerms(std::istream& inp, const vecPol& res)
  {
    vecPol data = res;
    Polygon comp;
    inp >> comp;
    if (inp.fail())
    {
      inp.clear();
      throw std::logic_error("Logic error");
    }
    std::sort(comp.points.begin(), comp.points.end());
    size_t quantity = 0;
    quantity = std::count_if(data.begin(), data.end(), std::bind(isEqualPoints, _1, comp));
    std::cout << quantity << "\n";
  }

  void runRightshapes(std::istream&, const vecPol& res)
  {
    vecPol data = res;
    std::vector< Angle > angles;
    std::transform(data.begin(), data.end(), std::back_inserter(angles), getAngle);
    size_t quatity = std::count_if(angles.begin(), angles.end(), isRightshapes);
    std::cout << quatity << "\n";
  }
}
