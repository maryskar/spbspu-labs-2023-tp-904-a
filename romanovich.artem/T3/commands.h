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
using Point = romanovich::Point;
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
    std::transform(polygons.begin(), polygons.end(), areas.begin(), Polygon::AreaFunctor());
    return areas;
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
  std::vector< romanovich::Point > getPointsFromString(const std::string &input)
  {
    std::vector< romanovich::Point > points;
    size_t spacePos = input.find(' ');
    int numPoints = std::stoi(input.substr(0, spacePos));
    size_t startPos = spacePos + 1;
    for (int i = 0; i < numPoints; ++i)
    {
      size_t openParenPos = input.find('(', startPos);
      size_t semicolonPos = input.find(';', openParenPos);
      int x = std::stoi(input.substr(openParenPos + 1, semicolonPos - openParenPos - 1));
      int y = std::stoi(input.substr(semicolonPos + 1, input.find(')', semicolonPos) - semicolonPos - 1));
      romanovich::Point point{x, y};
      points.emplace_back(point);
      startPos = input.find(')', semicolonPos) + 1;
    }
    return points;
  }
}
void executeCommand(const std::vector< Polygon > &polygons, const std::string &command)
{
  auto polygonsTmp = polygons;
  const auto areaComp = static_cast<const std::function< bool(const Polygon &,
                                                              const Polygon &) > &>(Polygon::AreaComp{});
  const auto areaCompNegate = std::bind(std::logical_not<>(), std::bind(areaComp, _1, _2));
  const auto pointsComp = static_cast<const std::function< bool(const Polygon &,
                                                                const Polygon &) > &>(Polygon::PointsCountComp{});
  const auto pointsCompNegate = std::bind(std::logical_not<>(), std::bind(pointsComp, _1, _2));
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
    auto itp = std::partition(polygonsTmp.begin(), polygonsTmp.end(), Polygon::IsEvenVertexCount{});
    std::vector< double > areas = makeAreasVector(polygonsTmp);
    auto ita = std::next(areas.begin(), std::distance(polygonsTmp.begin(), itp));
    double sumOdd = std::accumulate(areas.begin(), ita, 0.0);
    double sumEven = std::accumulate(ita, areas.end(), 0.0);
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
  else if (command.substr(0, 4) == "AREA")
  {
    try
    {
      size_t targetCount = std::stoi(command.substr(5));
      polygonsTmp.erase(
        std::remove_if(polygonsTmp.begin(), polygonsTmp.end(), Polygon::HasNotVertexCount(targetCount)),
        polygonsTmp.end());
      std::vector< double > areas = makeAreasVector(polygonsTmp);
      std::cout << std::fixed << std::setprecision(1) << std::accumulate(areas.begin(), areas.end(), 0.0) << '\n';
    }
    catch (...)
    {
      std::cerr << "<INVALID PARAMETER>\n";
    }
  }
  if (command == "COUNT EVEN")
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(), Polygon::IsEvenVertexCount{}) << "\n";
  }
  else if (command == "COUNT ODD")
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(), Polygon::IsOddVertexCount{}) << "\n";
  }
  else if (command.substr(0, 5) == "COUNT")
  {
    try
    {
      std::cout
        << std::count_if(polygons.begin(), polygons.end(), Polygon::HasVertexCount{std::stoul(command.substr(6))})
        << "\n";
    }
    catch (...)
    {
      std::cerr << "<INVALID PARAMETER>\n";
    }
  }
  else if (command.substr(0, 6) == "MAXSEQ")
  {
    try
    {
      std::vector< Point > points;
      maxSeqCommand(polygons, Polygon(getPointsFromString(command.substr(7))));
    }
    catch (...)
    {
      std::cerr << "<INVALID PARAMETER>\n";
    }
  }
  else if (command == "RIGHTSHAPES")
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(), Polygon::HasRightAngle{}) << '\n';
  }
}
#endif
