#include "commands.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <iofmtguard.h>
#include <map>

namespace azheganova
{
  bool checkEven(const Polygon & polygon)
  {
    return polygon.points.size() % 2 == 0;
  }

  bool checkOdd(const Polygon & polygon)
  {
    return !checkEven(polygon);
  }

  bool isCountVertex(const Polygon & polygon, size_t vertexcount)
  {
    return polygon.points.size() == vertexcount;
  }

  double getPartArea(double sum, const Point & p1, Point & p2)
  {
    sum += (p2.x * p1.y - p1.x * p2.y);
    p2 = p1;
    return sum;
  }

  double getArea(const Polygon & polygon)
  {
    using namespace std::placeholders;
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
    using namespace std::placeholders;
    double area = 0;
    std::vector< Polygon > areas;
    std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(areas), std::bind(checkEven, _1));
    area = std::accumulate(areas.cbegin(), areas.cend(), 0, getSumArea);
    return area;
  }

  double getAreaOdd(const std::vector< Polygon > & polygon)
  {
    using namespace std::placeholders;
    double area = 0;
    std::vector< Polygon > areas;
    std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(areas), std::bind(checkOdd, _1));
    area = std::accumulate(areas.cbegin(), areas.cend(), 0, getSumArea);
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
    using namespace std::placeholders;
    double area = 0;
    std::vector< Polygon > areas;
    std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(areas), std::bind(isCountVertex, _1, countVert));
    area = std::accumulate(areas.cbegin(), areas.cend(), 0, getSumArea);
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
    std::vector< Polygon >::const_iterator tmp = std::max_element(polygon.cbegin(), polygon.cend(), pred);
    return getArea(*tmp);
  }

  template< typename Pred >
  size_t getMaxOrMinVertexes(const std::vector< Polygon > & polygon, Pred pred)
  {
    std::vector< Polygon >::const_iterator tmp = std::max_element(polygon.cbegin(), polygon.cend(), pred);
    return tmp->points.size();
  }

  size_t getCountEven(const std::vector< Polygon > & polygon)
  {
    using namespace std::placeholders;
    return std::count_if(polygon.cbegin(), polygon.cend(), std::bind(checkEven, _1));
  }

  size_t getCountOdd(const std::vector< Polygon > & polygon)
  {
    using namespace std::placeholders;
    return std::count_if(polygon.cbegin(), polygon.cend(), std::bind(checkOdd, _1));
  }

  size_t getCountVertexes(const std::vector< Polygon > & polygon, size_t countVert)
  {
    using namespace std::placeholders;
    return std::count_if(polygon.cbegin(), polygon.cend(), std::bind(isCountVertex, _1, countVert));
  }

  bool isCompareRmecho(const Polygon & first, const Polygon & second, const Polygon & polygon)
  {
    return (first == polygon && second == polygon);
  }

  bool isRightAngle(const Point & a, const Point & b, const Point & c)
  {
    return (b.x - a.x) * (c.x - b.x) + (b.y - a.y) * (c.y - b.y) == 0;
  }

  bool hasRightAngles(std::vector< Point > points, size_t i)
  {
    size_t n = points.size();
    Point a = points[i];
    Point b = points[(i + 1) % n];
    Point c = points[(i + 2) % n];
    return isRightAngle(a, b, c);
  }

  bool getRightShapes(const Polygon & polygon)
  {
    using namespace std::placeholders;
    std::vector< size_t > ind(polygon.points.size());
    std::iota(ind.begin(), ind.end(), 0);
    return std::any_of(ind.begin(), ind.end(), std::bind(hasRightAngles, polygon.points, _1));
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
  std::string second = "";
  in >> second;
  iofmtguard iofmtguard(out);
  std::cout << std::fixed << std::setprecision(1);
  if (isNumber(second))
  {
    size_t size = std::stoul(second);
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
  out << commands.at(second)(polygon) << "\n";
}

void azheganova::max(std::vector< Polygon > & polygon, std::istream & in, std::ostream & out)
{
  std::string second = "";
  in >> second;
  if (!polygon.size())
  {
    throw std::logic_error("<INVALID COMMAND>");
  }
  if (second == "AREA")
  {
    iofmtguard iofmtguard(out);
    std::cout << std::fixed << std::setprecision(1);
    out << getMaxOrMinArea(polygon, isLessArea) << "\n";
  }
  else if (second == "VERTEXES")
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
  std::string second = "";
  in >> second;
  if (second == "AREA")
  {
    iofmtguard iofmtguard(out);
    std::cout << std::fixed << std::setprecision(1);
    out << getMaxOrMinArea(polygon, isGreaterArea) << "\n";
  }
  else if (second == "VERTEXES")
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
  std::string second = "";
  in >> second;
  if (isNumber(second))
  {
    size_t size = std::stoul(second);
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
  out << commands.at(second)(polygon) << "\n";
}

void azheganova::rmecho(std::vector< Polygon > & polygon, std::istream & in, std::ostream & out)
{
  using namespace std::placeholders;
  Polygon newpolygon;
  in >> newpolygon;
  if (!in)
  {
    throw std::logic_error("error");
  }
  size_t sizeBefore = polygon.size();
  polygon.erase(std::unique(polygon.begin(), polygon.end(), std::bind(isCompareRmecho, _1, _2, newpolygon)), polygon.end());
  out << sizeBefore - polygon.size() << '\n';
}

void azheganova::rightshapes(std::vector< Polygon > & polygon, std::ostream & out)
{
  out << std::count_if(polygon.begin(), polygon.end(), getRightShapes) << '\n';
}

std::ostream & azheganova::printInvalidCommand(std::ostream & out)
{
  out << "<INVALID COMMAND>" << '\n';
  return out;
}
