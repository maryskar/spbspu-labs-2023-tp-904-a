#include "commands.h"
#include <algorithm>
#include <numeric>
#include <functional>
#include "processFunctions.h"

template< typename Pred >
double calcArea(const std::deque< avdeeva::Polygon > & polygons, Pred p) {
  std::deque< avdeeva::Polygon > filtPolygons;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(filtPolygons), p);
  std::deque< double > values(filtPolygons.size());
  std::transform(filtPolygons.begin(), filtPolygons.end(), values.begin(), avdeeva::getArea);
  return std::accumulate(values.begin(), values.end(), 0.0);
}
double avdeeva::calcAreaOdd(const std::deque< Polygon > & polygons) {
  return calcArea(polygons, isOdd);
}

double avdeeva::calcAreaEven(const std::deque< Polygon > & polygons) {
  return calcArea(polygons, isEven);
}

double avdeeva::calcAreaMean(const std::deque< Polygon > & polygons) {
  if (polygons.empty()) {
    throw std::invalid_argument("Empty vector of polygons");
  }
  std::deque< double > values(polygons.size());
  std::transform(polygons.begin(), polygons.end(), values.begin(), getArea);
  double res = std::accumulate(values.begin(), values.end(), 0.0) / polygons.size();
  return res;
}
double avdeeva::calcAreaVerts(const std::deque< Polygon > & polygons, size_t num) {
  if (verts < 3) {
    throw std::invalid_argument("No polygons with this number of vertexes");
  }
  using namespace std::placeholders;
  auto pred = std::bind(isNumOfVerts, _1, verts);
  return calcArea(polygons, pred);
}
