#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <numeric>
#include "polygon.h"
using namespace std::placeholders;
using Polygon = romanovich::Polygon;
namespace
{
  std::vector< Polygon >::const_iterator findMinMixEl(const std::vector< Polygon > &polygons,
                                                      const std::function< bool(const Polygon &,
                                                                                const Polygon &) > &comp)
  {
    auto result = std::minmax_element(polygons.begin(), polygons.end(), comp);
    return comp(*result.second, *result.first) ? result.second : result.first;
  }
  std::vector< double > makeAreasVector(const std::vector< Polygon > &polygons)
  {
    std::vector< double > areas;
    areas.resize(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), romanovich::Polygon::AreaFunctor());
    return areas;
  }
  bool isAreaOdd(double area)
  {
    return (static_cast<int>(area) % 2 != 0);
  }
  void rightShapesCountCommand(const std::vector< Polygon > &polygons)
  {
    size_t count = 0;
    for (const auto &polygon: polygons)
    {
      bool hasRightAngle = false;
      size_t n = polygon.getPointsCount();
      for (std::size_t i = 0; i < n; ++i)
      {
        const auto &pointA = polygon.getPoint(i);
        const auto &pointB = polygon.getPoint((i + 1) % n);
        const auto &pointC = polygon.getPoint((i + 2) % n);
        const auto v1 = pointB - pointA;
        const auto v2 = pointC - pointB;
        if (doScalarMultiplication(v1, v2) == 0)
        {
          hasRightAngle = true;
          break;
        }
      }
      if (hasRightAngle)
      {
        ++count;
      }
    }
    std::cout << count << '\n';
  }
  void maxSeqCommand(const std::vector< Polygon > &polygons, const Polygon &polygon)
  {
    if (polygons.empty())
    {
      std::cerr << "No polygons.\n";
      return;
    }
    auto notComp = std::bind(std::negate<>(), std::bind(Polygon::PolygonComparator(polygon), _1, _2));
    const auto maxSeq = std::adjacent_find(polygons.begin(), polygons.end(), notComp);
    if (maxSeq == polygons.end())
    {
      std::cout << "0\n";
    }
    else
    {
      const auto start = maxSeq;
      const auto end = std::adjacent_find(maxSeq + 1, polygons.end(), notComp);
      const auto count = end - start;
      std::cout << count << '\n';
    }
  }
  void countCommand(const std::vector< Polygon > &polygons, const std::string &param)
  {
    if (polygons.empty())
    {
      std::cerr << "No polygons.\n";
      return;
    }
    size_t count = 0;
    if (param == "EVEN")
    {
      count = std::count_if(polygons.begin(), polygons.end(), Polygon::IsEvenVertexCount{});
    }
    else if (param == "ODD")
    {
      count = std::count_if(polygons.begin(), polygons.end(), Polygon::IsOddVertexCount{});
    }
    std::cout << count << '\n';
  }
  void countCommand(const std::vector< Polygon > &polygons, size_t vertexCount)
  {
    if (polygons.empty())
    {
      std::cerr << "No polygons.\n";
      return;
    }
    size_t count = 0;
    try
    {
      count = std::count_if(polygons.begin(), polygons.end(), Polygon::HasVertexCount{vertexCount});
    }
    catch (...)
    {
      std::cerr << "Error: invalid parameter\n";
      return;
    }
    std::cout << count << '\n';
  }
  /*void maxCommand(const std::vector< Polygon > &polygons, const std::string &param)
  {
    if (polygons.empty())
    {
      std::cerr << "No polygons.\n";
      return;
    }
    if (param == "AREA")
    {
      ///const auto maxIt = std::max_element(polygons.begin(), polygons.end(), Polygon::AreaComp{});
      ///const auto i = std::distance(polygons.begin(), maxIt);
      ///std::cout << std::fixed << std::setprecision(1) << polygons[i].getArea() << '\n';
      auto areaCompNegate = std::bind(std::logical_not<>(), std::bind(Polygon::AreaComp{}, _1, _2));
      const auto maxIt = findMinMixEl(polygons, areaCompNegate);
      const auto i = std::distance(polygons.begin(), maxIt);
      std::cout << std::fixed << std::setprecision(1) << polygons[i].getArea() << '\n';
    }
    else if (param == "VERTEXES")
    {
      ///const auto maxIt = std::max_element(polygons.begin(), polygons.end(), Polygon::PointsCountComp{});
      ///const auto i = std::distance(polygons.begin(), maxIt);
      ///std::cout << polygons[i].getPointsCount() << '\n';
      auto pointsCompNegate = std::bind(std::logical_not<>(),
                                        std::bind(Polygon::PointsCountComp{}, _1, _2));
      const auto maxIt = findMinMixEl(polygons, pointsCompNegate);
      const auto i = std::distance(polygons.begin(), maxIt);
      std::cout << std::fixed << std::setprecision(1) << polygons[i].getArea() << '\n';
    }
  }
  void minCommand(const std::vector< Polygon > &polygons, const std::string &param)
  {
    if (polygons.empty())
    {
      std::cerr << "No polygons.\n";
      return;
    }
    if (param == "AREA")
    {
      ///const auto maxIt = std::min_element(polygons.begin(), polygons.end(), Polygon::AreaComp{});
      ///const auto i = std::distance(polygons.begin(), maxIt);
      ///std::cout << std::fixed << std::setprecision(1) << polygons[i].getArea() << '\n';
      const auto minEl = findMinMixEl(polygons, Polygon::AreaComp{});
      const auto i = std::distance(polygons.begin(), minEl);
      std::cout << std::fixed << std::setprecision(1) << polygons[i].getArea() << '\n';
    }
    else if (param == "VERTEXES")
    {
      ///const auto maxIt = std::min_element(polygons.begin(), polygons.end(), Polygon::PointsCountComp{});
      ///const auto i = std::distance(polygons.begin(), maxIt);
      ///std::cout << polygons[i].getPointsCount() << '\n';
      const auto minEl = findMinMixEl(polygons, Polygon::PointsCountComp{});
      const auto i = std::distance(polygons.begin(), minEl);
      std::cout << std::fixed << std::setprecision(1) << polygons[i].getPointsCount() << '\n';
    }
  }*/
  /*void areaCommand(const std::vector< Polygon > &polygons, const std::string &param)
  {
    double sum = 0;
    size_t count = 0;
    for (const auto &polygon: polygons)
    {
      if (param == "MEAN" || polygon.getPointsCount() % 2 == (param == "EVEN"))
      {
        sum += polygon.getArea();
        ++count;
      }
    }
    if (param == "MEAN")
    {
      sum /= count;
    }
    std::cout << std::fixed << std::setprecision(1) << sum << '\n';
  }*/
  void areaCommand(const std::vector< Polygon > &polygons, size_t verticesCount)
  {
    double sum = 0;
    for (const auto &polygon: polygons)
    {
      if (polygon.getPointsCount() == verticesCount)
      {
        sum += polygon.getArea();
      }
    }
    std::cout << std::fixed << std::setprecision(1) << sum << '\n';
  }
}
void executeCommand(const std::vector< Polygon > &polygons, const std::string &command)
{
  const auto areaComp = static_cast<const std::function< bool(const Polygon &,
                                                              const Polygon &) > &>(Polygon::AreaComp{});
  const auto areaCompNegate = std::bind(std::logical_not<>(), std::bind(areaComp, _1, _2));
  //
  //
  const auto pointsComp = static_cast<const std::function< bool(const Polygon &,
                                                                const Polygon &) > &>(Polygon::PointsCountComp{});
  const auto pointsCompNegate = std::bind(std::logical_not<>(), std::bind(pointsComp, _1, _2));
  //
  //
  if (command == "MAX AREA" || command == "MIN AREA")
  {
    const auto elIt = findMinMixEl(polygons, (command == "MIN AREA") ? areaComp : areaCompNegate);
    const auto i = std::distance(polygons.begin(), elIt);
    std::cout << std::fixed << std::setprecision(1) << polygons[i].getArea() << '\n';
  }
  else if (command == "MAX VERTEXES" || command == "MIN VERTEXES")
  {
    const auto elIt = findMinMixEl(polygons, (command == "MIN VERTEXES") ? pointsComp : pointsCompNegate);
    const auto i = std::distance(polygons.begin(), elIt);
    std::cout << polygons[i].getPointsCount() << '\n';
  }
  else if (command == "AREA MEAN" || command == "AREA ODD" || command == "AREA EVEN")
  {
    std::vector< double > areas = makeAreasVector(polygons);
    auto it = std::partition(areas.begin(), areas.end(), isAreaOdd);
    double sumOdd = std::accumulate(areas.begin(), it, 0.0);
    double sumEven = std::accumulate(it, areas.end(), 0.0);
    double sumMean = std::accumulate(areas.begin(), areas.end(), 0.0) / static_cast< double >(areas.size());
    if (command == "AREA MEAN")
    {
      std::cout << std::fixed << std::setprecision(1) << sumMean << '\n';
    }
    else if (command == "AREA ODD")
    {
      std::cout << std::fixed << std::setprecision(1) << sumOdd << '\n';
    }
    else if (command == "AREA EVEN")
    {
      std::cout << std::setprecision(1) << sumEven << '\n';
    }
  }
  else if (command == "AREA MEAN" || command == "AREA ODD" || command == "AREA EVEN")
  {
    std::vector< double > areas = makeAreasVector(polygons);
    auto it = std::partition(areas.begin(), areas.end(), isAreaOdd);
    double sumOdd = std::accumulate(areas.begin(), it, 0.0);
    double sumEven = std::accumulate(it, areas.end(), 0.0);
    double sumMean = std::accumulate(areas.begin(), areas.end(), 0.0) / static_cast< double >(areas.size());
    if (command == "AREA MEAN")
    {
      std::cout << std::fixed << std::setprecision(1) << sumMean << '\n';
    }
    else if (command == "AREA ODD")
    {
      std::cout << std::fixed << std::setprecision(1) << sumOdd << '\n';
    }
    else if (command == "AREA EVEN")
    {
      std::cout << std::setprecision(1) << sumEven << '\n';
    }///////////////[AREA <num-of-vertexes>] Расчёт суммы площади фигур с заданным количеством вершин
  }
}
void processCommand(std::vector< Polygon > &polygons, const std::string &command)
{
  /*if (command == "AREA")
  {
    std::string param;
    std::cin >> param;
    if (param == "EVEN" || param == "ODD" || param == "MEAN")
    {
      areaCommand(polygons, param);
    }
    else
    {
      try
      {
        areaCommand(polygons, std::stoi(param));
      }
      catch (...)
      {
        std::cerr << "<INVALID PARAMETER>\n";
      }
    }
  }*/
  /*else if (command == "MAX")
  {
    std::string param;
    std::cin >> param;
    if (param == "AREA" || param == "VERTEXES")
    {
      maxCommand(polygons, param);
    }
    else
    {
      std::cerr << "<INVALID PARAMETER>\n";
    }
  }
  else if (command == "MIN")
  {
    std::string param;
    std::cin >> param;
    if (param == "AREA" || param == "VERTEXES")
    {
      minCommand(polygons, param);
    }
    else
    {
      std::cerr << "<INVALID PARAMETER>\n";
    }
  }*/
  if (command == "COUNT")
  {
    std::string param;
    std::cin >> param;
    if (param == "EVEN" || param == "ODD")
    {
      countCommand(polygons, param);
    }
    else
    {
      try
      {
        countCommand(polygons, std::stoul(param));
      }
      catch (...)
      {
        std::cerr << "<INVALID PARAMETER>\n";
      }
    }
  }
  else if (command == "MAXSEQ")
  {
    try
    {
      std::vector< romanovich::Point > points;
      size_t pointsCount;
      std::istream &input = std::cin;
      while (input >> pointsCount)
      {
        if (input.fail())
        {
          input.clear();
          input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
          continue;
        }
        for (size_t i = 0; i < pointsCount; i++)
        {
          romanovich::Point point{};
          input >> point;
          if (input.fail())
          {
            input.clear();
            input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
            break;
          }
          points.push_back(point);
        }
        maxSeqCommand(polygons, Polygon(points));
      }
    }
    catch (...)
    {
      std::cerr << "<INVALID PARAMETER>\n";
    }
  }
  else if (command == "RIGHTSHAPES")
  {
    rightShapesCountCommand(polygons);
  }
  else
  {
    std::cerr << "<INVALID COMMAND>\n";
  }
}
#endif
