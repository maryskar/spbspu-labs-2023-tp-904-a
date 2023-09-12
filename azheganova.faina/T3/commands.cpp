#include "commands.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <iofmtguard.h>

namespace azheganova
{
  bool isEven(const Polygon & polygon)
  {
    return (polygon.points.size() % 2 == 0);
  }

  bool isOdd(const Polygon & polygon)
  {
    return (polygon.points.size() % 2 != 0);
  }

  void getAreaEven(std::vector< Polygon > & polygon, std::ostream & out)
  {
    iofmtguard fmtguard(out);
    std::vector< double > rhs;
    std::transform(polygon.begin(), polygon.end(), std::back_inserter(rhs), isEven);
    out << std::fixed << std::setprecision(1) << std::accumulate(rhs.begin(), rhs.end(), 0.0) << '\n';
  }

  void getAreaOdd(std::vector< Polygon > & polygon, std::ostream & out)
  {
    iofmtguard fmtguard(out);
    std::vector< double > rhs;
    std::transform(polygon.begin(), polygon.end(), std::back_inserter(rhs), isOdd);
    out << std::fixed << std::setprecision(1) << std::accumulate(rhs.begin(), rhs.end(), 0.0) << '\n';
  }

  void getAreaMean(std::vector< Polygon > & polygon, std::ostream & out)
  {
    if (polygon.empty())
    {
      throw std::invalid_argument("error");
    }
    iofmtguard iofmtguard(out);
    std::vector< double > rhs(polygon.size());
    std::transform(polygon.begin(), polygon.end(), rhs.begin(), getArea);
    out << std::fixed << std::setprecision(1) << std::accumulate(rhs.begin(), rhs.end(), 0.0) / polygon.size() << "\n";
  }

  double isCountVertex(const Polygon & polygon, size_t vertexcount)
  {
    if (polygon.points.size() == vertexcount)
    {
      return getArea(polygon);
    }
    else
    {
      return 0.0;
    }
  }

  void getAreaNumOfVertexes(std::vector< Polygon > & polygon, size_t num, std::ostream & out)
  {
    using namespace std::placeholders;
    iofmtguard fmtguard(out);
    std::vector< double > areas;
    std::transform(polygon.begin(), polygon.end(), std::back_inserter(areas), std::bind(isCountVertex, _1, num));
    double area = std::accumulate(areas.begin(), areas.end(), 0.0);
    out << std::fixed << std::setprecision(1) << area << '\n';
  }

  void getMaxArea(std::vector< Polygon > & polygon, std::ostream & out)
  {
    if (polygon.empty())
    {
      throw std::invalid_argument("error");
    }
    iofmtguard fmtguard(out);
    std::vector< double > areas;
    std::transform(polygon.begin(), polygon.end(), std::back_inserter(areas), getArea);
    auto max = std::max_element(areas.begin(), areas.end());
    out << std::fixed << std::setprecision(1) << * max << '\n';
  }

  size_t countVertex(const Polygon & polygon)
  {
    return polygon.points.size();
  }

  void getMaxVertexes(std::vector< Polygon > & polygon, std::ostream & out)
  {
    if (polygon.empty())
    {
      throw std::invalid_argument("error");
    }
    iofmtguard fmtguard(out);
    std::vector< size_t > vertexes;
    std::transform(polygon.begin(), polygon.end(), std::back_inserter(vertexes), countVertex);
    auto max = std::max_element(vertexes.begin(), vertexes.end());
    out << std::fixed << * max << '\n';
  }

  void getMinArea(std::vector< Polygon > & polygon, std::ostream & out)
  {
    if (polygon.empty())
    {
      throw std::invalid_argument("error");
    }
    iofmtguard fmtguard(out);
    std::vector< double > areas;
    std::transform(polygon.begin(), polygon.end(), std::back_inserter(areas), getArea);
    auto min = std::min_element(areas.begin(), areas.end());
    out << std::fixed << std::setprecision(1) << * min << '\n';
  }

  void getMinVertexes(std::vector< Polygon > & polygon, std::ostream & out)
  {
    if (polygon.empty())
    {
      throw std::invalid_argument("error");
    }
    iofmtguard fmtguard(out);
    std::vector< size_t > vertexes;
    std::transform(polygon.begin(), polygon.end(), std::back_inserter(vertexes), countVertex);
    auto min = std::min_element(vertexes.begin(), vertexes.end());
    out << std::fixed << * min << '\n';
  }

  void countEven(std::vector< Polygon > & polygon, std::ostream & out)
  {
    iofmtguard fmtguard(out);
    out << std::fixed << std::count_if(polygon.begin(), polygon.end(), isEven) << '\n';
  }

  void countOdd(std::vector< Polygon > & polygon, std::ostream & out)
  {
    iofmtguard fmtguard(out);
    out << std::fixed << std::count_if(polygon.begin(), polygon.end(), isOdd) << '\n';
  }

  void countNumOfVertexes(std::vector< Polygon > & polygon, size_t num, std::ostream & out)
  {
    using namespace std::placeholders;
    iofmtguard iofmtguard(out);
    out << std::count_if(polygon.begin(), polygon.end(), std::bind(isCountVertex, _1, num)) << "\n";
  }

  bool isCompareRmecho(const Polygon & first, const Polygon & second, const Polygon & polygon)
  {
    return (first == polygon && second == polygon);
  }

  void getRmecho(std::vector< Polygon > & polygon, std::ostream & out, std::istream & in)
  {
    Polygon newpolygon;
    in >> newpolygon;
    if (!in)
    {
      throw std::logic_error("error");
    }
    using namespace std::placeholders;
    size_t sizeBefore = polygon.size();
    auto func = std::bind(isCompareRmecho, _1, _2, newpolygon);
    auto condition = std::unique(polygon.begin(), polygon.end(), func);
    polygon.erase(condition, polygon.end());
    out << sizeBefore - polygon.size() << '\n';
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

  void getRightshapes(std::vector< Polygon > & polygon, std::ostream & out)
  {
    out << std::count_if(polygon.begin(), polygon.end(), hasRightAngles) << '\n';
  }

  std::string inputCommand(std::istream & in)
  {
    std::string command = " ";
    in >> command;
    if (!in)
    {
      throw std::invalid_argument("error");
    }
    if (command == "RMECHO" || command == "RIGHTSHAPES")
    {
      return command;
    }
    std::string parameter = " ";
    in >> parameter;
    if (!in)
    {
      throw std::invalid_argument("error");
    }
    command += " ";
    command += parameter;
    return command;
  }

  std::ostream & printInvalidCommand(std::ostream & out)
  {
    out << "<INVALID COMMAND>";
    return out;
  }
}
