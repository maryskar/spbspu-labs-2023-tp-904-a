#include "commands.h"
#include <iostream>
#include <numeric>
#include "polygonutils.h"
using namespace romanovich;
namespace
{
  using compType = const std::function< bool(const Polygon &, const Polygon &) >&;
  using iterPair = std::pair< std::vector< Polygon >::const_iterator, std::vector< Polygon >::const_iterator >;
  const Polygon &findMinMaxEl(const std::vector< Polygon > &polygons,
      const std::function< bool(const Polygon &, const Polygon &) > &comp)
  {
    iterPair result = std::minmax_element(polygons.begin(), polygons.end(), comp);
    const Polygon &el = comp(*result.second, *result.first) ? *result.second : *result.first;
    return el;
  }
  void findMinMaxElArea(const std::vector< Polygon > &polygons,
      const std::function< bool(const Polygon &, const Polygon &) > &comp)
  {
    if (polygons.empty())
    {
      throw std::runtime_error("No polygons.");
    }
    else
    {
      std::cout << std::fixed << std::setprecision(1) << getArea(findMinMaxEl(polygons, comp)) << "\n";
    }
  }
  void findMinMaxElPointsCount(const std::vector< Polygon > &polygons,
      const std::function< bool(const Polygon &, const Polygon &) > &comp)
  {
    if (polygons.empty())
    {
      throw std::runtime_error("No polygons.");
    }
    else
    {
      std::cout << getPointsCount(findMinMaxEl(polygons, comp)) << '\n';
    }
  }
  std::vector< double > makeAreasVector(const std::vector< Polygon > &polygons)
  {
    std::vector< double > areas;
    areas.resize(polygons.size());
    std::transform(polygons.begin(), polygons.end(), areas.begin(), AreaFunctor());
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
      points.push_back({x, y});
      startPos = input.find(')', semicolonPos) + 1;
    }
    return points;
  }
  std::pair< double, double > partitionPolygonAreas(std::vector< Polygon > polygons)
  {
    std::vector< Polygon >::iterator itp = std::partition(polygons.begin(), polygons.end(),
        romanovich::IsEvenPointsCount{});
    std::vector< double > areas = makeAreasVector(polygons);
    std::vector< double >::iterator ita = std::next(areas.begin(), std::distance(polygons.begin(), itp));
    double sumEven = std::accumulate(ita, areas.end(), 0.0);
    double sumOdd = std::accumulate(areas.begin(), ita, 0.0);
    return {sumEven, sumOdd};
  }
}
namespace romanovich
{
  using namespace std::placeholders;
  void CommandProcessor::calcAreaMin(const std::vector< Polygon > &polygons)
  {
    compType areaComp = static_cast< compType >(romanovich::AreaComp{});
    findMinMaxElArea(polygons, areaComp);
  }
  void CommandProcessor::calcAreaMax(const std::vector< Polygon > &polygons)
  {
    compType areaComp = static_cast< compType >(romanovich::AreaComp{});
    compType areaCompNegate = std::bind(std::logical_not<>(), std::bind(areaComp, _1, _2));
    findMinMaxElArea(polygons, areaCompNegate);
  }
  void CommandProcessor::calcPointsMax(const std::vector< Polygon > &polygons)
  {
    compType pointsCompNegate = std::bind(std::logical_not<>(), std::bind(romanovich::PointsCountComp{}, _1, _2));
    findMinMaxElPointsCount(polygons, pointsCompNegate);
  }
  void CommandProcessor::calcPointsMin(const std::vector< Polygon > &polygons)
  {
    findMinMaxElPointsCount(polygons, romanovich::PointsCountComp{});
  }
  void CommandProcessor::calcAreaMean(const std::vector< Polygon > &polygons)
  {
    if (polygons.empty())
    {
      throw std::runtime_error("No polygons.");
    }
    else
    {
      double sumOfAreas = partitionPolygonAreas(polygons).second + partitionPolygonAreas(polygons).first;
      std::cout << std::fixed << std::setprecision(1);
      std::cout  << sumOfAreas / static_cast< double >(polygons.size()) << '\n';
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
      throw std::runtime_error("Invalid command.");
    }
  }
  void CommandProcessor::calcAreaWithNumber(const std::vector< Polygon > &pols, const std::string &command)
  {
    size_t targetNumber = getTargetNumber(command);
    if (targetNumber > 2)
    {
      std::vector< Polygon > polygonsTmp = pols;
      std::vector< Polygon >::const_iterator first = std::remove_if(polygonsTmp.begin(), polygonsTmp.end(),
          romanovich::HasNotPointsCount(targetNumber));
      std::vector< Polygon >::const_iterator last = polygonsTmp.end();
      polygonsTmp.erase(first, last);
      std::vector< double > areas = makeAreasVector(polygonsTmp);
      std::cout << std::fixed << std::setprecision(1) << std::accumulate(areas.begin(), areas.end(), 0.0) << '\n';
    }
    else
    {
      throw std::runtime_error("Invalid input.");
    }
  }
  void CommandProcessor::countWithNumber(const std::vector< Polygon > &polygons, const std::string &command)
  {
    size_t targetNumber = getTargetNumber(command);
    if (targetNumber > 2)
    {
      std::cout << std::count_if(polygons.begin(), polygons.end(), romanovich::HasPointsCount{targetNumber}) << "\n";
    }
    else
    {
      throw std::runtime_error("Invalid input.");
    }
  }
  void CommandProcessor::operator()(const std::string &command, const std::vector< Polygon > &polygons)
  {
    mapType::iterator it = commands.find(command);
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
    std::cout << std::count_if(polygons.begin(), polygons.end(), romanovich::IsEvenPointsCount{}) << "\n";
  }
  void CommandProcessor::countOdd(const std::vector< Polygon > &polygons)
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(), romanovich::IsOddPointsCount{}) << "\n";
  }
  void CommandProcessor::countMaxSeq(const std::vector< Polygon > &polygons, const std::string &argString)
  {
    if (polygons.empty())
    {
      throw std::runtime_error("No polygons.");
    }
    size_t targetNumber = getTargetNumber(argString);
    Polygon generatedPolygon = Polygon{getPointsFromString(std::to_string(targetNumber))};
    compType comp = std::bind(romanovich::PolygonComparator(generatedPolygon), _1, _2);
    size_t maxSeqCount = 0;
    size_t currSeqCount = 0;
    bool insideSeq = false;
    for (const Polygon &polygon: polygons)
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
      throw std::runtime_error("Invalid input.");
    }
    else
    {
      std::cout << maxSeqCount << '\n';
    }
  }
  void CommandProcessor::countShapesWithRightAngle(const std::vector< Polygon > &polygons)
  {
    std::cout << std::count_if(polygons.begin(), polygons.end(), romanovich::HasRightAngle{}) << '\n';
  }
  int CommandProcessor::getTargetNumber(const std::string &line)
  {
    return std::stoi(line.substr(line.length() - 1, 1));
  }
}
