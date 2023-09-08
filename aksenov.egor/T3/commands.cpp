#include "commands.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include "polygon.h"
#include "helpFunctions.h"
namespace aksenov
{
  void doAreaEven(const std::vector< Polygon > &pol)
  {
    std::vector< Polygon > vecOfPolygons;
    std::copy_if(pol.begin(),pol.end(), std::back_inserter(vecOfPolygons), isEven);
    std::vector< double > areas = getArea(vecOfPolygons);
    double res = std::accumulate(areas.begin(), areas.end(), 0);
    std::cout << res << "\n";
  }

  void doAreaOdd(const std::vector< Polygon > &pol)
  {
    std::vector< Polygon > vecOfPolygons;
    std::copy_if(pol.begin(),pol.end(), std::back_inserter(vecOfPolygons), isOdd);
    std::vector< double > areas = getArea(vecOfPolygons);
    double res = std::accumulate(areas.begin(), areas.end(), 0);
    std::cout << res << "\n";
  }

  void doAreaMean(const std::vector< Polygon > &pol)
  {
    std::vector< double > areas = getArea(pol);
    double area = std::accumulate(areas.begin(), areas.end(), 0);
    area /= pol.size();
    std::cout << area << "\n";
  }

  void doAreaWithVertexes(const std::vector< Polygon > &pol, std::string command)
  {
    size_t num = std::stoul(command);
    std::vector< Polygon > pols;
    auto func = std::bind(isNotEqual, std::placeholders::_1, num);
    std::copy_if(pol.begin(),pol.end(), std::back_inserter(pols), func);
    std::vector< double > areas = getArea(pols);
    double res = std::accumulate(areas.begin(), areas.end(), 0);
    std::cout << res << "\n";
  }

  void doArea(std::istream &inp, const std::vector< Polygon > &pol)
  {
    std::string command = "";
    inp >> command;

    if (command == "EVEN")
    {
      doAreaEven(pol);
    }
    else if (command == "ODD")
    {
      doAreaOdd(pol);
    }
    else if (command == "MEAN")
    {
      doAreaMean(pol);
    }
    else if (isInteger(command))
    {
      if (command == "1" || command == "2")
      {
        std::cout << "error";
      }
      else
      {
        doAreaWithVertexes(pol, command);
      }
    }
  }

  void doMaxArea(const std::vector< Polygon > &pol)
  {
    std::vector< double > areas = getArea(pol);
    auto maxElementIter = std::max_element(areas.begin(), areas.end());
    auto it = std::ostream_iterator< double > (std::cout, "\n");
    std::copy(maxElementIter, maxElementIter + 1, it);
  }

  void doMax(std::istream &inp, const std::vector< Polygon > &pol)
  {
    std::string command = "";
    inp >> command;
    if (command == "AREA")
    {
      doMaxArea(pol);
    }
    else if (command == "VERTEXES")
    {
      doMaxVertexes(pol);
    }
    else
    {
      std::cout << "invalid command";
    }
  }
}
