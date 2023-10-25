#include "CommandHandler.h"
#include <list>
#include <numeric>
#include <iomanip>
#include <algorithm>
#include <IOFmtGuard.h>

namespace nesterov
{
  bool hasEvenVertexes(const Polygon &polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool hasOddVertexes(const Polygon &polygon)
  {
    return !hasEvenVertexes(polygon);
  }

  double getAreaHelper(const Point &point1, const Point &point2)
  {
    return point1.x * point2.y - point2.x * point1.y;
  }

  double getArea(const Polygon &polygon)
  {
    std::vector< double > area(polygon.points.size());

    std::transform(
      polygon.points.begin(),
      polygon.points.end() - 1,
      polygon.points.begin() + 1,
      area.begin(),
      getAreaHelper
    );

    double sum = std::accumulate(area.begin(), area.end(), 0.0);
    sum += getAreaHelper(polygon.points.back(), polygon.points.front());

    return 0.5 * std::abs(sum);
  }

  bool hasNVertexes(const Polygon &polygon, size_t vertexes)
  {
    return polygon.points.size() == vertexes;
  }

  double getAreaOddFun(double area, const Polygon &polygon)
  {
    if (!hasOddVertexes(polygon))
    {
      return area;
    }
    return area + getArea(polygon);
  }

  double getAreaEvenFun(double area, const Polygon &polygon)
  {
    if (!hasEvenVertexes(polygon))
    {
      return area;
    }
    return area + getArea(polygon);
  }

  size_t getVertexes(const Polygon &polygon)
  {
    return polygon.points.size();
  }

  double getAreaFun(double area, const Polygon &polygon)
  {
    return area + getArea(polygon);
  }

  double getAreaWithVertexesFun(double area, const Polygon &polygon, size_t vertexes)
  {
    if (getVertexes(polygon) != vertexes)
    {
      return area;
    }
    return area + getArea(polygon);
  }

  void printAreaOdd(const std::deque< Polygon > &pls, std::ostream &out)
  {
    double area = std::accumulate(
      pls.begin(),
      pls.end(),
      0.0,
      getAreaOddFun
    );
    IOFmtGuard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << area << '\n';
  }

  void printAreaMean(const std::deque< Polygon > &pls, std::ostream &out)
  {
    if (pls.empty())
    {
      throw std::logic_error("");
    }

    double area = std::accumulate(
      pls.begin(),
      pls.end(),
      0.0,
      getAreaFun
    );

    double meanArea = area / static_cast< double >(pls.size());

    IOFmtGuard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << meanArea << '\n';
  }

  void printAreaWithVertexes(const std::deque< Polygon > &pls, std::ostream &out, size_t vertexes)
  {
    if (vertexes < 3)
    {
      throw std::logic_error("");
    }
    auto fun = std::bind(
      getAreaWithVertexesFun,
      std::placeholders::_1,
      std::placeholders::_2,
      vertexes
    );
    double area = std::accumulate(
      pls.begin(),
      pls.end(),
      0.0,
      fun
    );
    IOFmtGuard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << area << '\n';
  }

  void printAreaEven(const std::deque< Polygon > &pls, std::ostream &out)
  {
    double area = std::accumulate(
      pls.begin(),
      pls.end(),
      0.0,
      getAreaEvenFun
    );
    IOFmtGuard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << area << '\n';
  }

  void printMaxVertexes(const std::deque< Polygon > &pls, std::ostream &out)
  {
    if (pls.empty())
    {
      throw std::logic_error("");
    }
    std::deque< size_t > vertexes(pls.size());
    std::transform(pls.begin(), pls.end(), vertexes.begin(), getVertexes);
    auto maxVertexesIterator = std::max_element(vertexes.begin(), vertexes.end());
    out << *maxVertexesIterator << '\n';
  }

  void printMaxArea(const std::deque< Polygon > &pls, std::ostream &out)
  {
    if (pls.empty())
    {
      throw std::logic_error("");
    }
    std::deque< double > areas(pls.size());
    std::transform(pls.begin(), pls.end(), areas.begin(), getArea);
    auto maxAreaIterator = std::max_element(areas.begin(), areas.end());
    IOFmtGuard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << *maxAreaIterator << '\n';
  }

  void printMinVertexes(const std::deque< Polygon > &pls, std::ostream &out)
  {
    if (pls.empty())
    {
      throw std::logic_error("");
    }
    std::deque< size_t > vertexes(pls.size());
    std::transform(pls.begin(), pls.end(), vertexes.begin(), getVertexes);
    auto minVertexesIterator = std::min_element(vertexes.begin(), vertexes.end());
    out << *minVertexesIterator << '\n';
  }

  void printMinArea(const std::deque< Polygon > &pls, std::ostream &out)
  {
    if (pls.empty())
    {
      throw std::logic_error("");
    }
    std::deque< double > areas(pls.size());
    std::transform(pls.begin(), pls.end(), areas.begin(), getArea);
    auto minAreaIterator = std::min_element(areas.begin(), areas.end());
    IOFmtGuard iofmtguard(out);
    out << std::fixed << std::setprecision(1) << *minAreaIterator << '\n';
  }

  void countEven(const std::deque< Polygon > &pls, std::ostream &out)
  {
    size_t even = std::count_if(pls.cbegin(), pls.cend(), hasEvenVertexes);
    out << even << '\n';
  }

  void countOdd(const std::deque< Polygon > &pls, std::ostream &out)
  {
    size_t odd = std::count_if(pls.cbegin(), pls.cend(), hasOddVertexes);
    out << odd << '\n';
  }

  void countWithNVertexes(const std::deque< Polygon > &pls, std::ostream &out, size_t vertexes)
  {
    if (vertexes < 3)
    {
      throw std::logic_error("");
    }
    auto predicate = std::bind(hasNVertexes, std::placeholders::_1, vertexes);
    auto n = std::count_if(pls.begin(), pls.end(), predicate);
    out << n << '\n';
  }

  void executeAreaCommand(const std::deque< Polygon > &pls, std::istream &in, std::ostream &out)
  {
    std::string subcommand;
    if (in >> subcommand)
    {
      if (subcommand == "EVEN")
      {
        printAreaEven(pls, out);
      }
      else if (subcommand == "ODD")
      {
        printAreaOdd(pls, out);
      }
      else if (subcommand == "MEAN")
      {
        printAreaMean(pls, out);
      }
      else
      {
        size_t vertexes = std::stoull(subcommand);
        printAreaWithVertexes(pls, out, vertexes);
      }
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeMaxCommand(const std::deque< Polygon > &pls, std::istream &in, std::ostream &out)
  {
    std::string subcommand;
    if (in >> subcommand)
    {
      if (subcommand == "AREA")
      {
        printMaxArea(pls, out);
      }
      else if (subcommand == "VERTEXES")
      {
        printMaxVertexes(pls, out);
      }
      else
      {
        throw std::logic_error("");
      }
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeMinCommand(const std::deque< Polygon > &pls, std::istream &in, std::ostream &out)
  {
    std::string subcommand;
    if (in >> subcommand)
    {
      if (subcommand == "AREA")
      {
        printMinArea(pls, out);
      }
      else if (subcommand == "VERTEXES")
      {
        printMinVertexes(pls, out);
      }
      else
      {
        throw std::logic_error("");
      }
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeCountCommand(const std::deque< Polygon > &pls, std::istream &in, std::ostream &out)
  {
    std::string subcommand;
    if (in >> subcommand)
    {
      if (subcommand == "EVEN")
      {
        countEven(pls, out);
      }
      else if (subcommand == "ODD")
      {
        countOdd(pls, out);
      }
      else
      {
        size_t vertexes = std::stoull(subcommand);
        countWithNVertexes(pls, out, vertexes);
      }
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeMaxSeqCommand(const std::deque< Polygon > &pls, std::istream &in, std::ostream &out)
  {
    Polygon input;
    if (in >> input)
    {
      std::string remaining;
      std::getline(in, remaining, ')');
      if (!remaining.empty())
      {
        throw std::logic_error("");
      }
      size_t max = 0;
      auto i = std::find(pls.begin(), pls.end(), input);
      while (i != pls.end())
      {
        auto j = std::adjacent_find(i, pls.end(), std::not_equal_to< Polygon >());
        size_t distance = std::distance(i, j);
        if (j == pls.end())
        {
          max = std::max(max, distance);
          break;
        }
        max = std::max(max, distance + 1);
        i = std::find(std::next(j), pls.end(), input);
      }

      out << max << '\n';
    }
    else
    {
      throw std::logic_error("");
    }
  }

  void executeEchoCommand(std::deque< Polygon > &pls, std::istream &in, std::ostream &out)
  {
    Polygon input;
    if (in >> input)
    {
      std::string remaining;
      std::getline(in, remaining, ')');
      if (!remaining.empty())
      {
        throw std::logic_error("");
      }
      std::list< Polygon > list(pls.begin(), pls.end());
      size_t inserted = 0;

      auto foundIterator = std::find(list.begin(), list.end(), input);
      while (foundIterator != list.end())
      {
        auto insertedIterator = list.insert(std::next(foundIterator), input);
        ++inserted;
        foundIterator = std::find(std::next(insertedIterator), list.end(), input);
      }

      pls.assign(list.begin(), list.end());
      out << inserted << '\n';
    }
    else
    {
      throw std::logic_error("");
    }
  }
}
