#include "commands.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include "areaCommands.h"
#include "maxCommands.h"
#include "minCommands.h"
#include "countFunctions.h"
#include "polygon.h"
#include "helpFunctions.h"
namespace aksenov
{
  void doArea(std::istream &inp, const std::vector< Polygon > &pol)
  {
    using areaMap = std::map< std::string, void(*)(const std::vector< aksenov::Polygon >&) >;
    areaMap areaCommands
    {
      {"EVEN", doAreaEven},
      {"ODD", doAreaOdd},
      {"MEAN", doAreaMean}
    };
    std::string command = "";
    inp >> command;
    try
    {
      if (isInteger(command))
      {
        doAreaWithVertexes(pol, command);
      }

      areaCommands[command](pol);
    }
    catch(...)
    {
      throw;
    }
  }

  void doMax(std::istream &inp, const std::vector< Polygon > &pol)
  {
    using maxMap = std::map< std::string, void(*)(const std::vector< aksenov::Polygon >&) >;
    maxMap maxCommands
    {
      {"AREA", doMaxArea},
      {"VERTEXES", doMaxVertexes}
    };
    std::string command = "";
    inp >> command;
    maxCommands[command](pol);
  }

  void doMin(std::istream &inp, const std::vector< Polygon > &pol)
  {
    using minMap = std::map< std::string, void(*)(const std::vector< aksenov::Polygon >&) >;
    minMap minCommands
    {
      {"AREA", doMinArea},
      {"VERTEXES", doMinVertexes}
    };
    std::string command = "";
    inp >> command;
    minCommands[command](pol);
  }

  void doCount(std::istream &inp, const std::vector< Polygon >&pol)
  {
    using countMap = std::map< std::string, void(*)(const std::vector< aksenov::Polygon >&) >;
    countMap countCommands
    {
      {"EVEN", doCountEven},
      {"ODD", doCountOdd}
    };
    std::string command = "";
    inp >> command;
    try
    {
      if (isInteger(command))
      {
        doCountVertexes(command, pol);
      }
      countCommands[command](pol);
    }
    catch(...)
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
