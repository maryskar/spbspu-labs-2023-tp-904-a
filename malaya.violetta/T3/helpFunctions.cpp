#include "helpFunctions.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>
#include "Polygon.hpp"
#include "commandFunctions.hpp"

namespace malaya
{
  std::string inputCommand(std::istream & in)
  {
    std::string command = " ";
    in >> command;
    return command;
  }

  void doCommand(std::vector< malaya::Polygon > data, std::string & command, std::istream & in, std::ostream & out)
  {
    if(command == "AREA")
    {
      std::string option = " ";
      in >> option;
      if(option == "EVEN")
      {
        std::vector< double > values;
        std::transform(data.begin(), data.end(), values.begin(), areaEven);
        out << std::accumulate(values.begin(), values.end(), 0.0) << '\n';
      }
      else if(option == "EVEN")
      {
        std::vector< double > values;
        std::transform(data.begin(), data.end(), values.begin(), areaOdd);
        out << std::accumulate(values.begin(), values.end(), 0.0) << '\n';
      }
      else
      {
        in.setstate(std::ios::failbit);
        out << "<INVALID COMMAND>\n";
      }
    }
    else if(command == "MAX")
    {

    }
    else if(command == "MIN")
    {

    }
    else if(command == "COUNT")
    {

    }
    else if(command == "PERMS")
    {

    }
    else if(command == "RECTS")
    {

    }
    else
    {
      out << "<INVALID COMMAND>\n";
      in.setstate(std::ios::failbit);
    }
  }

  double areaCounter::operator()(const Point & left, const Point & right)
  {
    return (0.5 * (left.x * right.y - right.x * left.y));
  }
  double getArea(const Polygon & polygon)
  {
    double result = 0.0;
    size_t size = polygon.points.size();
    std::vector< double > values;
    std::transform(polygon.points.begin(), --polygon.points.end(),
                   ++polygon.points.begin(), values.begin(),
                   areaCounter{});
    result = std::accumulate(values.begin(), values.end(), 0.0); //????
    result += 0.5 * (polygon.points[size - 1].x * polygon.points[0].y -
      polygon.points[size - 1].y * polygon.points[0].x);
    return std::abs(result);
  }
}