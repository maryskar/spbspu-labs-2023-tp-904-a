#include "commands.h"

#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <string>

#include <streamsguard.h>

namespace chulkov {
  using namespace std::placeholders;

  bool isEven(const Polygon& polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool isOdd(const Polygon& polygon)
  {
    return !isEven(polygon);
  }

  bool isEqualVertexes(const Polygon& polygon, size_t vert)
  {
    return polygon.points.size() == vert;
  }

  double getPartArea(double sum, const Point& frst, Point& sec)
  {
    sum += (frst.x * frst.y - frst.x * sec.y);
    sec = frst;
    return sum;
  }

  double getArea(const Polygon& polygon)
  {
    Point prev = polygon.points[polygon.points.size() - 1];
    double area = 0;
    area = std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0, std::bind(getPartArea, _1, _2, prev));
    return std::abs(area / 2);
  }

  double getSumArea(double area, const Polygon& polygon)
  {
    return area + getArea(polygon);
  }

  double areaEven(const std::vector< Polygon >& polygons)
  {
    double area = 0;
    std::vector< Polygon > evenPol;
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(evenPol), std::bind(isEven, _1));
    area = std::accumulate(evenPol.cbegin(), evenPol.cend(), 0, getSumArea);
    return area;
  }

  double areaOdd(const std::vector< Polygon >& polygons)
  {
    double area = 0;
    std::vector< Polygon > oddPol;
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(oddPol), std::bind(isOdd, _1));
    area = std::accumulate(oddPol.cbegin(), oddPol.cend(), 0, getSumArea);
    return area;
  }

  double areaMean(const std::vector< Polygon >& polygons)
  {
    if (!polygons.size()) {
      throw std::logic_error("<INVALID COMMAND>");
    }
    double area = 0;
    area = std::accumulate(polygons.cbegin(), polygons.cend(), 0, getSumArea);
    return area / polygons.size();
  }

  double areaVertexes(const std::vector< Polygon >& polygons, size_t countVert)
  {
    double area = 0;
    std::vector< Polygon > vertPol;
    std::copy_if(polygons.cbegin(), polygons.cend(), std::back_inserter(vertPol),
                 std::bind(isEqualVertexes, _1, countVert));
    area = std::accumulate(vertPol.cbegin(), vertPol.cend(), 0, getSumArea);
    return area;
  }

  bool rmEchoCompare(const Polygon& frst, const Polygon& sec, const Polygon& inPol)
  {
    return (frst == inPol && sec == inPol);
  }

  bool isLessArea(const Polygon& frst, const Polygon& sec)
  {
    return getArea(frst) < getArea(sec);
  }

  bool isGreaterArea(const Polygon& frst, const Polygon& sec)
  {
    return !isLessArea(frst, sec);
  }

  bool isLessVertexes(const Polygon& frst, const Polygon& sec)
  {
    return frst.points.size() <= sec.points.size();
  }

  bool isGreaterVertexes(const Polygon& frst, const Polygon& sec)
  {
    return !isLessVertexes(frst, sec);
  }

  template < typename T > double maxOrMinArea(const std::vector< Polygon >& polygons, T pred)
  {
    std::vector< Polygon >::const_iterator temp = std::max_element(polygons.cbegin(), polygons.cend(), pred);
    return getArea(*temp);
  }

  template < typename T > size_t maxOrMinVertexes(const std::vector< Polygon >& polygons, T pred)
  {
    std::vector< Polygon >::const_iterator temp = std::max_element(polygons.cbegin(), polygons.cend(), pred);
    return temp->points.size();
  }

  size_t countEven(const std::vector< Polygon >& polygon)
  {
    return std::count_if(polygon.cbegin(), polygon.cend(), std::bind(isEven, _1));
  }

  size_t countOdd(const std::vector< Polygon >& polygon)
  {
    return std::count_if(polygon.cbegin(), polygon.cend(), std::bind(isOdd, _1));
  }

  size_t countVertexes(const std::vector< Polygon >& polygon, size_t countVert)
  {
    return std::count_if(polygon.cbegin(), polygon.cend(), std::bind(isEqualVertexes, _1, countVert));
  }

  bool isNumber(const std::string& str)
  {
    bool isNumber = 1;
    for (size_t i = 0; i < str.size(); i++) {
      if (!std::isdigit(str[i]) && !((str[i] == '-') && (i == 0))) {
        isNumber = 0;
      }
    }
    return isNumber;
  }

  bool isPerm(const Polygon& frst, const Polygon& sec)
  {
    if (frst.points.size() != sec.points.size()) {
      return false;
    }
    return std::is_permutation(frst.points.cbegin(), frst.points.cend(), sec.points.cbegin());
  }

  void getArea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::istream::sentry sentryIn(in);
    std::ostream::sentry sentryOut(out);
    if (!sentryIn || !sentryOut) {
      return;
    }
    std::string secondArg = "";
    in >> secondArg;
    StreamGuard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    if (isNumber(secondArg)) {
      size_t size = std::stoul(secondArg);
      if (size < 3) {
        throw std::logic_error("<INVALID COMMAND>");
      }
      out << areaVertexes(polygons, size) << "\n";
      return;
    }
    using command_t = std::function< double(const std::vector< Polygon >&) >;
    std::map< std::string, command_t > commands{
        {"EVEN", areaEven},
        {"ODD", areaOdd},
        {"MEAN", areaMean},
    };
    out << commands.at(secondArg)(polygons) << "\n";
  }

  void getMax(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::istream::sentry sentryIn(in);
    std::ostream::sentry sentryOut(out);
    if (!sentryIn || !sentryOut) {
      return;
    }
    std::string secondArg = "";
    in >> secondArg;
    if (!polygons.size()) {
      throw std::logic_error("<INVALID COMMAND>");
    }
    if (secondArg == "AREA") {
      StreamGuard guard(std::cout);
      std::cout << std::fixed << std::setprecision(1);
      out << maxOrMinArea(polygons, isLessArea) << "\n";
    } else if (secondArg == "VERTEXES") {
      out << maxOrMinVertexes(polygons, isLessVertexes) << "\n";
    } else {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }

  void getMin(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::istream::sentry sentryIn(in);
    std::ostream::sentry sentryOut(out);
    if (!sentryIn || !sentryOut) {
      return;
    }
    std::string secondArg = "";
    in >> secondArg;
    if (secondArg == "AREA") {
      StreamGuard quard(std::cout);
      std::cout << std::fixed << std::setprecision(1);
      out << maxOrMinArea(polygons, isGreaterArea) << "\n";
    } else if (secondArg == "VERTEXES") {
      out << maxOrMinVertexes(polygons, isGreaterVertexes) << "\n";
    } else {
      throw std::logic_error("<INVALID COMMAND>");
    }
  }

  void getCount(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::istream::sentry sentryIn(in);
    std::ostream::sentry sentryOut(out);
    if (!sentryIn || !sentryOut) {
      return;
    }
    std::string secondArg;
    in >> secondArg;
    if (isNumber(secondArg)) {
      size_t size = std::stoul(secondArg);
      if (size < 3) {
        throw std::logic_error("<INVALID COMMAND>");
      }
      out << countVertexes(polygons, size) << "\n";
      return;
    }
    using command_t = std::function< size_t(const std::vector< Polygon >& pol) >;
    std::map< std::string, command_t > commands{{"EVEN", countEven}, {"ODD", countOdd}};
    out << commands.at(secondArg)(polygons) << "\n";
  }

  void getPerms(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::istream::sentry sentryIn(in);
    std::ostream::sentry sentryOut(out);
    if (!sentryIn || !sentryOut) {
      return;
    }
    Polygon input;
    in >> input;
    if (!in) {
      throw std::logic_error("<INVALID COMMAND>");
    }
    out << std::count_if(polygons.cbegin(), polygons.cend(), std::bind(isPerm, _1, input)) << "\n";
  }

  void getRmecho(std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
  {
    std::istream::sentry sentryIn(in);
    std::ostream::sentry sentryOut(out);
    if (!sentryIn || !sentryOut) {
      return;
    }
    Polygon polygon;
    in >> polygon;
    if (!in) {
      throw std::logic_error("<INVALID COMMAND>");
    }
    size_t beforeSize = polygons.size();
    polygons.erase(std::unique(begin(polygons), end(polygons), std::bind(rmEchoCompare, _1, _2, polygon)),
                   end(polygons));
    out << beforeSize - polygons.size() << "\n";
  }
}
