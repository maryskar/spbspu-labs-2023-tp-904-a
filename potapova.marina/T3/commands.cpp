#include "commands.h"
#include <functional>
#include "rectangle.h"

void potapova::printAverageArea(const std::deque< Polygon >& polygons,
    std::istream&,
    std::ostream& out)
{
  if (polygons.empty())
  {
    throw std::logic_error("There are no polygons");
  }
  double sum_of_areas = 0.0;
  sum_of_areas = getSumOfAreas(polygons);
  double average_area = sum_of_areas / static_cast< double >(polygons.size());
  out << std::fixed << std::setprecision(1) << average_area << '\n';
}

void potapova::printSumOfAreasWithSpecificPointsNum(const std::deque< Polygon >& polygons,
    size_t target_count_points,
    std::istream&,
    std::ostream& out)
{
  using namespace std::placeholders;
  if (target_count_points < 3)
  {
    throw std::logic_error("Too few target points");
  }
  double sum_areas = 0.0;
  sum_areas = std::accumulate(polygons.begin(),
    polygons.end(),
    0.0,
    std::bind(addAreaToSumIfNumPoints, _1, _2, target_count_points));
  out << std::fixed << std::setprecision(1) << sum_areas << '\n';
}

void potapova::printPolygonsNumWithTargetPointsNum(const std::deque< Polygon >& polygons,
    size_t target_count_points,
    std::istream&,
    std::ostream& out)
{
  using namespace std::placeholders;
  if (target_count_points < 3)
  {
    throw std::logic_error("Too few target points");
  }
  out << std::count_if(polygons.begin(), polygons.end(), std::bind(checkDesiredNumPoints, target_count_points, _1)) << '\n';
}

void potapova::removePolygonDuplicates(std::deque< Polygon >& polygons,
    std::istream& in,
    std::ostream& out)
{
  using namespace std::placeholders;
  Polygon target_polygon;
  if (!(in >> target_polygon))
  {
    in.clear(std::ios_base::goodbit);
    throw std::logic_error("Input polygon error");
  }
  std::deque< Polygon >::iterator new_end_iter = std::unique(polygons.begin(),
    polygons.end(),
    std::bind(isEqual, _1, _2, target_polygon));
  ptrdiff_t count_removed = std::distance(new_end_iter, polygons.end());
  polygons.resize(polygons.size() - static_cast< size_t >(count_removed));
  out << count_removed << '\n';
}

void potapova::printIsPolygonInFrame(const std::deque< Polygon >& polygons,
    std::istream& in,
    std::ostream& out)
{
  Rectangle frame(polygons.front());
  frame.expandBoundsToPolygons(polygons);
  Polygon input_polygon;
  if (!(in >> input_polygon))
  {
    in.clear(std::ios_base::goodbit);
    throw std::logic_error("Input polygon error");
  }
  if (frame.isPolygonInFrame(input_polygon))
  {
    out << "<TRUE>\n";
  }
  else
  {
    out << "<FALSE>\n";
  }
}
