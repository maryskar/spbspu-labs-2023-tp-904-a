#include "Commands.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <string>

bool isEvenNumOfVertexes(const ganiullin::Polygon& polygon)
{
  return polygon.points.size() % 2 == 0;
}
bool isOddNumOfVertexes(const ganiullin::Polygon& polygon)
{
  return !isEvenNumOfVertexes(polygon);
}
bool isDigits(const std::string& str)
{
  return std::all_of(str.begin(), str.end(), ::isdigit);
}

double getAreaIf(const std::vector< ganiullin::Polygon >& polygons,
  std::function< bool(const ganiullin::Polygon&) > predicate)
{
  std::vector< ganiullin::Polygon > filtered;
  std::copy_if(std::begin(polygons), std::end(polygons), std::back_inserter(filtered), predicate);
  std::vector< double > areas;
  std::transform(std::begin(filtered), std::end(filtered), std::back_inserter(areas), ganiullin::getPolygonArea);
  return std::accumulate(std::begin(areas), std::end(areas), 0.0);
}
double getArea(const std::vector< ganiullin::Polygon >& polygons)
{
  std::vector< double > areas;
  std::transform(std::begin(polygons), std::end(polygons), std::back_inserter(areas), ganiullin::getPolygonArea);
  return std::accumulate(std::begin(areas), std::end(areas), 0.0);
}

double ganiullin::processArea(std::istream& in, const std::vector< ganiullin::Polygon >& polygons)
{
  using namespace std::placeholders;
  size_t numVertex = 0;
  in >> numVertex;
  if (in) {
    return getAreaIf(polygons,
      std::bind(std::equal_to< size_t > {}, std::bind(ganiullin::getNumOfVertexes, _1), numVertex));
  } else {
    in.clear();
  }

  std::string args = "";
  std::getline(in, args, '\n');
  if (args == "EVEN") {
    return getAreaIf(polygons, isEvenNumOfVertexes);
  } else if (args == "ODD") {
    return getAreaIf(polygons, isOddNumOfVertexes);
  } else if (args == "MEAN" && polygons.size() > 0) {
    return getArea(polygons) / polygons.size();
  } else {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}
double ganiullin::processMin(std::istream& in, const std::vector< ganiullin::Polygon >& polygons);
double ganiullin::processMax(std::istream& in, const std::vector< ganiullin::Polygon >& polygons);
