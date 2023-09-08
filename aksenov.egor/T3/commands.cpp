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
    auto out = std::ostream_iterator< double > (std::cout, "\n");
    std::copy(maxElementIter, maxElementIter + 1, out);
  }

  void doMaxVertexes(const std::vector< Polygon > &pol)
  {
    std::vector< Polygon > pols = pol;
    std::vector< size_t > amountsOfVertexes;
    for (const Polygon &polygon : pols)
    {
      amountsOfVertexes.push_back(polygon.points.size());
    }
    auto maxVertIter = std::max_element(amountsOfVertexes.begin(), amountsOfVertexes.end());
    auto out = std::ostream_iterator< size_t > (std::cout, "\n");
    std::copy(maxVertIter, maxVertIter + 1, out);
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

  void doMinArea(const std::vector< Polygon > &pol)
  {
    std::vector< double > areas = getArea(pol);
    auto minElementIter = std::min_element(areas.begin(), areas.end());
    auto out = std::ostream_iterator< double > (std::cout, "\n");
    std::copy(minElementIter, minElementIter + 1, out);
  }

  void doMinVertexes(const std::vector< Polygon > &pol)
  {
    std::vector< Polygon > pols = pol;
    std::vector< size_t > amountsOfVertexes;
    for (const Polygon &polygon : pols)
    {
      amountsOfVertexes.push_back(polygon.points.size());
    }
    auto minVertIter = std::min_element(amountsOfVertexes.begin(), amountsOfVertexes.end());
    auto out = std::ostream_iterator< size_t > (std::cout, "\n");
    std::copy(minVertIter, minVertIter + 1, out);
  }

  void doMin(std::istream &inp, const std::vector< Polygon > &pol)
  {
    std::string command = "";
    inp >> command;
    if (command == "AREA")
    {
      doMinArea(pol);
    }
    else if (command == "VERTEXES")
    {
      doMinVertexes(pol);
    }
    else
    {
      std::cout << "invalid command";
    }
  }

  void doCount(std::istream &inp, const std::vector< Polygon >&pol)
  {
    std::string command = "";
    inp >> command;
    if (command == "EVEN")
    {
      doCountEven(pol);
    }
    else if (command == "ODD")
    {
      doCountOdd(pol);
    }
    else if (isInteger(command))
    {
      if (command == "1" || command == "2")
      {
        std::cout << "invalid command";
      }
      else
      {
        doCountVertexes(command, pol);
      }
    }
  }

}
