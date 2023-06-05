#include "commands.h"
#include <iostream>
#include <numeric>
using Polygon = romanovich::Polygon;
using Point = romanovich::Point;
namespace
{
  void printError()
  {
    std::cout << "<INVALID COMMAND>\n";
  }
  Polygon const &findMinMaxEl(const std::vector< Polygon > &polygons,
    const std::function< bool(const Polygon &, const Polygon &) > &comp)
  {
    auto result = std::minmax_element(polygons.begin(), polygons.end(), comp);
    const auto &el = comp(*result.second, *result.first) ? *result.second : *result.first;
    return el;
  }
  void findMinMaxElArea(const std::vector< Polygon > &polygons,
    const std::function< bool(const Polygon &, const Polygon &) > &comp)
  {
    if (polygons.empty())
    {
      printError();
    }
    else
    {
      std::cout << std::fixed << std::setprecision(1) << findMinMaxEl(polygons, comp).getArea() << "\n";
    }
  }
  void findMinMaxElPointsCount(const std::vector< Polygon > &polygons,
    const std::function< bool(const Polygon &, const Polygon &) > &comp)
  {
    if (polygons.empty())
    {
      printError();
    }
    else
    {
      std::cout << findMinMaxEl(polygons, comp).getPointsCount() << '\n';
    }
  }
  std::vector< double > makeAreasVector(const std::vector< Polygon > &polygons)
  {
    std::vector< double > areas;
    areas.resize(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), Polygon::AreaFunctor());
    return areas;
  }
  std::vector< Point > getPointsFromString(const std::string &input)
  {
    std::vector< Point > points;
    size_t spacePos = input.find(' ');
    int numPoints = std::stoi(input.substr(0, spacePos));
    size_t startPos = spacePos + 1;
    for (int i = 0; i < numPoints; ++i)
    {
      size_t openParenPos = input.find('(', startPos);
      size_t semicolonPos = input.find(';', openParenPos);
      int x = std::stoi(input.substr(openParenPos + 1, semicolonPos - openParenPos - 1));
      int y = std::stoi(input.substr(semicolonPos + 1, input.find(')', semicolonPos) - semicolonPos - 1));
      points.emplace_back(x, y);
      startPos = input.find(')', semicolonPos) + 1;
    }
    return points;
  }
  std::pair< double, double > partitionPolygonAreas(std::vector< Polygon > polygons)
  {
    auto itp = std::partition(polygons.begin(), polygons.end(), Polygon::IsEvenPointsCount{});
    std::vector< double > areas = makeAreasVector(polygons);
    auto ita = std::next(areas.begin(), std::distance(polygons.begin(), itp));
    double sumEven = std::accumulate(ita, areas.end(), 0.0);
    double sumOdd = std::accumulate(areas.begin(), ita, 0.0);
    return {sumEven, sumOdd};
  }
}
namespace romanovich
{
  void CommandProcessor::calcAreaMin(const std::vector< Polygon > &polygons)
  {
    const auto areaComp = static_cast<const std::function< bool(const Polygon &,
      const Polygon &) > &>(Polygon::AreaComp{});
    findMinMaxElArea(polygons, areaComp);
  }
  void CommandProcessor::calcAreaMax(const std::vector< Polygon > &polygons)
  {
    const auto areaComp = static_cast<const std::function< bool(const Polygon &,
      const Polygon &) > &>(Polygon::AreaComp{});
    const auto areaCompNegate = std::bind(std::logical_not<>(), std::bind(areaComp, _1, _2));
    findMinMaxElArea(polygons, areaCompNegate);
  }
  void CommandProcessor::calcPointsMax(const std::vector< Polygon > &polygons)
  {
    const auto pointsComp = static_cast<const std::function< bool(const Polygon &,
      const Polygon &) > &>(Polygon::PointsCountComp{});
    const auto pointsCompNegate = std::bind(std::logical_not<>(), std::bind(pointsComp, _1, _2));
    findMinMaxElPointsCount(polygons, pointsCompNegate);
  }
  void CommandProcessor::calcPointsMin(const std::vector< Polygon > &polygons)
  {
    const auto pointsComp = static_cast<const std::function< bool(const Polygon &,
      const Polygon &) > &>(Polygon::PointsCountComp{});
    findMinMaxElPointsCount(polygons, pointsComp);
  }
  void CommandProcessor::calcAreaMean(const std::vector< Polygon > &polygons)
  {
    if (polygons.empty())
    {
      printError();
    }
    else
    {
      auto sumOfAreas = partitionPolygonAreas(polygons).second + partitionPolygonAreas(polygons).first;
      std::cout << std::fixed << std::setprecision(1) << sumOfAreas
                                                              / static_cast< double >(polygons.size()) << '\n';
    }
  }
  void CommandProcessor::calcAreaOdd(const std::vector< Polygon > &polygons)
  {
    std::cout << std::fixed << std::setprecision(1) << partitionPolygonAreas(polygons).second << '\n';
  }
  void CommandProcessor::calcAreaEven(const std::vector< Polygon > &polygons)
  {
    std::cout << std::fixed << std::setprecision(1) << partitionPolygonAreas(polygons).first << '\n';
  }
  void tryCalcWithArg(const std::string &command, const std::vector< Polygon > &polygons)
  {
    CommandProcessor commandProcessor;
    if (command.substr(0, 4) == "AREA")
    {
      commandProcessor.calcAreaWithNumber(polygons, command);
    }
    else if (command.substr(0, 5) == "COUNT")
    {
      commandProcessor.countWithNumber(polygons, command);
    }
    else if (command.substr(0, 6) == "MAXSEQ")
    {
      commandProcessor.countMaxSeq(polygons, command);
    }
    else
    {
      printError();
    }
  }
  void CommandProcessor::calcAreaWithNumber(const std::vector< Polygon > &pols, const std::string &command)
  {
    try
    {
      size_t targetNumber = std::stoi(command.substr(5));
      if (targetNumber > 2)
      {
        auto polygonsTmp = pols;
        polygonsTmp.erase(
          std::remove_if(polygonsTmp.begin(), polygonsTmp.end(), Polygon::HasNotPointsCount(targetNumber)),
            polygonsTmp.end());
        std::vector< double > areas = makeAreasVector(polygonsTmp);
        std::cout << std::fixed << std::setprecision(1) << std::accumulate(areas.begin(), areas.end(), 0.0) << '\n';
      }
      else
      {
        printError();
      }
    }
    catch (...)
    {
      printError();
    }
  }
  void CommandProcessor::countWithNumber(const std::vector< Polygon > &polygons, const std::string &command)
  {
    try
    {
      size_t targetNumber = std::stoi(command.substr(6));
      if (targetNumber > 2)
      {
        std::cout << std::count_if(polygons.begin(), polygons.end(), Polygon::HasPointsCount{targetNumber}) << "\n";
      }
      else
      {
        printError();
      }
    }
    catch (...)
    {
      printError();
    }
  }
  void CommandProcessor::operator()(const std::string &command, const std::vector< Polygon > &polygons)
  {
    auto it = commands.find(command);
    if (it != commands.end())
    {
      (it->second)(polygons, "");
    }
    else
    {
      tryCalcWithArg(command, polygons);
    }
  }
  void CommandProcessor::countEven(const std::vector< Polygon > &polygons)
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(), Polygon::IsEvenPointsCount{}) << "\n";
  }
  void CommandProcessor::countOdd(const std::vector< Polygon > &polygons)
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(), Polygon::IsOddPointsCount{}) << "\n";
  }
  void CommandProcessor::countMaxSeq(const std::vector< Polygon > &polygons, const std::string &argString)
  {
    try
    {
      if (polygons.empty())
      {
        printError();
        return;
      }
      auto generatedPolygon = Polygon(getPointsFromString(argString.substr(7)));
      auto comp = std::bind(Polygon::PolygonComparator(generatedPolygon), _1, _2);
      size_t maxSeqCount = 0;
      size_t currSeqCount = 0;
      bool insideSeq = false;
      for (const auto &polygon: polygons)
      {
        if (comp(polygon, polygon))
        {
          if (!insideSeq)
          {
            insideSeq = true;
            currSeqCount = 1;
          }
          else
          {
            ++currSeqCount;
          }
          maxSeqCount = std::max(maxSeqCount, currSeqCount);
        }
        else
        {
          insideSeq = false;
        }
      }
      if (maxSeqCount == 0)
      {
        printError();
      }
      else
      {
        std::cout << maxSeqCount << '\n';
      }
    }
    catch (...)
    {
      printError();
    }
  }
  void CommandProcessor::countShapesWithRightAngle(const std::vector< Polygon > &polygons)
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(), Polygon::HasRightAngle{}) << '\n';
  }
}
