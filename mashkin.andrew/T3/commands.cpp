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
    if (res.empty())
    {
      throw std::logic_error("Logic error");
    }
    std::deque< Polygon > data = res;
    size_t quantity = res.size();
    std::vector< FullArea > areas = getFullArea(data.begin(), data.end());
    FullArea sumArea;
    sumArea.res = std::accumulate(areas.begin(), areas.end(), FullArea()).res / quantity;
    return out << sumArea;
  }

  std::ostream& runAreaNumOfVertexes(const std::deque< Polygon >& res, std::ostream& out, const std::string& num)
  {
    if (num == "0" || num == "1" || num == "2")
    {
      throw std::logic_error("Logic error");
    }
    std::deque< Polygon > data = res;
    size_t count = std::stoull(num);
    std::deque< Polygon >::iterator it = std::partition(data.begin(), data.end(), std::bind(isEqual, _1, count));
    std::vector< FullArea > areas = getFullArea(data.begin(), it);
    return out << std::accumulate(areas.begin(), areas.end(), FullArea());
  }

  std::ostream& runArea(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res)
  {
    std::string command;
    inp >> command;
    if (command == "EVEN")
    {
      runEven(res, out);
    }
    else if (command == "ODD")
    {
      runOdd(res, out);
    }
    else if (command == "MEAN")
    {
      runMean(res, out);
    }
    else if (command.find_first_not_of("0123456789") == std::string::npos)
    {
      runAreaNumOfVertexes(res, out, command);
    }
    else
    {
      throw std::logic_error("Logic error");
    }
    return out;
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
  std::ostream& runMinOrMax(AreaFunc areaFunc, VertexesFunc vertexesFunc, std::istream& inp,
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
      areaFunc(data, out);
    }
    else if (command == "VERTEXES")
    {
      vertexesFunc(data, out);
    }
    else
    {
      throw std::logic_error("Logic error");
    }
    return out;
  }

  std::ostream& runMax(std::istream& inp, std::ostream& out, const std::deque< Polygon >& data)
  {
    return runMinOrMax(runMaxArea, runMaxVertexes, inp, out, data);
  }

  std::ostream& runMin(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res)
  {
    return runMinOrMax(runMinArea, runMinVertexes, inp, out, res);
  }

  template< class P >
  std::ostream& runCountEvenOrOdd(const std::deque< Polygon >& res, std::ostream& out, P p)
  {
    if (res.empty())
    {
      return out << 0;
    }
    return out << std::count_if(res.begin(), res.end(), p);
  }

  std::ostream& runCountEven(const std::deque< Polygon >& res, std::ostream& out)
  {
    return runCountEvenOrOdd(res, out, isEven);
  }

  std::ostream& runCountOdd(const std::deque< Polygon >& res, std::ostream& out)
  {
    return runCountEvenOrOdd(res, out, isOdd);
  }

  std::ostream& runCountNumOfVertexes(const std::deque< Polygon >& res, std::ostream& out, const std::string& command)
  {
    if (command == "0" || command == "1" || command == "2")
    {
      throw std::logic_error("Logic error");
    }
    return out << std::count_if(res.begin(), res.end(), std::bind(isEqual, _1, std::stoull(command)));
  }

  std::ostream& runCount(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res)
  {
    std::string command;
    inp >> command;
    if (command == "EVEN")
    {
      runCountEven(res, out);
    }
    else if (command == "ODD")
    {
      runCountOdd(res, out);
    }
    else if (command.find_first_not_of("0123456789") == std::string::npos)
    {
       runCountNumOfVertexes(res, out, command);
    }
    else
    {
      throw std::logic_error("Logic error");
    }
    return out;
  }

  std::ostream& runPerms(std::istream& inp, std::ostream& out, const std::deque< Polygon >& res)
  {
    std::deque< Polygon > data = res;
    Polygon comp;
    inp >> comp;
    if (inp.fail())
    {
      throw std::logic_error("Logic error");
    }
    std::sort(comp.points.begin(), comp.points.end());
    return out << std::count_if(data.begin(), data.end(), std::bind(isEqualPoints, _1, comp));
  }

  std::ostream& runRightShapes(std::istream&, std::ostream& out, const std::deque< Polygon >& res)
  {
    return out << std::count_if(res.begin(), res.end(), isRightShapes);
  }
}
