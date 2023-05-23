#include "helpFunctions.hpp"
#include <algorithm>
#include <numeric>
#include <cmath>
#include <functional>
#include <iostream>
#include <limits>
#include <vector>
#include <cctype> //???????????????????
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
  void invalidPrint(std::ostream & out)
  {
    out << "<INVALID COMMAND>";
  }

  void doCommand(const std::vector< malaya::Polygon > & data, std::string & command, std::istream & in,
                 std::ostream & out)
  {
    if(command == "AREA")
    {
      std::string option = " ";
      in >> option;
      if(option == "EVEN")
      {
        outAreaEven(data, out);
      }
      else if(option == "ODD")
      {
        outAreaOdd(data, out);
      }
      else if(option == "MEAN") //?????????????????????????????
      {
        std::vector< double > values;
        std::transform(data.begin(), data.end(), values.begin(), getArea);
        double sum = std::accumulate(values.begin(), values.end(), 0.0);
        out << std::round((sum / values.size()) * 10) / 10;
      }
      //else //><DJKHKGFLSIU>ALOJ?:KPUYDTFRQYFSTKHVGJB<KN
      //{
      //  unsigned long long number = std::stoull(option);
      //  if(number < 3)
      //  {
      //    out << "<INVALID COMMAND>\n";
      //  }
      //  std::vector< double > values;
      //  std::transform(data.begin(), data.end(), values.begin(), areaNum(number));
      //  double sum = std::accumulate(values.begin(), values.end(), 0.0);
      //  out << std::round((sum / values.size()) * 10) / 10; //??????
      //}
    }
    else if(command == "MAX")
    {
      //std::string option = " ";
      //in >> option;
      //if(option == "")
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