#include "commands.h"
#include <algorithm>
#include <functional>
#include <numeric>
#include <iofmtguard.h>

namespace azheganova
{
  using namespace std::placeholders;
  Commands::Commands()
  {
    dict_1.insert({ "AREA EVEN", getAreaEven });
    dict_1.insert({ "AREA ODD", getAreaOdd });
    dict_1.insert({ "AREA MEAN", getAreaMean });
    dict_1.insert({ "MAX AREA", getMaxArea });
    dict_1.insert({ "MAX VERTEXES", getMaxVertexes });
    dict_1.insert({ "MIN AREA", getMinArea });
    dict_1.insert({ "MIN VERTEXES", getMinVertexes });
    dict_1.insert({ "COUNT EVEN", countEven });
    dict_1.insert({ "COUNT ODD", countOdd });
    dict_2.insert({ "AREA", getAreaNumOfVertexes });
    dict_2.insert({ "COUNT", countNumOfVertexes });
    dict_3.insert({ "RMECHO", getRmecho });
    dict_1.insert({ "RIGHTSHAPES", getRightshapes });
  }

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
    std::vector< Polygon > evenPol;
    std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(evenPol), std::bind(isEven, _1));
    out << std::accumulate(evenPol.cbegin(), evenPol.cend(), 0, getSumArea) << '\n';
  }

  void getAreaOdd(std::vector< Polygon > & polygon, std::ostream & out)
  {
    iofmtguard fmtguard(out);
    std::vector< Polygon > oddPol;
    std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(oddPol), std::bind(isOdd, _1));
    out << std::accumulate(oddPol.cbegin(), oddPol.cend(), 0, getSumArea) << '\n';
  }

  void getAreaMean(std::vector< Polygon > & polygon, std::ostream & out)
  {
    iofmtguard fmtguard(out);
    if (!polygon.size())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }
    double area = 0;
    area = std::accumulate(polygon.cbegin(), polygon.cend(), 0, getSumArea);
    auto area2 = area / polygon.size();
    out << area2 << "\n";
  }

  double isCountVertex(const Polygon & polygon, size_t vertexcount)
  {
    return polygon.points.size() == vertexcount;
  }

  void getAreaNumOfVertexes(std::vector< Polygon > & polygon, size_t num, std::ostream & out)
  {
    iofmtguard fmtguard(out);
    std::vector< Polygon > areas;
    std::copy_if(polygon.cbegin(), polygon.cend(), std::back_inserter(areas), std::bind(isCountVertex, _1, num));
    out << std::accumulate(areas.cbegin(), areas.cend(), 0, getSumArea) << '\n';
  }

  void getMaxArea(std::vector< Polygon > & polygon, std::ostream & out)
  {
    iofmtguard fmtguard(out);
    if (polygon.empty())
    {
      throw std::invalid_argument("error");
    }
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
    out << std::count_if(polygon.cbegin(), polygon.cend(), std::bind(isEven, _1)) << '\n';
  }

  void countOdd(std::vector< Polygon > & polygon, std::ostream & out)
  {
    iofmtguard fmtguard(out);
    out << std::fixed << std::count_if(polygon.begin(), polygon.end(), isOdd) << '\n';
  }

  void countNumOfVertexes(std::vector< Polygon > & polygon, size_t num, std::ostream & out)
  {
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

  void Commands::doComm(const str & comm, std::vector< Polygon > & data, std::ostream & out) const
  {
    auto func = dict_1.at(comm);
    func(data, out);
  }
  void Commands::doComm(const str & comm, std::vector< Polygon > & data, size_t num, std::ostream & out) const
  {
    auto func = dict_2.at(comm);
    func(data, num, out);
  }

  void Commands::doComm(const str & comm, std::vector< Polygon > & data, std::ostream & out, std::istream & in) const
  {
    auto func = dict_3.at(comm);
    func(data, out, in);
  }

  void doCommand(const str & command, const Commands & dicts, std::vector< Polygon > & data, std::istream & in, std::ostream & out)
  {
    try
    {
      dicts.doComm(command, data, out);
      return;
    }
    catch(const std::out_of_range & e)
    {}
    try
    {
      dicts.doComm(command, data, out, in);
      return;
    }
    catch(const std::out_of_range & e)
    {}
    size_t pos = command.find(' ');
    size_t num = std::stoull(command.substr(pos));
    dicts.doComm(command.substr(0, pos), data, num, out);
  }

  std::ostream & printInvalidCommand(std::ostream & out)
  {
    out << "<INVALID COMMAND>";
    return out;
  }
}
