#include "commands.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <iterator>
#include <map>
#include <cctype>
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

    if (command.find_first_not_of("0123456789") == std::string::npos)
    {
      doAreaWithVertexes(pol, command);
    }
    else
    {
      areaCommands[command](pol);
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

    if (command.find_first_not_of("0123456789") == std::string::npos)
    {
      doCountVertexes(command, pol);
    }
    else
    {
      countCommands[command](pol);
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

  bool isRightShape(const aksenov::Polygon& polygon)
  {
    if (polygon.points.size() != 4)
    {
      return false;
    }
    int dx1 = polygon.points[1].x - polygon.points[0].x;
    int dy1 = polygon.points[1].y - polygon.points[0].y;
    int dx2 = polygon.points[2].x - polygon.points[1].x;
    int dy2 = polygon.points[2].y - polygon.points[1].y;
    int dx3 = polygon.points[3].x - polygon.points[2].x;
    int dy3 = polygon.points[3].y - polygon.points[2].y;
    return (dx1 * dx2 + dy1 * dy2 == 0) && (dx2 * dx3 + dy2 * dy3 == 0);
  }

  void doRightshapes(std::istream &, const std::vector< Polygon > &pol)
    {
      std::vector< Polygon > rightShapes;
      std::copy_if(pol.begin(), pol.end(), std::back_inserter(rightShapes), isRightShape);
      std::cout << rightShapes.size();
    }
  }
