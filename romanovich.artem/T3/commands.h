#ifndef COMMANDS_H
#define COMMANDS_H
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
namespace romanovich
{
  class CommandProcessor
  {
  public:
    CommandProcessor()
    {
      commands["MAX AREA"] = std::bind(&CommandProcessor::calcAreaMax, this, _1);
      commands["MIN AREA"] = std::bind(&CommandProcessor::calcAreaMin, this, _1);
      commands["MAX VERTEXES"] = std::bind(&CommandProcessor::calcPointsMax, this, _1);
      commands["MIN VERTEXES"] = std::bind(&CommandProcessor::calcPointsMin, this, _1);
      commands["AREA MEAN"] = std::bind(&CommandProcessor::calcAreaMean, this, _1);
      commands["AREA ODD"] = std::bind(&CommandProcessor::calcAreaOdd, this, _1);
      commands["AREA EVEN"] = std::bind(&CommandProcessor::calcAreaEven, this, _1);
      commands["AREA"] = std::bind(&CommandProcessor::calcAreaWithNumber, this, _1, _2);
      commands["COUNT"] = std::bind(&CommandProcessor::countWithNumber, this, _1, _2);
      commands["COUNT EVEN"] = std::bind(&CommandProcessor::countEven, this, _1);
      commands["COUNT ODD"] = std::bind(&CommandProcessor::countOdd, this, _1);
      commands["MAXSEQ"] = std::bind(&CommandProcessor::countMaxSeq, this, _1, _2);
      commands["RIGHTSHAPES"] = std::bind(&CommandProcessor::countShapesWithRightAngle, this, _1);
    }
    void tryCalcWithArg(const std::string &command, const std::vector< Polygon > &polygons);
    void operator()(const std::string &command, const std::vector< romanovich::Polygon > &polygons)
    {
      auto it = commands.find(command);
      if (it != commands.end())
      {
        (it->second)(polygons, 0);
      }
      else
      {
        tryCalcWithArg(command, polygons);
      }
    }
    std::unordered_map< std::string, std::function< void(const std::vector< Polygon > &, std::string)>> commands{
    };
  private:
    void calcAreaMin(const std::vector< Polygon > &);
    void calcAreaMax(const std::vector< Polygon > &);
    void calcPointsMax(const std::vector< Polygon > &);
    void calcPointsMin(const std::vector< Polygon > &);
    void calcAreaMean(const std::vector< Polygon > &);
    void calcAreaOdd(const std::vector< Polygon > &);
    void calcAreaEven(const std::vector< Polygon > &);
    void countOdd(const std::vector< Polygon > &);
    void countEven(const std::vector< Polygon > &);
    void countShapesWithRightAngle(const std::vector< Polygon > &);
    void calcAreaWithNumber(const std::vector< Polygon > &, const std::string &);
    void countWithNumber(const std::vector< Polygon > &, const std::string &);
    void countMaxSeq(const std::vector< Polygon > &, const std::string &);
  };
}
namespace
{
  void findMinMaxEl(const std::vector< Polygon > &polygons,
                    const std::function< bool(const Polygon &, const Polygon &) > &comp)
  {
    auto result = std::minmax_element(polygons.begin(), polygons.end(), comp);
    const auto elIt = comp(*result.second, *result.first) ? result.second : result.first;
    const auto i = std::distance(polygons.begin(), elIt);
    std::cout << std::fixed << std::setprecision(1) << polygons[i].getArea() << '\n';
  }
  std::vector< double > makeAreasVector(const std::vector< Polygon > &polygons)
  {
    std::vector< double > areas;
    areas.resize(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), Polygon::AreaFunctor());
    return areas;
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
  std::pair< std::vector< double >, std::vector< double >::iterator >
  partitionPolygonAreas(std::vector< Polygon > &polygonsTmp)
  {
    auto itp = std::partition(polygonsTmp.begin(), polygonsTmp.end(), Polygon::IsEvenPointsCount{});
    std::vector< double > areas = makeAreasVector(polygonsTmp);
    auto ita = std::next(areas.begin(), std::distance(polygonsTmp.begin(), itp));
    return {areas, ita};
  }
}
void romanovich::CommandProcessor::calcAreaMin(const std::vector< Polygon > &polygons)
{
  const auto areaComp = static_cast<const std::function< bool(const Polygon &,
                                                              const Polygon &) > &>(Polygon::AreaComp{});
  findMinMaxEl(polygons, areaComp);
}
void romanovich::CommandProcessor::calcAreaMax(const std::vector< Polygon > &polygons)
{
  const auto areaComp = static_cast<const std::function< bool(const Polygon &,
                                                              const Polygon &) > &>(Polygon::AreaComp{});
  const auto areaCompNegate = std::bind(std::logical_not<>(), std::bind(areaComp, _1, _2));
  findMinMaxEl(polygons, areaCompNegate);
}
void romanovich::CommandProcessor::calcPointsMax(const std::vector< Polygon > &polygons)
{
  const auto pointsComp = static_cast<const std::function< bool(const Polygon &,
                                                                const Polygon &) > &>(Polygon::PointsCountComp{});
  const auto pointsCompNegate = std::bind(std::logical_not<>(), std::bind(pointsComp, _1, _2));
  findMinMaxEl(polygons, pointsCompNegate);
}
void romanovich::CommandProcessor::calcPointsMin(const std::vector< Polygon > &polygons)
{
  const auto pointsComp = static_cast<const std::function< bool(const Polygon &,
                                                                const Polygon &) > &>(Polygon::PointsCountComp{});
  findMinMaxEl(polygons, pointsComp);
}
void romanovich::CommandProcessor::calcAreaMean(const std::vector< Polygon > &polygons)
{
  auto polygonsTmp = polygons;
  auto areas = partitionPolygonAreas(polygonsTmp).first;
  double sumMean = std::accumulate(areas.begin(), areas.end(), 0.0) / static_cast< double >(areas.size());
  std::cout << std::fixed << std::setprecision(1) << sumMean << '\n';
}
void romanovich::CommandProcessor::calcAreaOdd(const std::vector< Polygon > &polygons)
{
  auto polygonsTmp = polygons;
  auto areas = partitionPolygonAreas(polygonsTmp).first;
  auto ita = partitionPolygonAreas(polygonsTmp).second;
  double sumOdd = std::accumulate(areas.begin(), ita, 0.0);
  std::cout << std::fixed << std::setprecision(1) << sumOdd << '\n';
}
void romanovich::CommandProcessor::calcAreaEven(const std::vector< Polygon > &polygons)
{
  auto polygonsTmp = polygons;
  auto areas = partitionPolygonAreas(polygonsTmp).first;
  auto ita = partitionPolygonAreas(polygonsTmp).second;
  double sumEven = std::accumulate(ita, areas.end(), 0.0);
  std::cout << std::fixed << std::setprecision(1) << sumEven << '\n';
}
void
romanovich::CommandProcessor::calcAreaWithNumber(const std::vector< Polygon > &polygons, const std::string &command)
{
  try
  {
    auto polygonsTmp = polygons;
    size_t targetNumber = std::stoi(command.substr(5));
    polygonsTmp.erase(
      std::remove_if(polygonsTmp.begin(), polygonsTmp.end(), Polygon::HasNotPointsCount(targetNumber)),
      polygonsTmp.end());
    std::vector< double > areas = makeAreasVector(polygonsTmp);
    std::cout << std::fixed << std::setprecision(1) << std::accumulate(areas.begin(), areas.end(), 0.0) << '\n';
  }
  catch (...)
  {
    std::cerr << "<INVALID PARAMETER>\n";
  }
}
void romanovich::CommandProcessor::countWithNumber(const std::vector< Polygon > &polygons, const std::string &command)
{
  try
  {
    size_t targetNumber = std::stoi(command.substr(6));
    std::cout << std::count_if(polygons.begin(), polygons.end(), Polygon::HasPointsCount{targetNumber}) << "\n";
  }
  catch (...)
  {
    std::cerr << "<INVALID PARAMETER>\n";
  }
}
void romanovich::CommandProcessor::tryCalcWithArg(const std::string &command, const std::vector< Polygon > &polygons)
{
  if (command.substr(0, 4) == "AREA")
  {
    calcAreaWithNumber(polygons, command);
  }
  else if (command.substr(0, 5) == "COUNT")
  {
    countWithNumber(polygons, command);
  }
  else if (command.substr(0, 6) == "MAXSEQ")
  {
    countMaxSeq(polygons, command);
  }
  else
  {
    std::cerr << "<INVALID COMMAND>\n";
  }
}
void romanovich::CommandProcessor::countEven(const std::vector< Polygon > &polygons)
{
  std::cout << std::count_if(polygons.begin(), polygons.end(), Polygon::IsEvenPointsCount{}) << "\n";
}
void romanovich::CommandProcessor::countOdd(const std::vector< Polygon > &polygons)
{
  std::cout << std::count_if(polygons.begin(), polygons.end(), Polygon::IsOddPointsCount{}) << "\n";
}
void romanovich::CommandProcessor::countMaxSeq(const std::vector< Polygon > &polygons, const std::string &argString)
{
  try
  {
    if (polygons.empty())
    {
      std::cerr << "No polygons.\n";
      return;
    }
    auto generatedPolygon = Polygon(getPointsFromString(argString.substr(7)));
    auto notComp = std::bind(std::negate<>(), std::bind(Polygon::PolygonComparator(generatedPolygon), _1, _2));
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
  catch (...)
  {
    std::cerr << "<INVALID PARAMETER>\n";
  }
}
void romanovich::CommandProcessor::countShapesWithRightAngle(const std::vector< Polygon > &polygons)
{
  std::cout << std::count_if(polygons.begin(), polygons.end(), Polygon::HasRightAngle{}) << '\n';
}
#endif
/*

void executeCommand(const std::vector< Polygon > &polygons, const std::string &command)
{
  auto polygonsTmp = polygons;
  const auto areaComp = static_cast<const std::function< bool(const Polygon &,
                                                              const Polygon &) > &>(Polygon::AreaComp{});
  const auto areaCompNegate = std::bind(std::logical_not<>(), std::bind(areaComp, _1, _2));
  const auto pointsComp = static_cast<const std::function< bool(const Polygon &,
                                                                const Polygon &) > &>(Polygon::PointsCountComp{});
  //
  //
  //
  //
  //
  const auto pointsCompNegate = std::bind(std::logical_not<>(), std::bind(pointsComp, _1, _2));

  else if (command == "RIGHTSHAPES")
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(), Polygon::HasRightAngle{}) << '\n';
  }
  else
  {
    std::cerr << "<INVALID COMMAND>\n";
  }
}
#endif
*/
