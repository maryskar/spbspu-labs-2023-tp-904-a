#include "commands.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <iofmtguard.h>

namespace azheganova
{
  using namespace std::placeholders;
    bool isEven(const Polygon & polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool isOdd(const Polygon & polygon)
  {
    return !isEven(polygon);
  }

  bool isEqualVertexes(const Polygon & polygon, size_t vert)
  {
    return polygon.points.size() == vert;
  }

  double getPartArea(double sum, const Point & p1, Point & p2)
  {
    sum += (p2.x * p1.y - p1.x * p2.y);
    p2 = p1;
    return sum;
  }
  double getArea(const Polygon & polygon)
  {
    Point prev = polygon.points[polygon.points.size() - 1];
    double area = 0;
    area = std::accumulate(polygon.points.cbegin(), polygon.points.cend(), 0, std::bind(getPartArea, _1, _2, prev));
    return std::abs(area / 2);
  }

  double getSumArea(double area, const Polygon & polygon)
  {
    return area + getArea(polygon);
  }

  double getAreaEven(const std::vector< Polygon > & polygon)
  {
    double area = 0;
    std::vector< Polygon > evenPol;
    std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(evenPol), std::bind(isEven, _1));
    area = std::accumulate(evenPol.cbegin(), evenPol.cend(), 0, getSumArea);
    return area;
  }

  double getAreaOdd(const std::vector< Polygon > & polygon)
  {
    double area = 0;
    std::vector< Polygon > oddPol;
    std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(oddPol), std::bind(isOdd, _1));
    area = std::accumulate(oddPol.cbegin(), oddPol.cend(), 0, getSumArea);
    return area;
  }

  double getAreaMean(const std::vector< Polygon > & polygon)
  {
    if (!polygon.size())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    double area = 0;
    area = std::accumulate(polygon.cbegin(), polygon.cend(), 0, getSumArea);
    return area / polygon.size();
  }

  double getAreaVertexes(const std::vector< Polygon > & polygon, size_t countVert)
  {
    double area = 0;
    std::vector< Polygon > vertPol;
    std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(vertPol), std::bind(isEqualVertexes, _1, countVert));
    area = std::accumulate(vertPol.cbegin(), vertPol.cend(), 0, getSumArea);
    return area;
  }
  bool isLessArea(const Polygon & polygon1, const Polygon & polygon2)
  {
    return getArea(polygon1) < getArea(polygon2);
  }

  bool isGreaterArea(const Polygon & polygon1, const Polygon & polygon2)
  {
    return !isLessArea(polygon1, polygon2);
  }

  bool isLessVertexes(const Polygon & polygon1, const Polygon & polygon2)
  {
    return polygon1.points.size() <= polygon2.points.size();
  }

  bool isGreaterVertexes(const Polygon & polygon1, const Polygon & polygon2)
  {
    return !isLessVertexes(polygon1, polygon2);
  }

  template< typename Pred >
  double getMaxOrMinArea(const std::vector< Polygon > & polygon, Pred pred)
  {
    std::vector< Polygon >::const_iterator temp = std::max_element(polygon.cbegin(), polygon.cend(), pred);
    return getArea(*temp);
  }

  template< typename Pred >
  size_t getMaxOrMinVertexes(const std::vector< Polygon > & polygon, Pred pred)
  {
    std::vector< Polygon >::const_iterator temp = std::max_element(polygon.cbegin(), polygon.cend(), pred);
    return temp->points.size();
  }

  size_t getCountEven(const std::vector< Polygon > & polygon)
  {
    return std::count_if(polygon.cbegin(), polygon.cend(), std::bind(isEven, _1));
  }

  size_t getCountOdd(const std::vector< Polygon > & polygon)
  {
    return std::count_if(polygon.cbegin(), polygon.cend(), std::bind(isOdd, _1));
  }

  size_t getCountVertexes(const std::vector< Polygon > & polygon, size_t countVert)
  {
    return std::count_if(polygon.cbegin(), polygon.cend(), std::bind(isEqualVertexes, _1, countVert));
  }

  bool isCompareRmecho(const Polygon & first, const Polygon & second, const Polygon & polygon)
  {
    return (first == polygon && second == polygon);
  }

  bool isRightAngle(const Point & a, const Point & b, const Point & c)
  {
    return (b.x - a.x) * (c.x - b.x) + (b.y - a.y) * (c.y - b.y) == 0;
  }

  bool hasRightAngles(const Polygon & polygon)
  {
    auto n = polygon.points.size();
    auto points = polygon.points;
    auto state = [&](size_t i)
    {
      Point a = points[i];
      Point b = points[(i + 1) % n];
      Point c = points[(i + 2) % n];
      return isRightAngle(a, b, c);
    };
    std::vector< size_t > ind(n);
    std::iota(ind.begin(), ind.end(), 0);
    return std::any_of(ind.begin(), ind.end(), state);
  }

  bool isNumber(const std::string & str)
  {
    bool isNumber = 1;
    for (size_t i = 0; i < str.size(); i++)
    {
      if (!std::isdigit(str[i]) && !((str[i] == '-') && (i == 0)))
      {
        isNumber = 0;
      }
    }
    return isNumber;
  }
}

void azheganova::area(std::vector< Polygon > & polygon, std::istream & in, std::ostream & out)
{
  std::istream::sentry sentryIn(in);
  std::ostream::sentry sentryOut(out);
  if (!sentryIn || !sentryOut)
  {
    return;
  }
  std::string secondArg = "";
  in >> secondArg;
  iofmtguard iofmtguard(out);
  std::cout << std::fixed << std::setprecision(1);
  if (isNumber(secondArg))
  {
    size_t size = std::stoul(secondArg);
    if (size < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    out << getAreaVertexes(polygon, size) << "\n";
    return;
  }
  using command_t = std::function< double(const std::vector< Polygon >&) >;
  std::map < std::string, command_t > commands
  {
    {"EVEN", getAreaEven},
    {"ODD", getAreaOdd},
    {"MEAN", getAreaMean},
  };
  out << commands.at(secondArg)(polygon) << "\n";
}

void azheganova::max(std::vector< Polygon > & polygon, std::istream & in, std::ostream & out)
{
  std::istream::sentry sentryIn(in);
  std::ostream::sentry sentryOut(out);
  if (!sentryIn || !sentryOut)
  {
    return;
  }
  std::string secondArg = "";
  in >> secondArg;
  if (!polygon.size())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  if (secondArg == "AREA")
  {
    iofmtguard iofmtguard(out);
    std::cout << std::fixed << std::setprecision(1);
    out << getMaxOrMinArea(polygon, isLessArea) << "\n";
  }
  else if (secondArg == "VERTEXES")
  {
    out << getMaxOrMinVertexes(polygon, isLessVertexes) << "\n";
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void azheganova::min(std::vector< Polygon > & polygon, std::istream & in, std::ostream & out)
{
  std::istream::sentry sentryIn(in);
  std::ostream::sentry sentryOut(out);
  if (!sentryIn || !sentryOut)
  {
    return;
  }
  std::string secondArg = "";
  in >> secondArg;
  if (secondArg == "AREA")
  {
    iofmtguard iofmtguard(out);
    std::cout << std::fixed << std::setprecision(1);
    out << getMaxOrMinArea(polygon, isGreaterArea) << "\n";
  }
  else if (secondArg == "VERTEXES")
  {
    out << getMaxOrMinVertexes(polygon, isGreaterVertexes) << "\n";
  }
  else
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
}

void azheganova::count(std::vector< Polygon > & polygon, std::istream & in, std::ostream & out)
{
  std::istream::sentry sentryIn(in);
  std::ostream::sentry sentryOut(out);
  if (!sentryIn || !sentryOut)
  {
    return;
  }
  std::string secondArg = "";
  in >> secondArg;
  if (isNumber(secondArg))
  {
    size_t size = std::stoul(secondArg);
    if (size < 3)
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    out << getCountVertexes(polygon, size) << "\n";
    return;
  }
  using command_t = std::function< size_t(const std::vector< Polygon >& pol) >;
  std::map < std::string, command_t > commands
  {
    {"EVEN", getCountEven},
    {"ODD", getCountOdd}
  };
  out << commands.at(secondArg)(polygon) << "\n";
}

void azheganova::rmecho(std::vector< Polygon > & polygon, std::istream & in, std::ostream & out)
{
  std::istream::sentry sentryIn(in);
  std::ostream::sentry sentryOut(out);
  if (!sentryIn || !sentryOut)
  {
    return;
  }
  Polygon newpolygon;
  in >> newpolygon;
  if (!in)
  {
    throw std::logic_error("error");
  }
  size_t sizeBefore = polygon.size();
  auto func = std::bind(isCompareRmecho, _1, _2, newpolygon);
  auto condition = std::unique(polygon.begin(), polygon.end(), func);
  polygon.erase(condition, polygon.end());
  out << sizeBefore - polygon.size() << '\n';
}

void azheganova::rightshapes(std::vector< Polygon > & polygon, std::ostream & out)
{
  out << std::count_if(polygon.begin(), polygon.end(), azheganova::hasRightAngles) << '\n';
}

