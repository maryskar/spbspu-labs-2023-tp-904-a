  #include "commands.h"
  #include <iostream>
  #include <vector>
  #include <string>
  #include <algorithm>
  #include <numeric>
  #include <functional>
  #include <iterator>
  #include <iomanip>
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
      size_t num = std::stoul(command);
      std::vector< Polygon > pols;
      auto func = std::bind(isEqual, std::placeholders::_1, num);
      std::copy_if(pol.begin(),pol.end(), std::back_inserter(pols), func);
      std::vector< double > areas = getArea(pols);
      double res = std::accumulate(areas.begin(), areas.end(), 0);
      std::cout << std::fixed << std::setprecision(1) << res << "\n";
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
        if (command == "1" || command == "2" || command == "0")
        {
          throw;
        }
        else
        {
          doAreaWithVertexes(pol, command);
        }
      }
      else
      {
        throw;
      }
    }

    void doMaxArea(const std::vector< Polygon > &pol)
    {
      if (pol.empty())
      {
        throw std::invalid_argument("empty polygon");
      }
      std::vector< double > areas = getArea(pol);
      double maxElemen = *std::max_element(areas.begin(), areas.end());
      std::cout << std::fixed << std::setprecision(1) << maxElemen << "\n";
    }

    void doMaxVertexes(const std::vector< Polygon > &pol)
    {
      if (pol.empty())
      {
        throw std::invalid_argument("empty polygon");
      }
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
        throw;
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
        throw;
      }
    }

    void doCountEven(const std::vector< Polygon > &pol)
    {
      std::vector< Polygon > pols = pol;
      size_t res = std::count_if(pols.begin(), pols.end(), isEven);
      std::cout << res << "\n";
    }

    void doCountOdd(const std::vector< Polygon > &pol)
    {
      std::vector< Polygon > pols = pol;
      size_t res = std::count_if(pols.begin(), pols.end(), isOdd);
      std::cout << res << "\n";
    }

    void doCountVertexes(std::string command, const std::vector< Polygon > &pol)
    {
      std::vector< Polygon > pols = pol;
      size_t amount = std::stoull(command);
      auto func = std::bind(isEqual, std::placeholders::_1, amount);
      size_t res = std::count_if(pols.begin(), pols.end(), func);
      std::cout << res << "\n";
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
        if (command == "1" || command == "2" || command == "0")
        {
          throw;
        }
        else
        {
          doCountVertexes(command, pol);
        }
      }
      else
      {
        throw;
      }
    }

    void doSame(std::istream &inp, const std::vector< Polygon > &pol)
    {
      if (pol.size() == 0 || pol.size() == 1)
      {
        throw std::invalid_argument("empty pol");
      }
      Polygon polygon;
      inp >> polygon;
      auto sort = std::bind(isEqual, std::placeholders::_1, polygon.points.size());
      std::vector< Polygon > sorted;
      std::copy_if(pol.begin(),pol.end(),sorted.begin(), sort);
      auto func = std::bind(isSame, std::placeholders::_1, polygon);
      auto counter = std::count_if(sorted.begin(), sorted.end(), func);
      std::cout << counter << "\n";
    }

    void doRightshapes(std::istream &, const std::vector< Polygon > &pol)
    {
      size_t count = 0;
      for (const Polygon& polygon : pol)
      {
        for (size_t i = 0; i < polygon.points.size(); i++)
        {
          const Point& p1 = polygon.points[i];
          const Point& p2 = polygon.points[(i + 1) % polygon.points.size()];
          const Point& p3 = polygon.points[(i + 2) % polygon.points.size()];
          int x1 = p2.x - p1.x;
          int y1 = p2.y - p1.y;
          int x2 = p3.x - p2.x;
          int y2 = p3.y - p2.y;
          if (x1 * x2 + y1 * y2 == 0)
          {
            count++;
            break;
          }
        }
      }
      std::cout << count << "\n";
    }
  }
