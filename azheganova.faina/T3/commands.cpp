#include "commands.h"
#include <ostream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <functional>
#include <list>
#include <iofmtguard.h>

azheganova::Commands createCommands()
{
  azheganova::Commands res;
  res.dict_1.insert({ "AREA EVEN", azheganova::getAreaEven });
  res.dict_1.insert({ "AREA ODD", azheganova::getAreaOdd });
  res.dict_1.insert({ "AREA MEAN", azheganova::getAreaMean });
  res.dict_1.insert({ "MAX AREA", azheganova::getMaxArea });
  res.dict_1.insert({ "MAX VERTEXES", azheganova::getMaxVertexes });
  res.dict_1.insert({ "MIN AREA", azheganova::getMinArea });
  res.dict_1.insert({ "MIN VERTEXES", azheganova::getMinVertexes });
  res.dict_1.insert({ "COUNT EVEN", azheganova::countEven });
  res.dict_1.insert({ "COUNT ODD", azheganova::countOdd });
  res.dict_2.insert({ "AREA", azheganova::getAreaNumOfVertexes });
  res.dict_2.insert({ "COUNT", azheganova::countNumOfVertexes });
  //res.dict_3.insert({ "RMECHO", azheganova::getRmecho });
  //res.dict_3.insert({ "RIGHTSHAPES", azheganova::getRightshapes });
  return res;
}

using namespace std::placeholders;
bool azheganova::isEven(const Polygon & polygon)
{
  return (polygon.points.size() % 2 == 0);
}

bool azheganova::isOdd(const Polygon & polygon)
{
  return (polygon.points.size() % 2 != 0);
}

void azheganova::getAreaEven(const std::vector< Polygon > & polygon, std::ostream & out)
{
  iofmtguard fmtguard(out);
  std::vector< double > rhs;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(rhs), isEven);
  out << std::fixed << std::setprecision(1) << std::accumulate(rhs.begin(), rhs.end(), 0.0);
}

void azheganova::getAreaOdd(const std::vector< Polygon > & polygon, std::ostream & out)
{
  iofmtguard fmtguard(out);
  std::vector< double > rhs;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(rhs), isOdd);
  out << std::fixed << std::setprecision(1) << std::accumulate(rhs.begin(), rhs.end(), 0.0);
}

void azheganova::getAreaMean(const std::vector< Polygon > & polygon, std::ostream & out)
{
  if (polygon.empty())
  {
    throw std::invalid_argument("error");
  }
  iofmtguard iofmtguard(out);
  std::vector< double > rhs;
  std::transform(polygon.begin(), polygon.end(), rhs.begin(), getArea);
  out << std::fixed << std::setprecision(1) << std::accumulate(rhs.begin(), rhs.end(), 0.0) / polygon.size() << "\n";
}

double azheganova::isCountVertex(const Polygon & polygon, size_t vertexcount)
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

void azheganova::getAreaNumOfVertexes(const std::vector< Polygon > & polygon, size_t num, std::ostream & out)
{
  iofmtguard fmtguard(out);
  std::vector< double > areas;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(areas), std::bind(isCountVertex, _1, num));
  double area = std::accumulate(areas.begin(), areas.end(), 0.0);
  out << std::fixed << std::setprecision(1) << area;
}

void azheganova::getMaxArea(const std::vector< Polygon > & polygon, std::ostream & out)
{
  if (polygon.empty())
  {
    throw std::invalid_argument("error");
  }
  iofmtguard fmtguard(out);
  std::vector< double > areas;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(areas), getArea);
  auto max = std::max_element(areas.begin(), areas.end());
  out << std::fixed << std::setprecision(1) << * max;
}

size_t countVertex(const azheganova::Polygon & polygon)
{
  return polygon.points.size();
}

void azheganova::getMaxVertexes(const std::vector< Polygon > & polygon, std::ostream & out)
{
  if (polygon.empty())
  {
    throw std::invalid_argument("error");
  }
  iofmtguard fmtguard(out);
  std::vector< size_t > vertexes;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(vertexes), countVertex);
  auto max = std::max_element(vertexes.begin(), vertexes.end());
  out << std::fixed << * max;
}

void azheganova::getMinArea(const std::vector< Polygon > & polygon, std::ostream & out)
{
  if (polygon.empty())
  {
    throw std::invalid_argument("error");
  }
  iofmtguard fmtguard(out);
  std::vector< double > areas;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(areas), getArea);
  auto min = std::min_element(areas.begin(), areas.end());
  out << std::fixed << std::setprecision(1) << * min;
}

void azheganova::getMinVertexes(const std::vector< Polygon > & polygon, std::ostream & out)
{
  if (polygon.empty())
  {
    throw std::invalid_argument("error");
  }
  iofmtguard fmtguard(out);
  std::vector< size_t > vertexes;
  std::transform(polygon.begin(), polygon.end(), std::back_inserter(vertexes), countVertex);
  auto min = std::min_element(vertexes.begin(), vertexes.end());
  out << std::fixed << * min;
}

void azheganova::countEven(const std::vector< Polygon > & polygon, std::ostream & out)
{
  iofmtguard fmtguard(out);
  out << std::fixed << std::count_if(polygon.begin(), polygon.end(), isEven);
}

void azheganova::countOdd(const std::vector< Polygon > & polygon, std::ostream & out)
{
  iofmtguard fmtguard(out);
  out << std::fixed << std::count_if(polygon.begin(), polygon.end(), isOdd);
}

void azheganova::countNumOfVertexes(const std::vector< Polygon > & polygon, size_t num, std::ostream & out)
{
  iofmtguard iofmtguard(out);
  out << std::count_if(polygon.begin(), polygon.end(), std::bind(isCountVertex, _1, num)) << "\n";
}

//void azheganova::getRmecho(const std::vector< Polygon > & polygon, std::ostream & out)
//{

//}

//void azheganova::getRightshapes(const std::vector< Polygon > & polygon, std::ostream & out)
//{

//}

std::string azheganova::inputCommand(std::istream & in)
{
  std::string command = " ";
  in >> command;
  if (!in)
  {
    throw std::invalid_argument("error");
  }
  if (command == "RMECHO" && command == "RIGHTSHAPES")
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


