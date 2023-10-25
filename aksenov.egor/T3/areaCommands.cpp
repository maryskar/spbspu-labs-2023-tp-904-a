#include "areaCommands.h"
#include <iomanip>
#include <iostream>
#include <numeric>
#include <functional>
#include "helpFunctions.h"
namespace aksenov
{
  void doAreaEven(const std::vector< Polygon > &pol)
  {
    std::vector< Polygon > vecOfPolygons;
    std::copy_if(pol.begin(),pol.end(), std::back_inserter(vecOfPolygons), isEven);
    std::vector< double > areas = getArea(vecOfPolygons);
    double res = std::accumulate(areas.begin(), areas.end(), 0);
    std::cout << std::fixed << std::setprecision(1) << res << "\n";
  }

  void doAreaOdd(const std::vector< Polygon > &pol)
  {
    std::vector< Polygon > vecOfPolygons;
    std::copy_if(pol.begin(),pol.end(), std::back_inserter(vecOfPolygons), isOdd);
    std::vector< double > areas = getArea(vecOfPolygons);
    double res = std::accumulate(areas.begin(), areas.end(), 0);
    std::cout << std::fixed << std::setprecision(1) << res << "\n";
  }

  void doAreaMean(const std::vector< Polygon > &pol)
  {
    if (pol.empty())
    {
      throw std::invalid_argument("invalid argument");
    }
    std::vector< double > areas = getArea(pol);
    double area = std::accumulate(areas.begin(), areas.end(), 0);
    area /= pol.size();
    std::cout << std::fixed << std::setprecision(1) << area << "\n";
  }

  void doAreaWithVertexes(const std::vector< Polygon > &pol, std::string command)
  {
    if (command == "1" || command == "2" || command == "0")
    {
      throw std::invalid_argument("invalid input");
    }
    size_t num = std::stoul(command);
    std::vector< Polygon > pols;
    auto func = std::bind(isEqual, std::placeholders::_1, num);
    std::copy_if(pol.begin(),pol.end(), std::back_inserter(pols), func);
    std::vector< double > areas = getArea(pols);
    double res = std::accumulate(areas.begin(), areas.end(), 0);
    std::cout << std::fixed << std::setprecision(1) << res << "\n";
  }
}
