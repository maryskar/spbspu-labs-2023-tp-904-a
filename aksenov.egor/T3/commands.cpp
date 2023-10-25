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
    using areaMap = std::map< std::string, void (*)(const std::vector< aksenov::Polygon > &) >;
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
    } else
    {
      areaCommands[command](pol);
    }
  }

  void doMax(std::istream &inp, const std::vector< Polygon > &pol)
  {
    using maxMap = std::map< std::string, void (*)(const std::vector< aksenov::Polygon > &) >;
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
    using minMap = std::map< std::string, void (*)(const std::vector< aksenov::Polygon > &) >;
    minMap minCommands
    {
      {"AREA", doMinArea},
      {"VERTEXES", doMinVertexes}
    };
    std::string command = "";
    inp >> command;
    minCommands[command](pol);
  }

  void doCount(std::istream &inp, const std::vector< Polygon > &pol)
  {
    using countMap = std::map< std::string, void (*)(const std::vector< aksenov::Polygon > &) >;
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
    std::copy_if(pol.begin(), pol.end(), sorted.begin(), sort);
    auto func = std::bind(isSame, std::placeholders::_1, polygon);
    auto counter = std::count_if(sorted.begin(), sorted.end(), func);
    std::cout << counter << "\n";
  }

  double getDistance(const Point &p1, const Point &p2)
  {
    return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
  }

  Polygon createAngle(int &i, const Polygon &polygon)
  {
    Polygon angle;
    auto iter = polygon.points.begin() + i;
    angle.points.insert(angle.points.cbegin(), iter, iter + 3);
    i++;
    return angle;
  }

  std::vector< Polygon > createVectorOfAngles(const Polygon &polygon)
  {
    Polygon tmp(polygon);
    tmp.points.push_back(polygon.points.at(0));
    tmp.points.push_back(polygon.points.at(1));
    std::vector< Polygon > angles(polygon.points.size());
    int i = 0;
    auto bindFunction = std::bind(createAngle, i, tmp);
    std::generate(angles.begin(), angles.end(), bindFunction);
    return angles;
  }

  bool isRightAngle(const Polygon &angle)
  {
    if (angle.points.size() != 3)
    {
      return false;
    }
    double ab = getDistance(angle.points.at(0), angle.points.at(1));
    double bc = getDistance(angle.points.at(1), angle.points.at(2));
    double ca = getDistance(angle.points.at(2), angle.points.at(0));
    return std::sqrt(ab * ab + bc * bc) == ca;
  }

  bool isThereRightAngle(const Polygon &polygon)
  {
    auto angles = createVectorOfAngles(polygon);
    return std::any_of(angles.begin(), angles.end(), isRightAngle);
  }

  void doRightshapes(std::istream &, const std::vector< Polygon > &pol)
  {
    size_t count = std::count_if(pol.begin(), pol.end(), isThereRightAngle);
    std::cout << count << "\n";
  }
}
