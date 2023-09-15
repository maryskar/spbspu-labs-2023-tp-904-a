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
  constexpr auto maxSize = std::numeric_limits< std::streamsize >::max();

  template< class P >
  std::ostream& runEvenOrOdd(const std::deque< Polygon > res, std::ostream& out, P p)
  {
    std::deque< Polygon > data = res;
    std::deque< Polygon >::iterator it = std::partition(data.begin(), data.end(), p);
    std::vector< FullArea > areas = getFullArea(data.begin(), it);
    return out << std::accumulate(areas.begin(), areas.end(), FullArea());
  }

  std::ostream& runEven(const std::deque< Polygon >& res, std::ostream& out)
  {
    return runEvenOrOdd(res, out, isEven);
  }

  std::ostream& runOdd(const std::deque< Polygon >& res, std::ostream& out)
  {
    return runEvenOrOdd(res, out, isOdd);
  }

  std::ostream& runMean(const std::deque< Polygon >& res, std::ostream& out)
  {
    std::deque< Polygon > data = res;
    size_t quantity = res.size();
    std::vector< FullArea > areas = getFullArea(data.begin(), data.end());
    FullArea sumArea;
    sumArea.res = std::accumulate(areas.begin(), areas.end(), FullArea()).res / quantity;
    return out << sumArea;
  }

  std::ostream& runAreaNumOfVertexes(const std::deque< Polygon >& res, std::ostream& out, const std::string& num)
  {
    std::deque< Polygon > data = res;
    size_t count = std::stoull(num);
    std::deque< Polygon >::iterator it = std::partition(data.begin(), data.end(), std::bind(isEqual, _1, count));
    std::vector< FullArea > areas = getFullArea(data.begin(), it);
    return out << std::accumulate(areas.begin(), areas.end(), FullArea());
  }

  void runArea(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res)
  {
    std::string command;
    inp >> command;
    if (command == "EVEN")
    {
      runEven(res, out) << "\n";
    }
    else if (command == "ODD")
    {
      runOdd(res, out) << "\n";
    }
    else if (command == "MEAN")
    {
      if (res.empty())
      {
        throw std::logic_error("Logic error");
      }
      else
      {
        runMean(res, out) << "\n";
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
        runAreaNumOfVertexes(res, out, command) << "\n";
      }
    }
    else
    {
      throw std::logic_error("Logic error");
    }
  }

  std::vector< FullArea > runMaxOrMinArea(const std::deque< Polygon >& res)
  {
    std::deque< Polygon > data = res;
    std::vector< FullArea > areas = getFullArea(data.begin(), data.end());
    std::sort(areas.begin(), areas.end());
    return areas;
  }

  std::ostream& runMaxArea(const std::deque< Polygon >& res, std::ostream& out)
  {
    return out << *(--runMaxOrMinArea(res).end());
  }

  std::ostream& runMinArea(const std::deque< Polygon >& res, std::ostream& out)
  {
    return out << *runMaxOrMinArea(res).begin();
  }

  std::deque< Polygon > runMaxOrMinVertexes(const std::deque< Polygon >& res)
  {
    std::deque< Polygon > data = res;
    std::sort(data.begin(), data.end());
    return data;
  }

  std::ostream& runMaxVertexes(const std::deque< Polygon >& res, std::ostream& out)
  {
    return out << (--runMaxOrMinVertexes(res).end())->points.size();
  }

  std::ostream& runMinVertexes(const std::deque< Polygon >& res, std::ostream& out)
  {
    return out << runMaxOrMinVertexes(res).begin()->points.size();
  }

  template< class AreaFunc, class VertexesFunc >
  void runMinOrMax(AreaFunc areaFunc, VertexesFunc vertexesFunc, std::istream& inp,
      std::ostream& out, const std::deque< Polygon >& data )
  {
    std::string command;
    inp >> command;
    if (data.empty())
    {
      throw std::logic_error("Logic error");
    }
    else if (command == "AREA")
    {
      areaFunc(data, out) << "\n";
    }
    else if (command == "VERTEXES")
    {
      vertexesFunc(data, out) << "\n";
    }
    else
    {
      throw std::logic_error("Logic error");
    }
  }

  void runMax(std::istream& inp, std::ostream& out, const std::deque< Polygon >& data)
  {
    runMinOrMax(runMaxArea, runMaxVertexes, inp, out, data);
  }

  void runMin(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res)
  {
    runMinOrMax(runMinArea, runMinVertexes, inp, out, res);
  }

  std::ostream& runCountEven(const std::deque< Polygon >& res, std::ostream& out)
  {
    return out << std::count_if(res.begin(), res.end(), isEven);
  }

  std::ostream& runCountOdd(const std::deque< Polygon >& res, std::ostream& out)
  {
    return out << std::count_if(res.begin(), res.end(), isOdd);
  }

  std::ostream& runCountNumOfVertexes(const std::deque< Polygon >& res, std::ostream& out, const std::string& command)
  {
    std::deque< Polygon > data = res;
    size_t count = std::stoull(command);
    size_t quantity = std::count_if(data.begin(), data.end(), std::bind(isEqual, _1, count));
    std::cout << quantity;
    return out;
  }

  void runCount(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res)
  {
    std::string command;
    inp >> command;
    if (command == "EVEN")
    {
      if (res.empty())
      {
        out << 0 << "\n";
      }
      else
      {
        runCountEven(res, out) << "\n";
      }
    }
    else if (command == "ODD")
    {
      if (res.empty())
      {
        out << 0 << "\n";
      }
      else
      {
        runCountOdd(res, out) << "\n";
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
        runCountNumOfVertexes(res, out, command) << "\n";
      }
    }
    else
    {
      throw std::logic_error("Logic error");
    }
  }

  void runPerms(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res)
  {
    std::deque< Polygon > data = res;
    Polygon comp;
    inp >> comp;
    if (inp.fail())
    {
      throw std::logic_error("Logic error");
    }
    std::sort(comp.points.begin(), comp.points.end());
    size_t quantity = 0;
    quantity = std::count_if(data.begin(), data.end(), std::bind(isEqualPoints, _1, comp));
    out << quantity << "\n";
  }

  void runRightShapes(std::istream&, std::ostream& out, const std::deque< Polygon >& res)
  {
    out << std::count_if(res.begin(), res.end(), isRightShapes) << "\n";
  }
}
