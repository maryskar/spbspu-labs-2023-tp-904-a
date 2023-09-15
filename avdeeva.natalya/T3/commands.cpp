#include "commands.h"
#include <algorithm>
#include <numeric>
#include <functional>
#include "helpFunctions.h"
template< typename Pred >
double calcArea(const std::deque< avdeeva::Polygon > & polygons, Pred p)
{
  std::deque< avdeeva::Polygon > filtPolygons;
  std::copy_if(polygons.begin(), polygons.end(), std::back_inserter(filtPolygons), p);
  std::deque< double > values(filtPolygons.size());
  std::transform(filtPolygons.begin(), filtPolygons.end(), values.begin(), avdeeva::getArea);
  return std::accumulate(values.begin(), values.end(), 0.0);
}
double avdeeva::calcAreaOdd(const std::deque< Polygon > & polygons)
{
  return calcArea(polygons, isOdd);
}
double avdeeva::calcAreaEven(const std::deque< Polygon > & polygons)
{
  return calcArea(polygons, isEven);
}
double avdeeva::calcAreaMean(const std::deque< Polygon > & polygons)
{
  if (polygons.empty())
  {
    throw std::invalid_argument("Empty deque of polygons");
  }
  std::deque< double > values(polygons.size());
  std::transform(polygons.begin(), polygons.end(), values.begin(), getArea);
  double value = std::accumulate(values.begin(), values.end(), 0.0);
  double res = value / polygons.size();
  return res;
}
double avdeeva::calcAreaVerts(const std::deque< Polygon > & polygons, size_t num)
{
  using namespace std::placeholders;
  auto pred = std::bind(isNumOfVerts, _1, num);
  return calcArea(polygons, pred);
}
template< typename Pred >
size_t counter(const std::deque< avdeeva::Polygon > & polygons, Pred p)
{
  return std::count_if(polygons.begin(), polygons.end(), p);
}
size_t avdeeva::counterEven(const std::deque< Polygon > & polygons)
{
  return counter(polygons, isEven);
}
size_t avdeeva::counterOdd(const std::deque< Polygon > & polygons)
{
  return counter(polygons, isOdd);
}
size_t avdeeva::counterVertexes(const std::deque< Polygon > & polygons, size_t num)
{
  using namespace std::placeholders;
  auto pred = std::bind(isNumOfVerts, _1, num);
  return counter(polygons, pred);
}
template< typename T, typename Func, typename Comp >
T findMax(const std::deque< avdeeva::Polygon > & polygons, Comp comp, Func func)
{
  if (polygons.empty())
  {
    throw std::logic_error("Empty deque of polygons");
  }
  return func(*std::max_element(polygons.begin(), polygons.end(), comp));
}
double avdeeva::findMaxArea(const std::deque< Polygon > & polygons)
{
  return findMax< double >(polygons, compArea, getArea);
}
size_t avdeeva::findMaxVerts(const std::deque< Polygon > & polygons)
{
  return findMax< size_t >(polygons, compSize, size);
}
template< typename T, typename Func, typename Comp >
T findMin(const std::deque< avdeeva::Polygon > & polygons, Comp comp, Func func)
{
  if (polygons.empty())
  {
    throw std::logic_error("Empty deque of polygons");
  }
  return func(*std::min_element(polygons.begin(), polygons.end(), comp));
}
double avdeeva::findMinArea(const std::deque< Polygon > & polygons)
{
  return findMin< double >(polygons, compArea, getArea);
}
size_t avdeeva::findMinVerts(const std::deque< Polygon > & polygons)
{
  return findMin< size_t >(polygons, compSize, size);
}
size_t avdeeva::countRightShapes(const std::deque< Polygon > & polygons)
{
  int res = std::count_if(polygons.begin(), polygons.end(), isRightshape);
  return res;
}
bool avdeeva::isInFrame(const std::deque< Polygon > & polygons, const Polygon & polygon)
{
  Polygon frame = createFrame(polygons);
  return isInFrame(polygon, frame);
}
